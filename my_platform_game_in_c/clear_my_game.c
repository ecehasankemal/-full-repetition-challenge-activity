#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/xpm.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define GRAVITY 1.5
#define JUMP_STRENGTH 18
#define GROUND_LEVEL (WINDOW_HEIGHT - 64)

typedef struct {
    int playerX;
    int playerY;
} Coordinate;

typedef struct {
    bool isRight;
    bool isLeft;
    bool isUp;
    bool isFire;
    bool isRun;
    bool isJump;
} Direction;

typedef struct {
    int index;
    int speed;
    int display;
    int width;
    int height;
    int frame_counter;
    int frame_delay;
    char lastDirection;
    int velocityY;
    int health;
    int stamina;
    bool isOnGround;
    Coordinate coord;
    Direction direct;
    Pixmap anim[12];
    Pixmap mask[12];
    GC gc[12];
} t_characters;

typedef struct {
    Display *display;
    Window window;
    int screen;
    t_characters *one;
    t_characters *two;
} t_game;


const char *filenames[] =
{
    "megafire.xpm", "megaidle.xpm", "megajump.xpm",
    "megawalk.xpm", "megawalk2.xpm", "megawalk3.xpm",
    "megafirel.xpm", "megaidlel.xpm", "megajumpl.xpm",
    "megawalkl.xpm", "megawalkl2.xpm", "megawalkl3.xpm"
};

void
    handleKeyPress(XKeyEvent *event, t_characters *player1, t_characters *player2)
{
    KeySym key = XLookupKeysym(event, 0);
    switch (key)
    {
    case XK_Escape:
        exit(0);
    case XK_d:
        player1->direct.isRight = true;
        player1->lastDirection = 'R';
        break;
    case XK_a:
        player1->direct.isLeft = true;
        player1->lastDirection = 'L';
        break;
    case XK_w:
        if (player1->isOnGround)
        {
            player1->direct.isJump = true;
            player1->velocityY = -JUMP_STRENGTH;
            player1->isOnGround = false;
        }
        break;
    case XK_space:
        player1->direct.isFire = true;
        break;
    case XK_Shift_L:
        player1->direct.isRun = true;
        break;
    case XK_Right:
        player2->direct.isRight = true;
        player2->lastDirection = 'R';
        break;
    case XK_Left:
        player2->direct.isLeft = true;
        player2->lastDirection = 'L';
        break;
    case XK_Up:
        if (player2->isOnGround)
        {
            player2->direct.isJump = true;
            player2->velocityY = -JUMP_STRENGTH;
            player2->isOnGround = false;
        }
        break;
    case XK_Return:
        player2->direct.isFire = true;
        break;
    case XK_Shift_R:
        player2->direct.isRun = true;
        break;
    default:
        break;
    }
}

void
    handleKeyRelease(XKeyEvent *event, t_characters *player1, t_characters *player2)
{
    KeySym key = XLookupKeysym(event, 0);
    switch (key)
    {
    case XK_d:
        player1->direct.isRight = false;
        break;
    case XK_a:
        player1->direct.isLeft = false;
        break;
    case XK_w:
        player1->direct.isJump = false;
        break;
    case XK_space:
        player1->direct.isFire = false;
        break;
    case XK_Shift_L:
        player1->direct.isRun = false;
        break;
    case XK_Right:
        player2->direct.isRight = false;
        break;
    case XK_Left:
        player2->direct.isLeft = false;
        break;
    case XK_Up:
        player2->direct.isJump = false;
        break;
    case XK_Return:
        player2->direct.isFire = false;
        break;
    case XK_Shift_R:
        player2->direct.isRun = false;
        break;
    default:
        break;
    }
}

void update_animation(t_characters *character, Display *display, Window window) {
    // Frame güncelleme
    if (character->frame_counter >= character->frame_delay) {
        character->frame_counter = 0;

        // Animasyon kontrolü
        if (character->direct.isFire) {
            character->index = (character->lastDirection == 'L') ? 6 : 0; // Yüksek ihtimalle bu durumda 'fire' animasyonu
        } else if (character->direct.isJump) {
            character->index = 2; // Jump animasyonu
        } else if (character->direct.isLeft || character->direct.isRight) {
            character->index++; // Yürüyüş animasyonu
        } else {
            character->index = 1; // Idle durumu
        }
    } else {
        character->frame_counter++;
    }

    // Hız ayarı
    character->speed = character->direct.isRun ? 6 : 4;

    // Karakter pozisyonu güncelleme
    if (character->direct.isLeft) character->coord.playerX -= character->speed;
    if (character->direct.isRight) character->coord.playerX += character->speed;

    // Ekran sınırları
    if (character->coord.playerX < 0) character->coord.playerX = 0;
    if (character->coord.playerX > WINDOW_WIDTH - character->width) character->coord.playerX = WINDOW_WIDTH - character->width;

    // Yerçekimi ve zemin kontrolü
    if (!character->isOnGround) {
        character->velocityY += GRAVITY;
        character->coord.playerY += character->velocityY;

        if (character->coord.playerY >= GROUND_LEVEL) {
            character->coord.playerY = GROUND_LEVEL;
            character->isOnGround = true;
            character->velocityY = 0;
        } else {
            character->isOnGround = false;
        }
    }
}


