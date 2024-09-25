#include <iostream>
#include "vec3.hpp"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center; // Ray'in başlangıç noktası ile küre merkezi arasındaki vektör
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius; // Oc'un uzunluğunun karesi - küre yarıçapının karesi
    auto discriminant = b * b - 4 * a * c; // Diskriminant hesaplama
    return (discriminant >= 0); // Diskriminant sıfır veya pozitifse çarpışma var demektir
}
color ray_color(const ray& r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r)) { // Küre merkezi (0, 0, -1) ve yarıçapı 0.5
        return color(1, 0, 0); // Kırmızı renk
    }
    vec3 unit_direction = unit_vector(r.direction()); // Işın yönünü normalize et
    auto t = 0.5 * (unit_direction.y() + 1.0); // Y yönüne göre bir değer hesapla
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // Gradyan mavi-beyaz
}

int main() {
    // Görüntü ayarları
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    // Görüntü dosyası başlığı
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Ray oluşturma
    for (int j = image_height - 1; j >= 0; j--) {
        for (int i = 0; i < image_width; i++) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(point3(0, 0, 0), vec3(u * 2.0 - 1.0, v * 2.0 - 1.0, -1)); // Ray'i merkezden başlat
            color pixel_color = ray_color(r); // Piksel rengini al
            write_color(std::cout, pixel_color); // Rengi yaz
        }
    }
}
