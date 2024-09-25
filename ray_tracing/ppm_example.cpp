#include <iostream>

int
    main(void)
{
    // Image işlemleri hakkında bazı değişkenler

    int image_width = 256;
    int image_height = 256;

    // Image dosyası başlığı // render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Image dosyası içeriği

    int i, j;
    
    i = 0;
    while (i < image_height)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        j = 0;
        while (j < image_width)
        {
            float r = float(j) / (image_width - 1);
            float g = float(i) / (image_height - 1);
            float b = 0.25;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << "\n";

            j++;
        }
        i++;
    }
    std::clog << "\rDone.                 \n";
}