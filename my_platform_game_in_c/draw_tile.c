#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_SIZE 100

Pixmap load_xpm(Display *display, Window window, const char *filename, Pixmap *mask) {
    Pixmap pixmap;
    XpmAttributes attributes;
    attributes.valuemask = XpmReturnPixels | XpmReturnExtensions;

    int status = XpmReadFileToPixmap(display, window, filename, &pixmap, mask, &attributes);
    if (status != XpmSuccess) {
        fprintf(stderr, "XPM dosyası '%s' yüklenirken hata oluştu: %s\n", filename, XpmGetErrorString(status));
        exit(1);
    }

    return pixmap;
}

void draw_tile(Display *display, Window window, GC gc, int x, int y, char tile, Pixmap wall, Pixmap character, Pixmap empty, Pixmap mask) {
    Pixmap pixmap;
    switch (tile) {
        case '1': // Duvar
            pixmap = wall;
            break;
        case 'C': // Engel
            pixmap = character;
            break;
        case '0': // Boşluk
        default:
            pixmap = empty;
            break;
    }

    XSetClipMask(display, gc, mask);
    XSetClipOrigin(display, gc, x, y);
    XCopyArea(display, pixmap, window, gc, 0, 0, TILE_SIZE, TILE_SIZE, x, y);
}

void draw_map(Display *display, Window window, GC gc, Pixmap wall, Pixmap character, Pixmap empty, Pixmap mask) {
    const char *map[] = {
        "1111111111111111111111111111111111",
        "1E0000000000000C00000C000000000001",
        "1010010100100000101001000000010101",
        "1010010010101010001001000000010101",
        "1P0000000C00C0000000000000000000C1",
        "1111111111111111111111111111111111"
    };

    int rows = sizeof(map) / sizeof(map[0]);
    int cols = strlen(map[0]);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            draw_tile(display, window, gc, x * TILE_SIZE, y * TILE_SIZE, map[y][x], wall, character, empty, mask);
        }
    }
}

int main(void) {
    Display *display;
    Window window;
    int screen;
    GC gc;
    Pixmap wall, character, empty, mask;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "XOpenDisplay failed\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);

    // XPM dosyalarını yükle
    wall = load_xpm(display, window, "grass.xpm", &mask);
    character = load_xpm(display, window, "megaidle.xpm", &mask);
    empty = load_xpm(display, window, "cgirl.xpm", &mask);

    while (1) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == Expose) {
            draw_map(display, window, gc, wall, character, empty, mask);
        }
    }

    XFreePixmap(display, wall);
    XFreePixmap(display, character);
    XFreePixmap(display, empty);
    XFreeGC(display, gc);
    XCloseDisplay(display);
    return 0;
}