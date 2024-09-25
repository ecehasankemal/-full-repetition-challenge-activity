#include <stdio.h>
#include <math.h>

typedef struct
{
    double e[3];
} vec3;


double
    my_sqrt(double number)
{
    if (number < 0)
        return -1; // Negatif sayıların karekökü tanımsızdır

    double tolerance = 0.000001; // Hassasiyet seviyesi
    double guess = number / 2.0; // Başlangıç tahmini
    double difference;

    do
    {
        double new_guess = (guess + number / guess) / 2.0; // Newton-Raphson adımı
        difference = new_guess - guess;
        if (difference < 0)
            difference = -difference; // Mutlak fark
        guess = new_guess;
    } while (difference > tolerance); // İstediğimiz hassasiyete ulaşana kadar devam et

    return guess;
}

vec3
    vec3_new(double e0, double e1, double e2)
{
    vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

double
    vec3_x(vec3 v)
{
    return v.e[0];
}

double
    vec3_y(vec3 v)
{
    return v.e[1];
}

double
    vec3_z(vec3 v)
{
    return v.e[2];
}

vec3
    vec3_neg(vec3 v)
{
    return vec3_new(-v.e[0], -v.e[1], -v.e[2]);
}

double
    vec3_get(vec3 v, int i)
{
    return v.e[i];
}

void
    vec3_set(vec3 *v, int i, double val)
{
    v->e[i] = val;
}

vec3
    vec3_add(vec3 v, vec3 u)
{
    v.e[0] += u.e[0];
    v.e[1] += u.e[1];
    v.e[2] += u.e[2];
    return v;
}

vec3
    vec3_add2(vec3 v, double t)
{
    return vec3_new(v.e[0] + t, v.e[1] + t, v.e[2] + t);
}

vec3
    vec3_mul(vec3 v, double t)
{
    v.e[0] *= t;
    v.e[1] *= t;
    v.e[2] *= t;
    return v;
}

vec3
    vec3_div(vec3 v, double t)
{
    return vec3_mul(v, 1 / t);
}

double
    vec3_length_squared(vec3 v)
{
    return vec3_x(v) * vec3_x(v) + vec3_y(v) * vec3_y(v) + vec3_z(v) * vec3_z(v);
}

double
    vec3_length(vec3 v)
{
    return my_sqrt(vec3_length_squared(v));
}


typedef vec3 point3;

double
    vec3_dot(vec3 u, vec3 v)
{
    return vec3_x(u) * vec3_x(v) + vec3_y(u) * vec3_y(v) + vec3_z(u) * vec3_z(v);
}

inline vec3
    vec3_cross(vec3 u, vec3 v)
{
    return vec3_new(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

typedef vec3 color;

void
    write_color(int fd, color pixel_color)
{
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    // [0, 255] aralığında renk değerlerini ayarlayacagaız
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    // pixel renklerini dışa yazdır

    dprintf(fd, "%d %d %d\n", rbyte, gbyte, bbyte);
}

typedef struct
{
    point3 orig;
    vec3 dir;
} ray;

ray
    ray_new(point3 origin, vec3 direction)
{
    ray r;
    r.orig = origin;
    r.dir = direction;
    return r;
}

point3
    ray_origin(ray r)
{
    return r.orig;
}

vec3
    ray_direction(ray r)
{
    return r.dir;
}

point3
    ray_at(ray r, double t)
{
    // P(t) = A + tb
    return vec3_add(ray_origin(r), vec3_mul(ray_direction(r), t));
    // vec3_mul = t yi b nin içindeki tüm değerler işe çarpar
}

vec3
    vec3_sub(vec3 u, point3 v)
{
    return vec3_new(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

double
    hit_sphere(point3 center, double radius, ray r)
{
    vec3 oc = vec3_sub(ray_origin(r), center);
    double a = vec3_length_squared(ray_direction(r));
    double half_b = vec3_dot(oc, ray_direction(r));
    double c = vec3_length_squared(oc) - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return -1.0;
    else
        return (-half_b - my_sqrt(discriminant)) / a;
    //return discriminant > 0;
}

vec3
    vec3_unit_vector(vec3 v)
{
    return vec3_div(v, vec3_length(v));
}

// BU FONKSİYONA DÖN BİR BAK
color
    ray_color(ray r)
{
    point3 sphere_center = vec3_new(0, 0, -1);
    double sphere_radius = 0.5;

    // küre ile kesişimi kontrol ediyor.
    double t = hit_sphere(sphere_center, sphere_radius, r);
    if (t > 0.0)
    {
        vec3 N = vec3_unit_vector(vec3_sub(ray_at(r, t), sphere_center));
        return vec3_mul(vec3_new(N.e[0] + 1, N.e[1] + 1, N.e[2] + 1), 0.5);
        //return vec3_new(1.0, 0.0, 0.0);  // kırmızı
    }
    vec3 unit_direction = vec3_unit_vector(ray_direction(r));
    t = 0.5 * (vec3_y(unit_direction) + 1.0);
    return vec3_add(vec3_mul(vec3_new(1.0, 1.0, 1.0), 1.0 - t), vec3_mul(vec3_new(0.5, 0.7, 1.0), t));
}
typedef struct
{
    double aspect_ratio;
    int image_width;
    int image_height;
    double focal_length;
    double viewport_height;
    double viewport_width;
    point3 camera_center;
    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 viewport_upper_left;
    vec3 pixel00_loc;
}               t_program;

void
    t_program_init(t_program *program)
{
    program->aspect_ratio = 16.0 / 9.0; // bu daha sonra otamatik yapılacak. yani aspect_ratio = genişlik/yükseklik
    program->image_width = 400; // bu da daha sonra otamatik yapılacak. yani image_width = 400 olacak.
    program->image_height = (int)(program->image_width / program->aspect_ratio);
    program->image_height = (program->image_height < 1) ? 1 : program->image_height;
    program->focal_length = 1.0;
    program->viewport_height = 2.0;
    program->viewport_width = program->viewport_height * (double)(program->image_width / (double)program->image_height);
    program->camera_center = vec3_new(0, 0, 0);
    program->viewport_u = vec3_new(program->viewport_width, 0, 0);
    program->viewport_v = vec3_new(0, -program->viewport_height, 0);
    program->pixel_delta_u = vec3_div(program->viewport_u, program->image_width);
    program->pixel_delta_v = vec3_div(program->viewport_v, program->image_height);
    program->viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(program->camera_center, vec3_new(0, 0, program->focal_length)), vec3_div(program->viewport_u, 2)),
                                        vec3_div(program->viewport_v, 2));
    program->pixel00_loc = vec3_add(program->viewport_upper_left, vec3_mul(vec3_add(program->pixel_delta_u, program->pixel_delta_v), 0.5));
}
int
    main(void)
{
    t_program   program;
    int         index;
    int         index2;

    index = 0;
    index2 = 0;
    t_program_init(&program);
    // render
    dprintf(1, "P3\n%d %d\n255\n", program.image_width, program.image_height);
    while(index < program.image_height)
    {
        fprintf(stderr, "\rScanlines remaining: %d ", program.image_height - index);
        while(index2 < program.image_width)
        {
            vec3 pixel_center = vec3_add(program.pixel00_loc, vec3_add(vec3_mul(program.pixel_delta_u, index2), vec3_mul(program.pixel_delta_v, index)));
            vec3 ray_direction = vec3_sub(pixel_center, program.camera_center);
            ray r = ray_new(program.camera_center, ray_direction);
            color pixel_color = ray_color(r);
            write_color(1, pixel_color);
            index2++;
        }
        index2 = 0;
        index++;
    } 
    fprintf(stderr, "\rDone.                 \n");
    return (0);
}

