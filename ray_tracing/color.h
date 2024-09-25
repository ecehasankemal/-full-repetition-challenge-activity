#ifndef COLOR_H
# define COLOR_H

# include "vec3.hpp"

using color = vec3;

void
    write_color(std::ostream& out, const color& pixel_color)
{
    auto    r = pixel_color.x();
    auto    g = pixel_color.y();
    auto    b = pixel_color.z();

    // [0, 255] aralığında renk değerlerini ayarlayacagaız
    int     rbyte = static_cast<int>(255.999 * r);
    int     gbyte = static_cast<int>(255.999 * g);
    int     bbyte = static_cast<int>(255.999 * b);

    // pixel renklerini dışa yazdır

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif