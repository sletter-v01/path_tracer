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

int main() {
    // Journalisation de début de programme
    std::cout << "Démarrage du programme de tracé de chemin..." << std::endl;

    // Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // Journalisation des paramètres d'image
    std::cout << "Paramètres d'image : " << std::endl;
    std::cout << "  - largeuer : " << image_width << std::endl;
    std::cout << "  - hauteur : " << image_height << std::endl;
    std::cout << "  - échantillons par pixel : " << samples_per_pixel << std::endl;
    std::cout << "  - profondeur maximale : " << max_depth << std::endl;

    // World
    std::cout << "Création de la scène aléatoire..." << std::endl;
    auto world = random_scene();
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
    for (int j = image_height - 1; j >= 0; --j) {
        // Journalisation de la progression
        if (j % 10 == 0) {
            std::cout << "Ligne " << j << " sur " << image_height << std::endl;
        }
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_float()) / (image_width - 1);
                auto v = (j + random_float()) / (image_height - 1);
                Ray r = cam.getRay(u, v);
                pixel_color += path_tracer.ray_color(r, world, max_depth);
            }
            image.set_pixel(i, j, pixel_color, samples_per_pixel);
        }
    }

    image.save("output.ppm");
    std::cout << "Image enregistrée sous output.ppm" << std::endl;
    std::cout << "Temps de rendu : " << timer.elapsed() << " secondes" << std::endl;

    return 0;
}
