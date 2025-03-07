#include "matrix.h"
#include <cmath>

Matrix4x4 Matrix4x4::inverse() const {
    // Calcul des cofacteurs et déterminant
    // Note: cette implémentation est simplifiée et pourrait être optimisée
    
    std::array<float, 16> result;
    
    // Calcul des mineurs
    float minor[16];
    
    minor[0] = data[5] * (data[10] * data[15] - data[11] * data[14]) -
               data[6] * (data[9] * data[15] - data[11] * data[13]) +
               data[7] * (data[9] * data[14] - data[10] * data[13]);
               
    minor[1] = -(data[4] * (data[10] * data[15] - data[11] * data[14]) -
                data[6] * (data[8] * data[15] - data[11] * data[12]) +
                data[7] * (data[8] * data[14] - data[10] * data[12]));
                
    minor[2] = data[4] * (data[9] * data[15] - data[11] * data[13]) -
               data[5] * (data[8] * data[15] - data[11] * data[12]) +
               data[7] * (data[8] * data[13] - data[9] * data[12]);
               
    minor[3] = -(data[4] * (data[9] * data[14] - data[10] * data[13]) -
                data[5] * (data[8] * data[14] - data[10] * data[12]) +
                data[6] * (data[8] * data[13] - data[9] * data[12]));
                
    minor[4] = -(data[1] * (data[10] * data[15] - data[11] * data[14]) -
                data[2] * (data[9] * data[15] - data[11] * data[13]) +
                data[3] * (data[9] * data[14] - data[10] * data[13]));
                
    minor[5] = data[0] * (data[10] * data[15] - data[11] * data[14]) -
               data[2] * (data[8] * data[15] - data[11] * data[12]) +
               data[3] * (data[8] * data[14] - data[10] * data[12]);
               
    minor[6] = -(data[0] * (data[9] * data[15] - data[11] * data[13]) -
                data[1] * (data[8] * data[15] - data[11] * data[12]) +
                data[3] * (data[8] * data[13] - data[9] * data[12]));
                
    minor[7] = data[0] * (data[9] * data[14] - data[10] * data[13]) -
               data[1] * (data[8] * data[14] - data[10] * data[12]) +
               data[2] * (data[8] * data[13] - data[9] * data[12]);
               
    minor[8] = data[1] * (data[6] * data[15] - data[7] * data[14]) -
               data[2] * (data[5] * data[15] - data[7] * data[13]) +
               data[3] * (data[5] * data[14] - data[6] * data[13]);
               
    minor[9] = -(data[0] * (data[6] * data[15] - data[7] * data[14]) -
                data[2] * (data[4] * data[15] - data[7] * data[12]) +
                data[3] * (data[4] * data[14] - data[6] * data[12]));
                
    minor[10] = data[0] * (data[5] * data[15] - data[7] * data[13]) -
                data[1] * (data[4] * data[15] - data[7] * data[12]) +
                data[3] * (data[4] * data[13] - data[5] * data[12]);
                
    minor[11] = -(data[0] * (data[5] * data[14] - data[6] * data[13]) -
                 data[1] * (data[4] * data[14] - data[6] * data[12]) +
                 data[2] * (data[4] * data[13] - data[5] * data[12]));
                 
    minor[12] = -(data[1] * (data[6] * data[11] - data[7] * data[10]) -
                 data[2] * (data[5] * data[11] - data[7] * data[9]) +
                 data[3] * (data[5] * data[10] - data[6] * data[9]));
                 
    minor[13] = data[0] * (data[6] * data[11] - data[7] * data[10]) -
                data[2] * (data[4] * data[11] - data[7] * data[8]) +
                data[3] * (data[4] * data[10] - data[6] * data[8]);
                
    minor[14] = -(data[0] * (data[5] * data[11] - data[7] * data[9]) -
                 data[1] * (data[4] * data[11] - data[7] * data[8]) +
                 data[3] * (data[4] * data[9] - data[5] * data[8]));
                 
    minor[15] = data[0] * (data[5] * data[10] - data[6] * data[9]) -
                data[1] * (data[4] * data[10] - data[6] * data[8]) +
                data[2] * (data[4] * data[9] - data[5] * data[8]);
    
    // Déterminant
    float det = data[0] * minor[0] + data[1] * minor[1] + data[2] * minor[2] + data[3] * minor[3];
    float invDet = 1.0f / det;
    
    // Calculer la matrice adjointe multipliée par 1/déterminant
    for (int i = 0; i < 16; ++i) {
        result[i] = minor[i] * invDet;
    }
    
    return Matrix4x4(result);
}

Matrix4x4 Matrix4x4::translate(const Vec3& v) {
    Matrix4x4 result;
    result(0, 3) = v.x;
    result(1, 3) = v.y;
    result(2, 3) = v.z;
    return result;
}

Matrix4x4 Matrix4x4::scale(const Vec3& v) {
    Matrix4x4 result;
    result(0, 0) = v.x;
    result(1, 1) = v.y;
    result(2, 2) = v.z;
    return result;
}

Matrix4x4 Matrix4x4::rotateX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    Matrix4x4 result;
    result(1, 1) = c;
    result(1, 2) = -s;
    result(2, 1) = s;
    result(2, 2) = c;
    
    return result;
}

Matrix4x4 Matrix4x4::rotateY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    Matrix4x4 result;
    result(0, 0) = c;
    result(0, 2) = s;
    result(2, 0) = -s;
    result(2, 2) = c;
    
    return result;
}

Matrix4x4 Matrix4x4::rotateZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    Matrix4x4 result;
    result(0, 0) = c;
    result(0, 1) = -s;
    result(1, 0) = s;
    result(1, 1) = c;
    
    return result;
}

Matrix4x4 Matrix4x4::lookAt(const Point3& eye, const Point3& target, const Vec3& up) {
    Vec3 f = (target - eye).normalized();
    Vec3 s = f.cross(up).normalized();
    Vec3 u = s.cross(f);
    
    Matrix4x4 result;
    result(0, 0) = s.x;
    result(0, 1) = s.y;
    result(0, 2) = s.z;
    result(1, 0) = u.x;
    result(1, 1) = u.y;
    result(1, 2) = u.z;
    result(2, 0) = -f.x;
    result(2, 1) = -f.y;
    result(2, 2) = -f.z;
    result(0, 3) = -s.dot(eye);
    result(1, 3) = -u.dot(eye);
    result(2, 3) = f.dot(eye);
    
    return result;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float near, float far) {
    float tanHalfFovy = std::tan(fov / 2.0f);
    
    Matrix4x4 result;
    std::fill(result.data.begin(), result.data.end(), 0.0f);
    
    result(0, 0) = 1.0f / (aspect * tanHalfFovy);
    result(1, 1) = 1.0f / tanHalfFovy;
    result(2, 2) = -(far + near) / (far - near);
    result(2, 3) = -2.0f * far * near / (far - near);
    result(3, 2) = -1.0f;
    
    return result;
}