#pragma once
#include <string.h>

namespace GLES2 {
struct Matrix4x4{
    Matrix4x4(){
        memset(buffer, 0, sizeof(float)*16);
        buffer[3][3]  = 1;
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

    float buffer[4][4];
};

class Matrix4x4Util
{
public:
    static Matrix4x4
    BuildOrthoMatrix(float left, float right, float bottom, float top, float zNear, float zFar);

};

}

