#pragma once
#include "kfrt.h"
#include "hittable.h"

class Material{
    public:
        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material{
    public:
        Lambertian(const Color& a) : albedo(a){}
        
        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override{
            auto scatter_direction = rec.normal + random_unit_vector();
            if (scatter_direction.is_near_zero()){
                // catch degeneration of scatter direction
                scatter_direction = rec.normal;
            }
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;
};

class Metal : public Material{
    public:
        Metal(const Color& a, double f) : albedo(a){
            fuzzyness = clamp(f, 0, 1);
        }
        
        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override{
            auto scatter_direction = reflect(incident.direction(), rec.normal);
            if (scatter_direction.is_near_zero()){
                // catch degeneration of scatter direction
                scatter_direction = rec.normal;
            }
            scattered = Ray(rec.p, scatter_direction + fuzzyness * random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scatter_direction, rec.normal) > 0);
        }

    private:
        Color albedo;
        double fuzzyness;
};

class Dielectric : public Material{
    public:
        Dielectric(double index_of_refraction): ir(index_of_refraction){}
        
        virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& attenuation, Ray& scattered) const override{
            auto unit_direction = unit_vector(incident.direction());
            auto refraction_ratio = rec.front_surface ? (1.0/ir) : (ir);
            auto cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0); 
            auto sin_theta = sqrt(1 - cos_theta * cos_theta);
            bool can_refract = (refraction_ratio * sin_theta <= 1.0);
            vec3 scatter_direction;
            if (can_refract && (reflectance(cos_theta, refraction_ratio) < random_double())){
                scatter_direction = refract(unit_direction, rec.normal, refraction_ratio);
            }else{
                scatter_direction = reflect(unit_direction, rec.normal);
            }
            scattered = Ray(rec.p, scatter_direction);
            attenuation = Color(1, 1, 1);
            return true;
        }

    private:
        double ir;

        static double reflectance(double cos_theta, double refraction_ratio){
            auto r0 = (1 - refraction_ratio) / (1 + refraction_ratio);
            r0 = r0 + r0;
            return r0 + (1 - r0) * pow((1-cos_theta), 5);
        }

};
