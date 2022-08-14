#include <iostream>
#include "kfrt.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "material.h"

Color ray_color(const Ray& r, Hittable& object, int depth){
    if (depth <= 0){
        // reaching the recursion limit, returning black color
        return Color(0, 0, 0);
    }
    HitRecord rec;
    if (!object.hit(r, 0.001, infinity, rec)){
        // background
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 -t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
    // when hitting object
    Ray new_ray;
    Color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, new_ray)){
        return attenuation * ray_color(new_ray, object, depth - 1);
    }
    return Color(0, 0, 0);
}

int main(void){
    const auto aspect_ratio = 16.0 / 9.0; 
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 100;
    const int max_recursion = 50;

    // camera
    Camera cam;

    // world
    auto world = HittableList();
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<Metal>(Color(0.4, 0.7, 0.3));
    world.add(make_shared<Sphere>(Point3( 0,      0, -1), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3( 1,      0, -1), 0.5, material_right));
    world.add(make_shared<Sphere>(Point3(-1,    0.5, -1), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3( 0, -100.5, -1), 100, material_ground));

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
                pixel_color += ray_color(r, world, max_recursion);                
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }
    std::cerr << "Done\n";
    return 0;
}