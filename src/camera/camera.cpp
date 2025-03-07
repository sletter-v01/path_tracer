#include "../math/ray.h"
#include "../math/vector.h"
#include "camera.h"
#include <cmath>
#include <random>

// Constructeur de la classe Camera
Camera::Camera(
    Point3 lookFrom, Point3 lookAt, Vec3 vup,
    float vfov, float aspectRatio, float aperture, float focusDist,
    float t0, float t1
) {
    // Calcul de l'angle en radians à partir de l'angle en degrés
    float theta = vfov * M_PI / 180.0f;
    // Calcul de la hauteur du viewport en fonction de l'angle
    float h = std::tan(theta / 2.0f);
    // Calcul de la hauteur du viewport
    float viewportHeight = 2.0f * h;
    // Calcul de la largeur du viewport en fonction du ratio d'aspect
    float viewportWidth = aspectRatio * viewportHeight;
    
    // Calcul des vecteurs de la caméra
    w = (lookFrom - lookAt).normalized(); // Vecteur de la caméra pointant vers l'arrière
    u = vup.cross(w).normalized(); // Vecteur de la caméra pointant vers la droite
    v = w.cross(u); // Vecteur de la caméra pointant vers le haut
    
    // Définition de l'origine de la caméra
    origin = lookFrom;
    // Définition de la largeur horizontale du viewport
    horizontal = u * viewportWidth * focusDist;
    // Définition de la hauteur verticale du viewport
    vertical = v * viewportHeight * focusDist;
    // Calcul du coin inférieur gauche du viewport
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w * focusDist;
    
    // Définition du rayon de l'ouverture de la lentille
    lensRadius = aperture / 2.0f;
    // Définition du temps d'ouverture de l'obturateur
    time0 = t0;
    // Définition du temps de fermeture de l'obturateur
    time1 = t1;
}

// Méthode pour obtenir un rayon à partir de la caméra
Ray Camera::getRay(float s, float t) const {
    // Génération d'un point aléatoire dans un disque unitaire pour simuler la profondeur de champ
    Vec3 rd = Vec3::random_in_unit_disk() * lensRadius;
    // Calcul du décalage du rayon en fonction de l'ouverture de la lentille
    Vec3 offset = u * rd.x + v * rd.y;
    
    // Génération d'un temps aléatoire pour le flou de mouvement
    std::random_device rd_device;
    std::mt19937 gen(rd_device());
    std::uniform_real_distribution<float> dist(time0, time1);
    float time = time0 + dist(gen) * (time1 - time0);
    
    // Retourne un rayon partant de l'origine décalée et pointant vers une position dans le viewport
    return Ray(
        origin + offset,
        lowerLeftCorner + horizontal * s + vertical * t - origin - offset,
        time
    );
}
