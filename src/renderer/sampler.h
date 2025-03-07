#pragma once

#include "../math/vector.h"

class Sampler {
public:
    virtual Vec3 get_sample() const = 0;
};

class UniformSampler : public Sampler {
public:
    virtual Vec3 get_sample() const override {
        return Vec3::random();
    }
};