#pragma once
#include "kfrt.h"

struct HitRecord{
    Point3 p;
    vec3 normal;
    double t;
    bool front_surface;

    inline void set_surface_normal(const Ray& r, const vec3& outward_normal){
        front_surface = dot(r.direction(), outward_normal) < 0;
        normal = front_surface ? outward_normal : -outward_normal;
    }

};

class Hittable{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};