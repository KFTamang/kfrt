#pragma once
#include "kfrt.h"
#include "hittable.h"
#include <vector>

using std::vector;

class HittableList : public Hittable{
    public:
        HittableList(){}
        HittableList(shared_ptr<Hittable> object){ add(object);};

        void clear(){objects.clear();}
        void add(shared_ptr<Hittable> object){
            objects.push_back(object);
        }
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    private:
        vector<shared_ptr<Hittable>> objects; 
};

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    auto closest_so_far = t_max;
    bool hit_anything = false;

    for(const auto& obj: objects){
        if (obj->hit(r, t_min, closest_so_far, temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}