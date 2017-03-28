#include "matrix4x4.h"

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
