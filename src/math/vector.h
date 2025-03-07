#pragma once

#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>
#if defined(__AVX2__)
#include <immintrin.h>
#endif

class Vec3 {
public:
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    // Opérateurs de base
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    Vec3 operator/(float s) const { 
        float inv = 1.0f / s;
        return Vec3(x * inv, y * inv, z * inv);
    }
    
    // Opérateurs d'assignation
    Vec3& operator+=(const Vec3& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    
    Vec3& operator-=(const Vec3& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    
    Vec3& operator*=(float s) {
        x *= s; y *= s; z *= s;
        return *this;
    }
    
    Vec3& operator/=(float s) {
        float inv = 1.0f / s;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    
    // Négation
    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    
    // Accès aux éléments
    float operator[](int i) const {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1 ? y : z);
    }
    
    float& operator[](int i) {
        assert(i >= 0 && i < 3);
        return i == 0 ? x : (i == 1 ? y : z);
    }
    
    // Produit scalaire
    float dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    // Produit vectoriel
    Vec3 cross(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y,
                    z * v.x - x * v.z,
                    x * v.y - y * v.x);
    }
    
    // Longueur au carré
    float length_squared() const {
        return x * x + y * y + z * z;
    }
    
    // Longueur
    float length() const {
        return std::sqrt(length_squared());
    }
    
    // Normalisation
    Vec3 normalized() const {
        float len = length();
        if (len > 0) {
            return *this / len;
        }
        return *this;
    }
    
    void normalize() {
        float len = length();
        if (len > 0) {
            *this /= len;
        }
    }
    
    // Réflexion par rapport à une normale
    Vec3 reflect(const Vec3& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
    }
    
    // Réfraction selon une normale et un indice de réfraction
    Vec3 refract(const Vec3& normal, float etai_over_etat) const {
        float cos_theta = std::min((-*this).dot(normal), 1.0f);
        Vec3 r_out_perp = (*this + normal * cos_theta) * etai_over_etat;
        Vec3 r_out_parallel = normal * -std::sqrt(std::abs(1.0f - r_out_perp.length_squared()));
        return r_out_perp + r_out_parallel;
    }
    
    // Méthodes utilitaires pour le Monte Carlo
    bool near_zero() const {
        const float EPSILON = 1e-8f;
        return (std::abs(x) < EPSILON) && (std::abs(y) < EPSILON) && (std::abs(z) < EPSILON);
    }
    
    static Vec3 random(float min = 0.0f, float max = 1.0f);
    static Vec3 random_in_unit_sphere();
    static Vec3 random_unit_vector();
    static Vec3 random_in_unit_disk();
    static Vec3 random_in_hemisphere(const Vec3& normal);
};

// Alias pour faciliter l'utilisation
using Point3 = Vec3;
using Color = Vec3;

// Opérateurs pour l'affichage et multiplication externe
std::ostream& operator<<(std::ostream& out, const Vec3& v);
inline Vec3 operator*(float t, const Vec3& v) { return v * t; }