void check_health_stamina(t_characters *character1, t_characters *character2) {
    // Stamina süreyle dolacak
    if (character1->stamina < 100) {
        character1->stamina += 1; // Zamanla dolum
    }
    if (character2->stamina < 100) {
        character2->stamina += 1; // Zamanla dolum
    }

    // Sağlık süreyle dolacak
    if (character1->health < 100) {
        character1->health += 1; // Zamanla dolum
    }
    if (character2->health < 100) {
        character2->health += 1; // Zamanla dolum
    }

    // Değerleri sınırla
    character1->stamina = (character1->stamina > 100) ? 100 : character1->stamina;
    character2->stamina = (character2->stamina > 100) ? 100 : character2->stamina;
    character1->health = (character1->health > 100) ? 100 : character1->health;
    character2->health = (character2->health > 100) ? 100 : character2->health;
    character1->health = (character1->health < 0) ? 0 : character1->health;
    character2->health = (character2->health < 0) ? 0 : character2->health;

    // Çarpışma kontrolü ve sağlık kaybı
    int distance_x = abs(character1->coord.playerX - character2->coord.playerX);
    int distance_y = abs(character1->coord.playerY - character2->coord.playerY);
    
    // Karakterlerin her ikisi de birbirine çarparsa
    if (distance_x < 50 && distance_y < 50) {
        if (character1->direct.isFire) {
            character2->health -= 1; // Karakter 1 saldırırsa karakter 2'nin sağlığını azalt
            character1->direct.isFire = true; // Saldırı tamamlandı
        }
        if (character2->direct.isFire) {
            character1->health -= 1; // Karakter 2 saldırırsa karakter 1'in sağlığını azalt
            character2->direct.isFire = true; // Saldırı tamamlandı
        }
    }
}



void
    render_health_stamina(Display *display, Window window, t_characters *character1, t_characters *character2)
{
    char    health_text[50];
    char    stamina_text[50];

    GC gc = DefaultGC(display, 0);


    // metin rengini ayarladım la burda
    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    // metin boyutunu atarkadım 
    XSetFont(display, gc, XLoadFont(display, "10x20"));

    // Sağlık ve dayanıklılık değerlerini tahsis edicez
    snprintf(health_text, sizeof(health_text), "Player 1: Heality Check: %d", character1->health);
    snprintf(stamina_text, sizeof(stamina_text), "Player 1: Stamina Check: %d", character1->stamina);

    // Sağlık ve dayanıklılık değerlerini ekrana yazdırıyoruz
    XDrawString(display, window, DefaultGC(display, 0), 10, 20, health_text, strlen(health_text));
    XDrawString(display, window, DefaultGC(display, 0), 10, 40, stamina_text, strlen(stamina_text));

    // ikinci karakterin değerlerini ekrana yazdıralım

    snprintf(health_text, sizeof(health_text), "Player 2: Heality Check: %d", character2->health);
    snprintf(stamina_text, sizeof(stamina_text), "Player 2: Stamina Check: %d", character2->stamina);

    //XDrawString(display, window, DefaultGC(display, 0), 10, 60, health_text, strlen(health_text));
    //XDrawString(display, window, DefaultGC(display, 0), 10, 80, stamina_text, strlen(stamina_text));

    // ikinci karakterin değerlerini ekrana yazdıralım ama sağ tarafa yazdıralım hesabı bunlara göre yapalım = #define WINDOW_WIDTH 1920
    //#define WINDOW_HEIGHT 1080

    XDrawString(display, window, DefaultGC(display, 0), WINDOW_WIDTH - 290, 20, health_text, strlen(health_text));
    XDrawString(display, window, DefaultGC(display, 0), WINDOW_WIDTH - 290, 40, stamina_text, strlen(stamina_text));
    
}

