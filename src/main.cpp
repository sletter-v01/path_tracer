#include "renderer/path_tracer.h"
#include "scene/hittable_list.h"
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
void render_section(int start_row, int end_row, const Camera& cam, const HittableList& world, int image_width, int image_height, int samples_per_pixel, int max_depth, Image& image, PathTracer& path_tracer) {
    for (int j = start_row; j <= end_row; ++j) {
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_float()) / (image_width - 1);
                auto v = (j + random_float()) / (image_height - 1);
                Ray r = cam.getRay(u, v);
                pixel_color += path_tracer.ray_color(r, world, max_depth);
            }
            image.set_pixel(i, image_height - j - 1, pixel_color, samples_per_pixel); // Inverser l'ordre des lignes
        }
    }
}

int main() {
    // Journalisation de début de programme
    std::cout << "Démarrage du programme de tracé de chemin..." << std::endl;

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800; // Réduire la résolution
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100; // Réduire le nombre d'échantillons
    const int max_depth = 50; // Augmenter la profondeur maximale

    // Journalisation des paramètres d'image
    std::cout << "Paramètres d'image : " << std::endl;
    std::cout << "  - largeur : " << image_width << std::endl;
    std::cout << "  - hauteur : " << image_height << std::endl;
    std::cout << "  - échantillons par pixel : " << samples_per_pixel << std::endl;
    std::cout << "  - profondeur maximale : " << max_depth << std::endl;

    // World
    int num_spheres = 1; // Nombre de sphères à afficher
    std::cout << "Création de la scène aléatoire avec " << num_spheres << " sphères..." << std::endl;
    auto world = random_scene(num_spheres);
    std::cout << "Scène créée." << std::endl;

    // Camera
    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    std::cout << "Configuration de la caméra..." << std::endl;
    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    std::cout << "Caméra configurée." << std::endl;

    // Render
    std::cout << "Début du rendu..." << std::endl;
    PathTracer path_tracer;
    Image image(image_width, image_height);

    Timer timer;

    // Utilisation du multithreading
    int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int section_height = image_height / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * section_height;
        int end_row = (t == num_threads - 1) ? image_height - 1 : (start_row + section_height - 1);
        threads.push_back(std::thread(render_section, start_row, end_row, std::ref(cam), std::ref(world), image_width, image_height, samples_per_pixel, max_depth, std::ref(image), std::ref(path_tracer)));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    image.save("output.ppm");
    std::cout << "Image enregistrée sous output.ppm" << std::endl;
    std::cout << "Temps de rendu : " << timer.elapsed() << " secondes" << std::endl;

    return 0;
}
