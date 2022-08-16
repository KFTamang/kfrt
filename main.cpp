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

HittableList make_random_world(){
    HittableList world;
    auto material_ground = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, material_ground));
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                std::cerr << a << " " << b << "\n";
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main(int argc, char** argv){
    if (argc != 4){
        std::cerr << "Error: 2 arguments must be supplied.\n";
        return 1;
    }
    const auto aspect_ratio = 16.0 / 9.0;
    const auto vfov = 20.0; 
    const int image_width = atof(argv[1]);
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = atoi(argv[2]);
    const int max_recursion = atoi(argv[3]);

    // camera
    Camera cam(Point3(11, 5 , 5), Point3(0, 0, 0), vec3(0, 1, 0), vfov, aspect_ratio);

    // world
    auto world = make_random_world();

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