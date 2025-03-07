#pragma once

#include "vector.h"
#include <array>
#include <cmath>

class Matrix4x4 {
public:
    std::array<float, 16> data;
    
    // Constructeur par défaut (matrice identité)
    Matrix4x4() {
        for (int i = 0; i < 16; i++)
            data[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
    
    // Constructeur à partir d'un tableau
    Matrix4x4(const std::array<float, 16>& values) : data(values) {}
    
    // Accès aux éléments
    float& operator()(int row, int col) {
        return data[row * 4 + col];
    }
    
    float operator()(int row, int col) const {
        return data[row * 4 + col];
    }
    
    // Multiplication de matrices
    Matrix4x4 operator*(const Matrix4x4& b) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result(i, j) = 0;
                for (int k = 0; k < 4; ++k) {
                    result(i, j) += (*this)(i, k) * b(k, j);
                }
            }
        }
        return result;
    }
    
    // Transformation d'un point
    Point3 transformPoint(const Point3& p) const {
        float x = p.x * (*this)(0, 0) + p.y * (*this)(0, 1) + p.z * (*this)(0, 2) + (*this)(0, 3);
        float y = p.x * (*this)(1, 0) + p.y * (*this)(1, 1) + p.z * (*this)(1, 2) + (*this)(1, 3);
        float z = p.x * (*this)(2, 0) + p.y * (*this)(2, 1) + p.z * (*this)(2, 2) + (*this)(2, 3);
        float w = p.x * (*this)(3, 0) + p.y * (*this)(3, 1) + p.z * (*this)(3, 2) + (*this)(3, 3);
        
        return Point3(x/w, y/w, z/w);
    }
    
    // Transformation d'un vecteur (sans composante de translation)
    Vec3 transformVector(const Vec3& v) const {
        float x = v.x * (*this)(0, 0) + v.y * (*this)(0, 1) + v.z * (*this)(0, 2);
        float y = v.x * (*this)(1, 0) + v.y * (*this)(1, 1) + v.z * (*this)(1, 2);
        float z = v.x * (*this)(2, 0) + v.y * (*this)(2, 1) + v.z * (*this)(2, 2);
        
        return Vec3(x, y, z);
    }
    
    // Matrice inverse
    Matrix4x4 inverse() const;
    
    // Matrice transposée
    Matrix4x4 transpose() const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result(i, j) = (*this)(j, i);
            }
        }
        return result;
    }
    
    // Matrices de transformations courantes
    static Matrix4x4 translate(const Vec3& v);
    static Matrix4x4 scale(const Vec3& v);
    static Matrix4x4 rotateX(float angle);
    static Matrix4x4 rotateY(float angle);
    static Matrix4x4 rotateZ(float angle);
    static Matrix4x4 lookAt(const Point3& eye, const Point3& target, const Vec3& up);
    static Matrix4x4 perspective(float fov, float aspect, float near, float far);
};