#pragma once

#include "vector.h"

class Ray {
public:
    Point3 origin;
    Vec3 direction;
    float time;  // Pour les effets de flou de mouvement
    
    Ray() : origin(), direction(0, 0, 1), time(0) {}
    Ray(const Point3& origin, const Vec3& direction, float time = 0)
        : origin(origin), direction(direction), time(time) {}
    
    Point3 at(float t) const {
        return origin + direction * t;
    }
};