#include "vec3.hpp"
#include "color.h"
#include "ray.h"

/*
    1.  Pixelden "göz" ile ışını hesaplayın yani gözümüz
        bizim A Noktamız olacak ve ışınımız ise b vektörümüz olacak.
        yani formül şu şekilde olacak: P(t) = A + tb
        bu formuldeki A bizim gözümüz olacak ve b ise ışınımız olacak.

    2.  "Işının hangi nesnelerle kesiştiğini belirle." yani burda
        şu işlemi yapacağız: Nesnelerle kesişim noktalarını bulacağız. bunu da
        şu şekilde yapacağız: 
    
    3.  "Gölgeleme" yani gölgeleme işlemini yapacağız. yani gölgeleme işlemi
        şu şekilde yapılacak: Bir ışık kaynağından gelen ışınlar nesnelerin
        üzerine düşer ve bu ışınlar nesnelerin üzerine düştüğünde nesnelerin
        üzerinde gölgeler oluşturur. bu gölgeleri oluşturmak için ışınların
        nesnelerin üzerine düşüp düşmediğini kontrol etmemiz gerekiyor.
        bu işlemi de şu şekilde yapacağız: Bir ışık kaynağından gelen ışınlar
        nesnelerin üzerine düşer ve bu ışınlar nesnelerin üzerine düştüğünde
        nesnelerin üzerinde gölgeler oluşturur. bu gölgeleri oluşturmak için
        ışınların nesnelerin üzerine düşüp düşmediğini kontrol etmemiz gerekiyor.
        bu işlemi de şu şekilde yapacağız: Bir ışık kaynağından gelen ışınlar
        nesnelerin üzerine düşer ve bu ışınlar nesnelerin üzerine düştüğünde
        nesnelerin üzerinde gölgeler oluşturur. bu gölgeleri oluşturmak için
        ışınların nesnelerin üzerine düşüp düşmediğini kontrol etmemiz.

        en boy oranı 16:9 seçecegiz
        16:9 = 256:144

        formulumuz su sekilde olacak = genişlik/yükseklik = 16/9 = 1.7778
*/

bool
      hit_sphere(const point3& center, double radius, const ray& r)
{
           vec3 oc = r.origin() - center; // Işın başlangıç noktası ile küre merkezi arasındaki vektör
           auto a = dot(r.direction(), r.direction());
           auto b = 2.0 * dot(oc, r.direction());
           auto c = dot(oc, oc) - radius * radius;
           auto discriminant = b * b - 4 * a * c;
           return (discriminant > 0); // 0'dan büyükse sadece bir kesişim noktası var
}

color
      ray_color(const ray& r)
{
           // Kürenin merkezi ve yarıçapı
           point3 sphere_center(0, 0, -1);
           double sphere_radius = 0.5;

           // Eğer ışın küre ile kesişiyorsa kırmızı renk döndür
           if (hit_sphere(sphere_center, sphere_radius, r)) {
                   return color(1.0, 0.0, 0.0); // Kırmızı
           }

           // Aksi halde arka plan rengi
           vec3 unit_direction = unit_vector(r.direction());
           auto t = 0.5 * (unit_direction.y() + 1.0);
           return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int
      main()
{
           // Image
           auto aspect_ratio = 16.0 / 9.0;
           int image_width = 400;

           // Görüntü yüksekliğini hesaplayın ve en az 1 olmasını sağlayın.
           int image_height = int(image_width / aspect_ratio);
           image_height = (image_height < 1) ? 1 : image_height;

           // Kamera
           auto focal_length = 1.0;
           auto viewport_height = 2.0;
           auto viewport_width = viewport_height * (double(image_width) / image_height);
           auto camera_center = point3(0, 0, 0);

           // Yatay ve dikey görüntü kenarları boyunca vektörleri hesaplayın.
           auto viewport_u = vec3(viewport_width, 0, 0);
           auto viewport_v = vec3(0, -viewport_height, 0);

           // Pikselden piksele yatay ve dikey delta vektörlerini hesaplayın.
           auto pixel_delta_u = viewport_u / image_width;
           auto pixel_delta_v = viewport_v / image_height;

           // Üst sol pikselin konumunu hesaplayın.
           auto viewport_upper_left = camera_center
                                   - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
           auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

           // Render
           std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

           for (int j = 0; j < image_height; j++) {
                   std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                   for (int i = 0; i < image_width; i++) {
                           auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                           auto ray_direction = pixel_center - camera_center;
                           ray r(camera_center, ray_direction);

                           color pixel_color = ray_color(r);
                           write_color(std::cout, pixel_color);
                   }
           }

           std::clog << "\rDone.                 \n";
}


/*
blendedValue=(1−a)⋅startValue+a⋅endValueblendedValue=(1−a)⋅startValue+a⋅endValue

bu formülde a 0 ile 1 arasında bir değer alır ve bu değer 0 ise startValue değeri alınır
bu da şu işe yarar : bu bir triktir ve bu trik sayesinde 0 ile 1 arasında bir değer alır ve bu değer 0 ise startValue değeri alınır

örnek olarak benim a değişkenim olsun ve değeri 1 olsun. a = 1.0 : bu da mavi değerine tekabul etsin.
ben a = 0 verdiğimde ise beyaz olması yönünde istek ve arzum var diyelim.
bu durumda a = 0 olacak ve bu da beyaz olacak demektir.

ben bu ikisi arasında bir karışım istiyorum diyelim bu durumda örnek olarak a = 0.5
                                olacak ve bu da mavi ve beyazın karışımı olacak demektir.
*/
// küreyi çizmek için bir fonksiyon yazacağız
// x^2 + y^2 + z^2 = r^2 bu formülü kullanarak küreyi çizeceğiz.

// bizim yukarıdaki değerlerimiz ile bu formulu su sekilde kullanacagız (Cx−x)2+(Cy−y)2+(Cz−z)2=r2
// burada Cx, Cy ve Cz kameranın merkezi olacak ve x, y ve z ise kürenin merkezi olacak.

// (C−P)⋅(C−P)=(Cx−x)2+(Cy−y)2+(Cz−z)2 = r^2 burada 

// = (C−P)⋅(C−P)=r2