#include "matrix4x4.h"
#include "math.h"
using namespace GLES2;

Matrix4x4
Matrix4x4Util::BuildOrthoMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
{
    float dxInv = 1 / (right - left);
    float dyInv = 1 / (top - bottom);
    float dzInv = 1 / (zFar - zNear);

    return Matrix4x4(
        2 * dxInv,          0,          0,  (right + left) * -dxInv,
                0,  2 * dyInv,          0,  (top + bottom) * -dyInv,
                0,          0, -2 * dzInv,  (zFar + zNear) * -dzInv,
                0,          0,          0,                        1);
}

Matrix4x4 Matrix4x4Util::BuildFrustumMatrix(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float dxInv = 1 / (right - left);
    float dyInv = 1 / (top - bottom);
    float dzInv = 1 / (farZ - nearZ);
    float near2 = 2 * nearZ;

    return Matrix4x4(
        near2 * dxInv,              0,  (right + left) * dxInv,                     0,
                    0,  near2 * dyInv,  (top + bottom) * dyInv,                     0,
                    0,              0, (farZ + nearZ) * -dzInv, near2 * farZ * -dzInv,
                    0,              0,                      -1,                     0);
}

Matrix4x4 Matrix4x4Util::BuildPerspectiveMatrix(float fovYDegrees, float aspect, float nearZ, float farZ)
{
    static const float Pi=3.14159265359;
    float top = static_cast<float>(tan(fovYDegrees * 0.5 * Pi / 180.0) * nearZ);
    float right = top * aspect;
    return BuildFrustumMatrix(-right, right, -top, top, nearZ, farZ);
}

Matrix4x4
Matrix4x4Util::BuildViewportMatrix(float x, float y, float width, float height)
{
    float halfW = width / 2;
    float halfH = height / 2;

    return Matrix4x4(
        halfW,     0, 0, halfW + x,
            0, halfH, 0, halfH + y,
            0,     0, 1,         0,
            0,     0, 0,         1);
}
