#pragma once

#include "hittable.h"
#include "material.h"
#include "../math/vector.h"
#include <memory>

class RectangularPrism : public Hittable {
public:
    Point3 center;
    float width, height, depth;
    std::shared_ptr<Material> mat_ptr;

    RectangularPrism() {}
    RectangularPrism(Point3 cen, float w, float h, float d, std::shared_ptr<Material> m)
        : center(cen), width(w), height(h), depth(d), mat_ptr(m) {}

    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

bool RectangularPrism::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    // Implémentation simplifiée pour vérifier les intersections avec le pavé droit
    Point3 min = center - Vec3(width / 2, height / 2, depth / 2);
    Point3 max = center + Vec3(width / 2, height / 2, depth / 2);

    for (int a = 0; a < 3; a++) {
        float invD = 1.0f / r.direction[a];
        float t0 = (min[a] - r.origin[a]) * invD;
        float t1 = (max[a] - r.origin[a]) * invD;
        if (invD < 0.0f) std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min) return false;
    }

    rec.t = t_min;
    rec.p = r.at(t_min);
    Vec3 outward_normal = (rec.p - center).normalized();
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
