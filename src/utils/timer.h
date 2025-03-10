#pragma once

#include <chrono>

class Timer {
public:
    Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};
