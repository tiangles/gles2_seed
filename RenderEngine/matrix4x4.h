#pragma once

#include <string.h>

namespace GLES2 {
struct vec3;

struct Matrix4x4{
    Matrix4x4(){
        memset(buffer, 0, sizeof(float)*16);
        buffer[0][0] = buffer[1][1] = buffer[2][2] = buffer[3][3] = 1;
    }

    Matrix4x4(
           float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33)
    {
        buffer[0][0]  = m00;
        buffer[0][1]  = m01;
        buffer[0][2]  = m02;
        buffer[0][3]  = m03;
        buffer[1][0]  = m10;
        buffer[1][1]  = m11;
        buffer[1][2]  = m12;
        buffer[1][3]  = m13;
        buffer[2][0]  = m20;
        buffer[2][1]  = m21;
        buffer[2][2]  = m22;
        buffer[2][3]  = m23;
        buffer[3][0]  = m30;
        buffer[3][1]  = m31;
        buffer[3][2]  = m32;
        buffer[3][3]  = m33;
    }
    Matrix4x4 operator* (const Matrix4x4& m) const;
    vec3 operator* (const vec3& m) const;
    Matrix4x4& operator=(const Matrix4x4& m);

    float buffer[4][4];
};

class Matrix4x4Util
{
public:
    static Matrix4x4
    BuildViewportMatrix(float x, float y, float width, float height);
    static Matrix4x4
    BuildOrthoMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
    static Matrix4x4
    BuildFrustumMatrix(float left, float right, float bottom, float top, float nearZ, float farZ);
    static Matrix4x4
    BuildPerspectiveMatrix(float fovYDegrees, float aspect, float nearZ, float farZ);
    static Matrix4x4
    BuildLookAtMatrix(const vec3& eye, const vec3& center, const vec3& up);
    static Matrix4x4
    BuildTranslateMatrix(float x, float y, float z);
    static Matrix4x4
    BuildRotateMatrix(const vec3& axis, float radians);
    static Matrix4x4
    BuildRotateMatrix(float radians, float x, float y, float z);
};

}

