#include "kfrt.h"
#include "hittable.h"

class Sphere : public Hittable{
    public:
        Sphere(){}
        Sphere(Point3 cen, double r, shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m){};

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    private:
        Point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0){
        return false;
    }
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max){
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.mat_ptr = mat_ptr;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_surface_normal(r, outward_normal);
    return true;
}
