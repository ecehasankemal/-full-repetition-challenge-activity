#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void load_and_draw_character(Display *display, Window window, const char *filename, int x, int y) {
    Pixmap pixmap, mask;
    XpmAttributes attributes;
    attributes.valuemask = XpmReturnPixels | XpmReturnExtensions;
    GC gc;
    XGCValues values;

    int status = XpmReadFileToPixmap(display, window, filename, &pixmap, &mask, &attributes);
    if (status != XpmSuccess) {
        fprintf(stderr, "XPM dosyası '%s' yüklenirken hata oluştu: %s\n", filename, XpmGetErrorString(status));
        exit(1);
    }

    gc = XCreateGC(display, window, 0, &values);
    XSetClipMask(display, gc, mask);
    XSetClipOrigin(display, gc, x, y);
    XCopyArea(display, pixmap, window, gc, 0, 0, attributes.width, attributes.height, x, y);

    XFreePixmap(display, pixmap);
    XFreePixmap(display, mask);
    XFreeGC(display, gc);
}

int main(void) {
    Display *display;
    Window window;
    int screen;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "XOpenDisplay failed\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1,
                                 BlackPixel(display, screen), BlackPixel(display, screen));
    XSelectInput(display, window, ExposureMask);
    XMapWindow(display, window);

    const char *filenames[] = {
        "megafire.xpm", "megaidle.xpm", "megajump.xpm", 
        "megawalk.xpm", "megawalk2.xpm", "megawalk3.xpm",
        "megafirel.xpm", "megaidlel.xpm", "megajumpl.xpm",
        "megawalkl.xpm", "megawalkl2.xpm", "megawalkl3.xpm"
    };

    while (1) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == Expose) {
            int x = 50, y = 50;
            for (int i = 0; i < sizeof(filenames) / sizeof(filenames[0]); i++) {
                load_and_draw_character(display, window, filenames[i], x, y);
                x += 100; // Karakterleri yatayda aralıklı olarak yerleştir
                if (x + 64 > WINDOW_WIDTH) { // Satır sonuna gelince alt satıra geç
                    x = 50;
                    y += 100;
                }
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}