void
    load_character_animations(Display *display, t_characters *character)
{
    XGCValues       values;
    XpmAttributes   attributes;
    int             i;
    int             status;

    i = 0;
    attributes.valuemask = XpmReturnPixels | XpmReturnExtensions;
    while (i < sizeof(filenames) / sizeof(filenames[0]))
    {
        status = XpmReadFileToPixmap(display, DefaultRootWindow(display), filenames[i],
                                          &character->anim[i], &character->mask[i], &attributes);
        if (status != XpmSuccess)
        {
            fprintf(stderr, "Error loading XPM file '%s': %s\n", filenames[i], XpmGetErrorString(status));
            exit(1);
        }
        if (i == 0)
        {
            character->width = attributes.width;
            character->height = attributes.height;
        }
        character->gc[i] = XCreateGC(display, DefaultRootWindow(display), 0, &values);
        XSetClipMask(display, character->gc[i], character->mask[i]);
        XSetClipOrigin(display, character->gc[i], 0, 0);
        i++;
    }
    character->frame_delay = 8;
}

void
    render_character(Display *display, t_characters *character, Window window)
{
    Pixmap currentAnim;
    int status;
    GC gc;

    if (character->direct.isFire)
    {
        currentAnim = (character->lastDirection == 'L') ? character->anim[6] : character->anim[0];
        status = (character->lastDirection == 'L') ? 6 : 0;
    }
    else if (character->velocityY < 0)
    {
        currentAnim = character->anim[8];
        status = 8;
    }
    else if (character->velocityY > 0)
    {
        currentAnim = character->anim[2];
        status = 2;
    }
    else if (character->direct.isLeft)
    {
        currentAnim = character->anim[9 + (character->index % 3)];
        status = 9 + (character->index % 3);
    }
    else if (character->direct.isRight)
    {
        currentAnim = character->anim[3 + (character->index % 3)];
        status = 3 + (character->index % 3);
    }
    else
    {
        currentAnim = (character->lastDirection == 'L') ? character->anim[7] : character->anim[1];
        status = (character->lastDirection == 'L') ? 7 : 1;
    }
    gc = character->gc[status];
    XSetClipMask(display, gc, character->mask[status]);
    XSetClipOrigin(display, gc, character->coord.playerX, character->coord.playerY);
    XFillRectangle(display, window, character->gc[status], 
                   character->coord.playerX, character->coord.playerY, 
                   character->width, character->height);
    if (currentAnim)
    {
        XCopyArea(display, currentAnim, window, gc,
                  0, 0, character->width, character->height,
                  character->coord.playerX, character->coord.playerY);
    }
}

void
    loop(Display *display, Window window, t_characters *one, t_characters *two)
{
    XEvent event;
    while (true)
    {
        while (XPending(display))
        {
            XNextEvent(display, &event);
            if (event.type == KeyPress)
                handleKeyPress(&event.xkey, one, two);
            else if (event.type == KeyRelease)
                handleKeyRelease(&event.xkey, one, two);
        }
        update_animation(one, display, window);
        update_animation(two, display, window);
        check_health_stamina(one, two);
        XClearWindow(display, window);
        render_character(display, one, window);
        render_character(display, two, window);
        render_health_stamina(display, window, one, two);
        XFlush(display);
        usleep(16667); // FPS ayarı yaklaşık 60 FPS
    }
}

void
    game_init_functions(t_game *game)
{
    game->display = XOpenDisplay(NULL);
    if (game->display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    game->screen = DefaultScreen(game->display);
    game->window = XCreateSimpleWindow(game->display, RootWindow(game->display, game->screen),
                                       0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                       BlackPixel(game->display, game->screen),
                                       BlackPixel(game->display, game->screen));
    XSelectInput(game->display, game->window, KeyPressMask | KeyReleaseMask);
    XMapWindow(game->display, game->window);
    game->one = malloc(sizeof(t_characters));
    game->two = malloc(sizeof(t_characters));
    memset(game->one, 0, sizeof(t_characters));
    memset(game->two, 0, sizeof(t_characters));

    game->one->coord.playerX = 100;
    // game->one->coord.playerY = GROUND_LEVEL;
    game->two->coord.playerX = 300;
    // game->two->coord.playerY = GROUND_LEVEL;
    game->one->health = 100;   // Başlangıç sağlığı
    game->one->stamina = 100;  // Başlangıç dayanıklılığı
    game->two->health = 100;   // Başlangıç sağlığı
    game->two->stamina = 100;
}

int
    main(void)
{
    t_game game;

    game_init_functions(&game);
    load_character_animations(game.display, game.one);
    load_character_animations(game.display, game.two);
    loop(game.display, game.window, game.one, game.two);
    free(game.one);
    free(game.two);
    XCloseDisplay(game.display);
    return (0);
}