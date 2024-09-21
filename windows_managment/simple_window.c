#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;

    // X11 bağlantısını aç
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "X Açılırken hata oluştu.\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    // Pencereyi oluştur
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 400, 1,
                                  BlackPixel(display, screen), WhitePixel(display, screen));

    // Pencereyi göster
    XMapWindow(display, window);

    // Olay döngüsünü başlat
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Pencere yeniden çizildiğinde yapılacak işlemler
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 360, 160);
        }
        if (event.type == ClientMessage)
        {
            if ((Atom)event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False))
                break; // Pencere kapatıldığında çık
        }
        if (event.type == KeyPress) {
            break; // Bir tuşa basıldığında çık
        }
    }

    // X11 bağlantısını kapat
    XCloseDisplay(display);
    return 0;
}

