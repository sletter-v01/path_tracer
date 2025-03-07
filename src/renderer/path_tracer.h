#pragma once

#include "../math/ray.h"
#include "../scene/hittable_list.h"
#include "../camera/camera.h"
#include "../scene/material.h"
#include <limits>
#include <memory>

class PathTracer {
public:
    Color ray_color(const Ray& r, const Hittable& world, int depth) {
        HitRecord rec;

        // Si nous avons atteint la profondeur maximale de récursion, arrêtons.
        if (depth <= 0)
            return Color(0, 0, 0);

        // Si le rayon touche un objet, calculons la couleur réfléchie/réfractée.
        if (world.hit(r, 0.001, std::numeric_limits<float>::infinity(), rec)) {
            Ray scattered;
            Color attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, world, depth-1);
            return Color(0, 0, 0);
        }

        // Sinon, utilisons un dégradé de couleur pour le ciel.
        Vec3 unit_direction = r.direction.normalized();
        auto t = 0.5f*(unit_direction.y + 1.0f);
        return (1.0f-t)*Color(1.0f, 1.0f, 1.0f) + t*Color(0.5f, 0.7f, 1.0f);
    }
};
