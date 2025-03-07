#pragma once

#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include <memory>

// Déclaration de la fonction random_float
// Cette fonction renvoie un nombre flottant aléatoire entre 0 et 1.
float random_float();

// Surcharge de la fonction random_float
// Cette fonction renvoie un nombre flottant aléatoire entre min et max.
float random_float(float min, float max);

// Fonction random_scene
// Cette fonction génère une scène aléatoire composée de sphères avec différents matériaux.
HittableList random_scene(int num_spheres) {
    // Création d'un objet HittableList pour stocker les objets de la scène.
    HittableList world;

    // Création du matériau du sol (un Lambertian de couleur grise).
    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    // Ajout du sol à la scène (une grande sphère qui simule un plan horizontal).
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    // Calcul du nombre maximum de sphères par ligne en fonction du nombre total de sphères.
    int max_spheres_per_row = static_cast<int>(std::sqrt(num_spheres));
    int count = 0; // Compteur pour le nombre de sphères ajoutées.

    // Boucles pour générer des sphères dans une grille.
    for (int a = -max_spheres_per_row; a < max_spheres_per_row && count < num_spheres; a++) {
        for (int b = -max_spheres_per_row; b < max_spheres_per_row && count < num_spheres; b++) {
            // Génération d'un matériau aléatoire pour chaque sphère.
            float choose_mat = random_float();
            // Calcul de la position centrale de la sphère.
            Point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            // Vérifier que l'objet est dans le champ de vision (limité à une zone de 20x20).
            if (center.x < -10 || center.x > 10 || center.z < -10 || center.z > 10) {
                continue; // Sauter cette sphère si elle est hors du champ.
            }

            // Vérifier que la sphère ne chevauche pas une autre sphère spécifique.
            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                // Choisir un matériau en fonction de la valeur aléatoire.
                if (choose_mat < 0.8) {
                    // Matériau diffus (Lambertian) avec une couleur aléatoire.
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Matériau métallique avec une couleur et un flou aléatoires.
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // Matériau diélectrique (verre) avec un indice de réfraction de 1.5.
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                count++; // Incrémenter le compteur de sphères ajoutées.
            }
        }
    }

    // Ajouter trois grandes sphères avec des matériaux spécifiques au centre de la scène.
    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    // Retourner la liste des objets de la scène.
    return world;
}
