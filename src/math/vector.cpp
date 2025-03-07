#include "vector.h"
#include <random>
#include <functional>
#include <omp.h>

// Variables statiques pour la génération de nombres aléatoires
static std::uniform_real_distribution<float> distribution(0.0, 1.0);
static std::mt19937 generator;
static auto random_float = std::bind(distribution, generator);

Vec3 Vec3::random(float min, float max) {
    return Vec3(min + (max - min) * random_float(),
                min + (max - min) * random_float(),
                min + (max - min) * random_float());
}

Vec3 Vec3::random_in_unit_sphere() {
    while (true) {
        Vec3 p = Vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

Vec3 Vec3::random_unit_vector() {
    return random_in_unit_sphere().normalized();
}

Vec3 Vec3::random_in_unit_disk() {
    while (true) {
        Vec3 p(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, 0);
        if (p.length_squared() < 1)
            return p;
    }
}

Vec3 Vec3::random_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    // Dans le même hémisphère que la normale
    if (in_unit_sphere.dot(normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
