#include "kfrt.h"

class Camera{
    public:
        Camera(Point3 lookfrom, Point3 lookat, Point3 vup, double vfov, double aspect_ratio){
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2); 
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);
            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }

        Ray get_ray(double s, double t){
            return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
        }

    private:
        Point3 origin;
        vec3 horizontal;
        vec3 vertical;
        vec3 lower_left_corner;
};