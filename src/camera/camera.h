#pragma once

#include "../math/ray.h"
#include "../math/vector.h"
#include "../math/matrix.h"

class Camera {
public:
    Camera(
        Point3 lookFrom = Point3(0, 0, 0),
        Point3 lookAt = Point3(0, 0, -1),
        Vec3 vup = Vec3(0, 1, 0),
        float vfov = 40.0f,  // Vertical field-of-view in degrees
        float aspectRatio = 16.0f / 9.0f,
        float aperture = 0.0f,
        float focusDist = 10.0f,
        float time0 = 0.0f,
        float time1 = 0.0f
    );
    
    Ray getRay(float s, float t) const;

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    float lensRadius;
    float time0, time1;  // Intervalle de temps du shutter pour flou de mouvement
};