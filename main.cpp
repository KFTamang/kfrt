#include <iostream>
#include "kfrt.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"

Color ray_color(const Ray& r, Hittable& world){
    HitRecord rec;
    if (world.hit(r, 0, infinity, rec)){
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 -t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main(void){
    const auto aspect_ratio = 16.0 / 9.0; 
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 100;

    // camera
    Camera cam;

    // world
    auto world = HittableList();
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int j=image_height-1; j>=0; j--){
        std::cerr << "Scanline remaining:" << j << std::endl;
        for(int i=0; i < image_width; i++){
            Color pixel_color = Color(0, 0, 0);
            for(int k=0; k<sample_per_pixel; k++){
                auto u = double(i + random_double()) / (image_width - 1);
                auto v = double(j + random_double()) / (image_height - 1);
                auto r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);                
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }
    std::cerr << "Done\n";
    return 0;
}