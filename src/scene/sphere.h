#pragma once

#include "hittable.h"
#include "../math/vector.h"
#include <memory>

class Sphere : public Hittable {
public:
    Point3 center;
    float radius;
    std::shared_ptr<Material> mat_ptr;

    Sphere() {}
    Sphere(Point3 cen, float r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    Vec3 oc = r.origin - center;
    float a = r.direction.length_squared();
    float half_b = oc.dot(r.direction);
    float c = oc.length_squared() - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if (discriminant > 0) {
        float root = sqrt(discriminant);
        float temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            Vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            Vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
