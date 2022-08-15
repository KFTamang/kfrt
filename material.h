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
            auto scatter_direction = refract(unit_direction, rec.normal, refraction_ratio);
            scattered = Ray(rec.p, scatter_direction);
            attenuation = Color(1, 1, 1);
            return true;
        }

    private:
        double ir;
};
