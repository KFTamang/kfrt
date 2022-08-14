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

