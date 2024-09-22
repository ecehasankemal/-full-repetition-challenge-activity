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

void handleKeyPress(XKeyEvent *event, t_characters *player1, t_characters *player2) {
    KeySym key = XLookupKeysym(event, 0);
    switch (key) {
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
            if (player1->isOnGround) {
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
            if (player2->isOnGround) {
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

void handleKeyRelease(XKeyEvent *event, t_characters *player1, t_characters *player2) {
    KeySym key = XLookupKeysym(event, 0);
    switch (key) {
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
    XClearArea(display, window, character->coord.playerX, character->coord.playerY, character->width, character->height, False);

    if (character->frame_counter >= character->frame_delay) {
        character->frame_counter = 0;

        if (character->direct.isFire)
            character->index = (character->index + 1) % 3;
        else if (character->direct.isLeft) {
            character->index = (character->index + 1) % 3 + 9;
            character->lastDirection = 'L';
        }
        else if (character->direct.isRight) {
            character->index = (character->index + 1) % 3 + 3;
            character->lastDirection = 'R';
        }
        else {
            character->index = 0;
        }
    } else {
        character->frame_counter++;
    }

    character->speed = character->direct.isRun ? 6 : 4;

    if (character->direct.isLeft)
        character->coord.playerX -= character->speed;
    if (character->direct.isRight)
        character->coord.playerX += character->speed;

    if (character->coord.playerX < 0)
        character->coord.playerX = 0;
    if (character->coord.playerX > WINDOW_WIDTH - character->width)
        character->coord.playerX = WINDOW_WIDTH - character->width;

    if (!character->isOnGround) {
        character->velocityY += GRAVITY;
        character->coord.playerY += character->velocityY;

        if (character->coord.playerY >= GROUND_LEVEL) {
            character->coord.playerY = GROUND_LEVEL;
            character->isOnGround = true;
            character->velocityY = 0;
        } else {
            character->isOnGround = false; // Zemin kontrolü
        }
    }
}

void load_character_animations(Display *display, t_characters *character) {
    const char *filenames[] = {
        "megafire.xpm", "megaidle.xpm", "megajump.xpm",
        "megawalk.xpm", "megawalk2.xpm", "megawalk3.xpm",
        "megafirel.xpm", "megaidlel.xpm", "megajumpl.xpm",
        "megawalkl.xpm", "megawalkl2.xpm", "megawalkl3.xpm"
    };

    XGCValues values;
    XpmAttributes attributes;
    attributes.valuemask = XpmReturnPixels | XpmReturnExtensions;

    for (int i = 0; i < sizeof(filenames) / sizeof(filenames[0]); i++) {
        int status = XpmReadFileToPixmap(display, DefaultRootWindow(display), filenames[i],
                                          &character->anim[i], &character->mask[i], &attributes);
        
        if (status != XpmSuccess) {
            fprintf(stderr, "Error loading XPM file '%s': %s\n", filenames[i], XpmGetErrorString(status));
            exit(1);
        }

        if (i == 0) {
            character->width = attributes.width;
            character->height = attributes.height;
        }

        character->gc[i] = XCreateGC(display, DefaultRootWindow(display), 0, &values);
        XSetClipMask(display, character->gc[i], character->mask[i]);
        XSetClipOrigin(display, character->gc[i], 0, 0);
    }
    character->frame_delay = 8;
}

void render_character(Display *display, t_characters *character, Window window) {
    Pixmap currentAnim;
    int status;

    if (character->direct.isFire) {
        currentAnim = (character->lastDirection == 'L') ? character->anim[6] : character->anim[0];
        status = (character->lastDirection == 'L') ? 6 : 0;
    } else if (character->velocityY < 0) {
        currentAnim = character->anim[8];
        status = 8;
    } else if (character->velocityY > 0) {
        currentAnim = character->anim[2];
        status = 2;
    } else if (character->direct.isLeft) {
        currentAnim = character->anim[9 + (character->index % 3)];
        status = 9 + (character->index % 3);
    } else if (character->direct.isRight) {
        currentAnim = character->anim[3 + (character->index % 3)];
        status = 3 + (character->index % 3);
    } else {
        currentAnim = (character->lastDirection == 'L') ? character->anim[7] : character->anim[1];
        status = (character->lastDirection == 'L') ? 7 : 1;
    }

    GC gc = character->gc[status];
    XSetClipMask(display, gc, character->mask[status]);
    XSetClipOrigin(display, gc, character->coord.playerX, character->coord.playerY);

    XFillRectangle(display, window, character->gc[status], 
                   character->coord.playerX, character->coord.playerY, 
                   character->width, character->height);

    if (currentAnim) {
        XCopyArea(display, currentAnim, window, gc,
                  0, 0, character->width, character->height,
                  character->coord.playerX, character->coord.playerY);
    } else {
        fprintf(stderr, "Current animation is NULL.\n");
    }
}
void loop(Display *display, Window window, t_characters *player1, t_characters *player2) {
    XEvent event;
    while (true) {
        while (XPending(display)) {
            XNextEvent(display, &event);
            if (event.type == KeyPress)
                handleKeyPress(&event.xkey, player1, player2);
            else if (event.type == KeyRelease)
                handleKeyRelease(&event.xkey, player1, player2);
        }
        update_animation(player1, display, window);
        update_animation(player2, display, window);
        render_character(display, player1, window);
        render_character(display, player2, window);
        XFlush(display);
        usleep(16667); // FPS ayarı (yaklaşık 60 FPS)
    }
}


int main() {
    t_game game;
    game.display = XOpenDisplay(NULL);
    if (!game.display) {
        fprintf(stderr, "Unable to open X display\n");
        return 1;
    }

    game.screen = DefaultScreen(game.display);
    game.window = XCreateSimpleWindow(game.display, RootWindow(game.display, game.screen),
                                       0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1,
                                       BlackPixel(game.display, game.screen),
                                       BlackPixel(game.display, game.screen));
    XSelectInput(game.display, game.window, ExposureMask | KeyPressMask | KeyReleaseMask);
    XMapWindow(game.display, game.window);

    game.one = malloc(sizeof(t_characters));
    game.two = malloc(sizeof(t_characters));
    memset(game.one, 0, sizeof(t_characters));
    memset(game.two, 0, sizeof(t_characters));

    game.one->coord.playerX = 100;  // Birinci karakter için
    game.one->coord.playerY = GROUND_LEVEL;  // Yerden başlama

    game.two->coord.playerX = 300;  // İkinci karakter için farklı bir konum
    game.two->coord.playerY = GROUND_LEVEL;  // Yerden başlama

    load_character_animations(game.display, game.one);
    load_character_animations(game.display, game.two);

    loop(game.display, game.window, game.one, game.two);

    free(game.one);
    free(game.two);
    XCloseDisplay(game.display);
    return 0;
}
