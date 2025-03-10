pragma once

#include "../math/ray.h"
#include "../math/vector.h"

class AABB {
public:
    Point3 minimum;
    Point3 maximum;

    AABB() {}
    AABB(const Point3& a, const Point3& b) : minimum(a), maximum(b) {}

    Point3 min() const { return minimum; }
    Point3 max() const { return maximum; }

    bool hit(const Ray& r, float t_min, float t_max) const {
        for (int a = 0; a < 3; a++) {
            auto invD = 1.0f / r.direction[a];
            auto t0 = (min()[a] - r.origin[a]) * invD;
            auto t1 = (max()[a] - r.origin[a]) * invD;
            if (invD < 0.0f) std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min)
                return false;
        }
        return true;
    }
};

AABB surrounding_box(AABB box0, AABB box1) {
    Point3 small(fmin(box0.min().x, box1.min().x),
                 fmin(box0.min().y, box1.min().y),
                 fmin(box0.min().z, box1.min().z));

    Point3 big(fmax(box0.max().x, box1.max().x),
               fmax(box0.max().y, box1.max().y),
               fmax(box0.max().z, box1.max().z));

    return AABB(small, big);
}
