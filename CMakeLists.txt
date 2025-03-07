cmake_minimum_required(VERSION 3.15)
project(monte_carlo_path_tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options de compilation
option(USE_MULTITHREADING "Enable multithreading" ON)

# Flags de compilation
if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -O3 -mavx2 -fopenmp)
endif()

# Bibliothèques externes
find_package(Threads REQUIRED)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    add_compile_options(${OpenMP_CXX_FLAGS})
    link_libraries(${OpenMP_CXX_FLAGS})
endif()

# Fichiers source
set(SOURCES
    src/main.cpp
    src/math/vector.cpp
    src/math/matrix.cpp
    src/math/ray.cpp
    #src/scene/hittable.cpp
    #src/scene/sphere.cpp
    #src/scene/hittable_list.cpp
    #src/scene/material.cpp
    #src/scene/bvh.cpp
    #src/scene/aabb.cpp
    #src/renderer/path_tracer.cpp
    #src/renderer/sampler.cpp
    src/camera/camera.cpp
    #src/utils/image.cpp
    #src/utils/timer.cpp
    src/utils/random.cpp
)

# Fichiers d'en-tête
set(HEADERS
    src/math/vector.h
    src/math/matrix.h
    src/math/ray.h
    src/scene/hittable.h
    src/scene/sphere.h
    src/scene/rectangular_prism.h
    src/scene/hittable_list.h
    src/scene/material.h
    src/scene/bvh.h
    src/scene/aabb.h
    src/scene/object.h
    src/scene/scene.h
    src/renderer/path_tracer.h
    src/renderer/sampler.h
    src/camera/camera.h
    src/utils/image.h
    src/utils/timer.h
    src/utils/random.h
)


# Exécutable
add_executable(path_tracer ${SOURCES} ${HEADERS})

if(USE_MULTITHREADING)
    target_link_libraries(path_tracer PRIVATE Threads::Threads)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(path_tracer PRIVATE OpenMP::OpenMP_CXX)
    endif()
endif()

# Installation
install(TARGETS path_tracer DESTINATION bin)
