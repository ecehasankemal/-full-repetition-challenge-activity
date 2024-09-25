#ifndef RAY_H
# define RAY_H

/*
    IŞIN NEDİR:
        IŞININN TANIMI NEDİR:
            Işın, bir başlangıç noktası ve bir yön vektörü olan bir doğru parçasıdır.
            P(t) = A + tb
            P: 3 boyutlu bir nokta
            A: Işının başlangıç noktası
            b: Işının yönü
            t: Işının uzunluğu

            kısaca t sıfır ise sonuç A olur yani başlangıç noktası.
            lakin t sıfır değil ise ışın yönüne yani b ile çarpım olarak eklenir.
            ve başlangıç noktasına eklenir bu da bize varış noktası yani P yi verir?
*/



# include "vec3.hpp"

class  ray
{
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }

        point3 at(double t) const
        {
            return orig + t * dir; // P(t) = A + tb
        }


    private:
        point3 orig;
        vec3 dir;
};

#endif