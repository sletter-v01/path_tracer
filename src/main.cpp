#include "renderer/path_tracer.h"
#include "scene/hittable_list.h" // Inclusion du fichier d'en-tête pour la liste des objets "hittable"
#include "scene/sphere.h"
#include "camera/camera.h"
#include "scene/material.h"
#include "scene/scene.h"
#include "utils/image.h"
#include "utils/timer.h"
#include "utils/random.h"
#include <iostream>
#include <memory>
#include <vector>
#include <thread>

// Fonction pour rendre une partie de l'image
// Cette fonction est appelée par des threads pour paralléliser le rendu de l'image
void render_section(int start_row, int end_row, const Camera& cam, const HittableList& world, int image_width, int image_height, int samples_per_pixel, int max_depth, Image& image, PathTracer& path_tracer) {
    for (int j = start_row; j <= end_row; ++j) { // Parcourt les lignes de l'image de start_row à end_row
        for (int i = 0; i < image_width; ++i) { // Parcourt les colonnes de l'image
            Color pixel_color(1, 1, 1); // Initialise la couleur du pixel à noir
            for (int s = 0; s < samples_per_pixel; ++s) { // Effectue plusieurs échantillonnages pour le pixel
                float u = (i + random_float()) / (image_width - 1); // Coordonnée horizontale normalisée avec jitter
                float v = (j + random_float()) / (image_height - 1); // Coordonnée verticale normalisée avec jitter
                Ray r = cam.getRay(u, v); // Obtient un rayon de la caméra pour les coordonnées (u, v)
                pixel_color += path_tracer.ray_color(r, world, max_depth); // Calcule la couleur du rayon et l'ajoute à la couleur du pixel
            }
            image.set_pixel(i, image_height - j - 1, pixel_color, samples_per_pixel); // Définit la couleur du pixel dans l'image (en inversant l'ordre des lignes)
        }
    }
}

int main() {
    // Journalisation de début de programme
    std::cout << "Démarrage du programme de tracé de chemin..." << std::endl;

    // Image
    const auto aspect_ratio = 3.0 / 2.0; // Définition du ratio d'aspect de l'image
const int image_width = 600; // Largeur de l'image
    const int image_height = static_cast<int>(image_width / aspect_ratio); // Hauteur de l'image calculée à partir du ratio d'aspect
    const int samples_per_pixel = 150; // Nombre d'échantillons par pixel pour le rendu anti-aliasing
    const int max_depth = 25; // Profondeur maximale de récursion pour le tracé des rayons

    // Journalisation des paramètres d'image
    std::cout << "Paramètres d'image : " << std::endl;
    std::cout << "  - largeur : " << image_width << std::endl;
    std::cout << "  - hauteur : " << image_height << std::endl;
    std::cout << "  - échantillons par pixel : " << samples_per_pixel << std::endl;
    std::cout << "  - profondeur maximale : " << max_depth << std::endl;

    // World
    int num_spheres = 100; // Nombre de sphères à afficher dans la scène
    std::cout << "Création de la scène aléatoire avec " << num_spheres << " sphères..." << std::endl;
    auto world = random_scene(num_spheres); // Appel d'une fonction pour créer une scène aléatoire avec des sphères
    std::cout << "Scène créée." << std::endl;

    // Camera
    Point3 lookfrom(13, 2, 3); // Position de la caméra
    Point3 lookat(0, 0, 0); // Point que regarde la caméra
    Vec3 vup(0, 1, 0); // Vecteur "up" pour l'orientation de la caméra
    auto dist_to_focus = 5.0; // Distance de mise au point
    auto aperture = 0.0; // Ouverture de la caméra (pour la profondeur de champ)

    // Configuration de la caméra
    std::cout << "Configuration de la caméra..." << std::endl;
    Camera cam(lookfrom, lookat, vup, 25, aspect_ratio, aperture, dist_to_focus); // Initialisation de la caméra
    std::cout << "Caméra configurée." << std::endl;

    // Renderer
    std::cout << "Début du rendu..." << std::endl;
    PathTracer path_tracer; // Initialisation du tracer de chemin
    Image image(image_width, image_height); // Initialisation de l'image

    Timer timer; // Initialisation d'un chronomètre pour mesurer le temps de rendu

    // Utilisation du multithreading pour accélérer le rendu
    int num_threads = std::thread::hardware_concurrency(); // Obtient le nombre de threads supportés par le matériel
    std::vector<std::thread> threads; // Vecteur pour stocker les threads
    int section_height = image_height / num_threads; // Hauteur de la section de l'image rendue par chaque thread

    for (int t = 0; t < num_threads; ++t) { // Création et lancement des threads
        int start_row = t * section_height; // Ligne de départ pour le thread
        int end_row = (t == num_threads - 1) ? image_height - 1 : (start_row + section_height - 1); // Ligne de fin pour le thread
        threads.push_back(std::thread(render_section, start_row, end_row, std::ref(cam), std::ref(world), image_width, image_height, samples_per_pixel, max_depth, std::ref(image), std::ref(path_tracer))); // Lancement du thread
    }

    for (auto& thread : threads) { // Attente de la fin de tous les threads
        thread.join();
    }

    image.save("output.ppm"); // Sauvegarde de l'image rendue dans un fichier
    std::cout << "Image enregistrée sous output.ppm" << std::endl;
    std::cout << "Temps de rendu : " << timer.elapsed() << " secondes" << std::endl; // Affichage du temps de rendu

    return 0;
}
