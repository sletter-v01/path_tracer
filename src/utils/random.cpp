#include "random.h"

float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

float random_float(float min, float max) {
    return min + (max - min) * random_float();
}