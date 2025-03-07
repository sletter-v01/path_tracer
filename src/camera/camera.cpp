#include "camera.h"
#include <cmath>
#include <random>

Camera::Camera(
    Point3 lookFrom, Point3 lookAt, Vec3 vup,
    float vfov, float aspectRatio, float aperture, float focusDist,
    float t0, float t1
) {
    float theta = vfov * M_PI / 180.0f;
    float h = std::tan(theta / 2.0f);
    float viewportHeight = 2.0f * h;
    float viewportWidth = aspectRatio * viewportHeight;
    
    w = (lookFrom - lookAt).normalized();
    u = vup.cross(w).normalized();
    v = w.cross(u);
    
    origin = lookFrom;
    horizontal = u * viewportWidth * focusDist;
    vertical = v * viewportHeight * focusDist;
    lowerLeftCorner = origin - horizontal/2 - vertical/2 - w * focusDist;
    
    lensRadius = aperture / 2.0f;
    time0 = t0;
    time1 = t1;
}

Ray Camera::getRay(float s, float t) const {
    Vec3 rd = Vec3::random_in_unit_disk() * lensRadius;
    Vec3 offset = u * rd.x + v * rd.y;
    
    // Temps aléatoire pour le flou de mouvement
    std::random_device rd_device;
    std::mt19937 gen(rd_device());
    std::uniform_real_distribution<float> dist(time0, time1);
    float time = time0 + dist(gen) * (time1 - time0);
    
    return Ray(
        origin + offset,
        lowerLeftCorner + horizontal * s + vertical * t - origin - offset,
        time
    );
}