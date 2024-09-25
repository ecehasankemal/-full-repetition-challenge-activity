#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Midpoint Circle Algorithm için bir yardımcı fonksiyon
void draw_circle(Display *display, Window window, GC gc, int x_center, int y_center, int radius) {
    int x = radius;
    int y = 0;
    int decision_over2 = 1 - x;  // Karar değişkeni (midpoint decision variable)

    while (x >= y) {
        // Her sekizinci dilimi çiz
        XDrawPoint(display, window, gc, x_center + x, y_center + y);
        XDrawPoint(display, window, gc, x_center + y, y_center + x);
        XDrawPoint(display, window, gc, x_center - y, y_center + x);
        XDrawPoint(display, window, gc, x_center - x, y_center + y);
        XDrawPoint(display, window, gc, x_center - x, y_center - y);
        XDrawPoint(display, window, gc, x_center - y, y_center - x);
        XDrawPoint(display, window, gc, x_center + y, y_center - x);
        XDrawPoint(display, window, gc, x_center + x, y_center - y);
        y++;

        if (decision_over2 <= 0) {
            decision_over2 += 2 * y + 1;
        } else {
            x--;
            decision_over2 += 2 * (y - x) + 1;
        }
    }
}

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;
    GC gc;

    // X11 bağlantısını aç
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "X Açılırken hata oluştu.\n");
        exit(1);
    }

    screen = DefaultScreen(display);

    // Pencereyi oluştur
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 600, 1,
                                  BlackPixel(display, screen), WhitePixel(display, screen));

    // Pencereyi göster
    XMapWindow(display, window);

    // Olaylar için ilgilenilenler ayarlanıyor
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Pencere kapatıldığında işlem yapmak için
    Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDelete, 1);

    // GC (Graphics Context) oluştur
    gc = XCreateGC(display, window, 0, NULL);

    // Olay döngüsünü başlat
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Pencere yeniden çizildiğinde daire çizimi yapılacak
            XSetForeground(display, gc, BlackPixel(display, screen));
            draw_circle(display, window, gc, 400, 300, 100); // Orta noktası (400, 300) ve yarıçapı 100 olan daire çizimi
        }
        if (event.type == ClientMessage) {
            if ((Atom)event.xclient.data.l[0] == wmDelete) {
                break; // Pencere kapatıldığında çık
            }
        }
        if (event.type == KeyPress) {
            break; // Bir tuşa basıldığında çık
        }
    }

    // Temizleme
    XFreeGC(display, gc);
    XCloseDisplay(display);
    return 0;
}

// bu kodun mantıgını anlamak için alttaki youtube videosunu izleyebilirsiniz.
// ben de oradan daha detaylı tahkik edeceğim.
// link = https://www.youtube.com/watch?v=hpiILbMkF9w  (The Midpoint Circle Algorithm - Computerphile)
