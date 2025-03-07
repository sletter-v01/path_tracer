#pragma once

// Inclusion des fichiers d'en-tête nécessaires pour les rayons, vecteurs et fonctions aléatoires.
#include "../math/ray.h"
#include "../math/vector.h"
#include "../utils/random.h"
#include <memory>

// Déclaration avancée de la structure HitRecord pour éviter les dépendances circulaires.
struct HitRecord;

// Classe de base abstraite pour les matériaux.
// Les classes dérivées doivent implémenter la méthode scatter pour définir le comportement de diffusion.
class Material {
public:
    // Méthode virtuelle pure pour la diffusion des rayons.
    // Cette méthode doit être implémentée par les classes dérivées.
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
    
    // Méthode virtuelle pour l'émission de lumière.
    // Par défaut, elle renvoie une couleur noire (pas d'émission).
    virtual Color emitted(float /*u*/, float /*v*/, const Point3& /*p*/) const {
        return Color(0, 0, 0);
    }
};

// Classe pour le matériau Lambertian, représentant une surface diffuse.
// La lumière est diffusée uniformément dans toutes les directions.
class Lambertian : public Material {
public:
    // Couleur albédo du matériau.
    Color albedo;

    // Constructeur prenant une couleur comme paramètre.
    Lambertian(const Color& a) : albedo(a) {}

    // Implémentation de la méthode scatter pour le matériau Lambertian.
    virtual bool scatter(const Ray& /*r_in*/, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        // Direction aléatoire de diffusion.
        auto scatter_direction = rec.normal + Vec3::random_unit_vector();
        // Si la direction est proche de zéro, utiliser la normale de la surface.
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        // Créer un nouveau rayon diffusé.
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

// Classe pour le matériau métallique, représentant une surface réfléchissante.
class Metal : public Material {
public:
    // Couleur albédo du matériau.
    Color albedo;
    // Facteur de flou pour la réflexion.
    float fuzz;

    // Constructeur prenant une couleur et un facteur de flou comme paramètres.
    Metal(const Color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    // Implémentation de la méthode scatter pour le matériau métallique.
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        // Calculer la direction réfléchie.
        Vec3 reflected = r_in.direction.normalized().reflect(rec.normal);
        // Créer un nouveau rayon réfléchi avec un certain flou.
        scattered = Ray(rec.p, reflected + fuzz * Vec3::random_in_unit_sphere());
        attenuation = albedo;
        // Le rayon est réfléchi si la direction est dans le même sens que la normale de la surface.
        return (scattered.direction.dot(rec.normal) > 0);
    }
};

// Classe pour le matériau diélectrique, représentant un matériau transparent comme le verre.
class Dielectric : public Material {
public:
    // Indice de réfraction du matériau.
    float ir;

    // Constructeur prenant l'indice de réfraction comme paramètre.
    Dielectric(float index_of_refraction) : ir(index_of_refraction) {}

    // Implémentation de la méthode scatter pour le matériau diélectrique.
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0); // Le matériau transparent ne change pas la couleur de la lumière.
        float refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        Vec3 unit_direction = r_in.direction.normalized();
        float cos_theta = fmin((-unit_direction).dot(rec.normal), 1.0);
        float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 direction;

        // Déterminer si le rayon doit être réfléchi ou réfracté.
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
            direction = unit_direction.reflect(rec.normal);
        else
            direction = unit_direction.refract(rec.normal, refraction_ratio);

        // Créer un nouveau rayon diffusé.
        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    // Méthode statique pour calculer le coefficient de réflexion utilisant l'approximation de Schlick.
    static float reflectance(float cosine, float ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
