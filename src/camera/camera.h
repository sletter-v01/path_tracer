#pragma once

#include "../math/ray.h"
#include "../math/vector.h"

class Camera {
public:
    Camera(
        Point3 lookFrom, Point3 lookAt, Vec3 vup,
        float vfov, float aspectRatio, float aperture, float focusDist,
        float t0 = 0.0, float t1 = 1.0
    );

    Ray getRay(float s, float t) const;

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    float lensRadius;
    float time0, time1;  // shutter open/close times
};
