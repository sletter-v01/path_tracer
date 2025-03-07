#pragma once

#include "../math/vector.h"
#include <vector>
#include <string>
#include <fstream>

class Image {
public:
    Image(int width, int height) : width(width), height(height), data(width * height * 3) {}

    void set_pixel(int x, int y, const Color& color, int samples_per_pixel) {
        auto scale = 1.0 / samples_per_pixel;
        auto r = sqrt(scale * color.x);
        auto g = sqrt(scale * color.y);
        auto b = sqrt(scale * color.z);

        data[3 * (y * width + x) + 0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
        data[3 * (y * width + x) + 1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
        data[3 * (y * width + x) + 2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
    }

    void save(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        file << "P6\n" << width << " " << height << "\n255\n";
        for (auto value : data) {
            file << static_cast<unsigned char>(value);
        }
    }

private:
    int width, height;
    std::vector<int> data;

    static float clamp(float x, float min, float max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};
