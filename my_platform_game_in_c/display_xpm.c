#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;
    GC gc;
    XGCValues values;

    // X11 display'ini aç
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    screen = DefaultScreen(display);

    // Pencere oluştur
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 300, 300, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    // Olayları dinle
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // XPM resmini yükle
    Pixmap pixmap, mask;
    XpmAttributes attributes;
    attributes.valuemask = XpmReturnPixels | XpmReturnExtensions; // Şeffaflık için gerekli ayar

    int status = XpmReadFileToPixmap(display, window, "example.xpm", &pixmap, &mask, &attributes);
    if (status != XpmSuccess) {
        fprintf(stderr, "Failed to load example.xpm\n");
        return 1;
    }

    // Grafik bağlamını oluştur (GC)
    gc = XCreateGC(display, window, 0, &values);

    // Olay döngüsü
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Pencere çizildiğinde XPM'i maskesiyle beraber çiz
            XSetClipMask(display, gc, mask);
            XSetClipOrigin(display, gc, 50, 50);  // XPM'in pozisyonu
            XCopyArea(display, pixmap, window, gc, 0, 0, 64, 64, 64, 50);
        }
        if (event.type == KeyPress)
            break; // Bir tuşa basıldığında çık
    }

    // Temizleme
    XFreeGC(display, gc);
    XFreePixmap(display, pixmap);
    XFreePixmap(display, mask);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
