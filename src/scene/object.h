#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

class Object : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    Object() {}
    Object(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

bool Object::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}