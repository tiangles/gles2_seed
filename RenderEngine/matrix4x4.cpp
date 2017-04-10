#include "matrix4x4.h"
#include "math.h"
#include "vec.h"
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

Matrix4x4
Matrix4x4Util::BuildLookAtMatrix(const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 z = eye - center;
    z.normalise();
    vec3 x = up.crossProduct(z);
    x.normalise();
    vec3 y = z.crossProduct(x);
    y.normalise();

    return Matrix4x4(
        x.x, x.y, x.z, -x.dotProduct(eye),
        y.x, y.y, y.z, -y.dotProduct(eye),
        z.x, z.y, z.z, -z.dotProduct(eye),
                0,   0,   0,      1);
}

Matrix4x4 Matrix4x4Util::BuildTranslateMatrix(float x, float y, float z)
{
    return Matrix4x4(
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
                );
}

Matrix4x4 Matrix4x4Util::BuildRotateMatrix(const vec3& axis, float radians)
{
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float vecLengthInverse = static_cast<float>(1.0 / sqrt(x * x + y * y + z * z ));

    if (vecLengthInverse != vecLengthInverse)
    {
        return Matrix4x4();
    }

    x *= vecLengthInverse;
    y *= vecLengthInverse;
    z *= vecLengthInverse;

    float sinSave = static_cast<float>(sin(radians));
    float cosSave = static_cast<float>(cos(radians));
    float oneMinusCos = static_cast<float>(1.0 - cosSave);
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float yz = y * z;
    float zx = z * x;
    float xs = x * sinSave;
    float ys = y * sinSave;
    float zs = z * sinSave;

    return Matrix4x4(
        (oneMinusCos * xx) + cosSave, (oneMinusCos * xy) - zs     , (oneMinusCos * zx) + ys     , 0,
        (oneMinusCos * xy) + zs     , (oneMinusCos * yy) + cosSave, (oneMinusCos * yz) - xs     , 0,
        (oneMinusCos * zx) - ys     , (oneMinusCos * yz) + xs     , (oneMinusCos * zz) + cosSave, 0,
        0                           , 0                           , 0                           , 1);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const{
    Matrix4x4 r;

    r.buffer[0][0] = buffer[0][0] * m.buffer[0][0] + buffer[0][1] * m.buffer[1][0] + buffer[0][2] * m.buffer[2][0] + buffer[0][3] * m.buffer[3][0];
    r.buffer[0][1] = buffer[0][0] * m.buffer[0][1] + buffer[0][1] * m.buffer[1][1] + buffer[0][2] * m.buffer[2][1] + buffer[0][3] * m.buffer[3][1];
    r.buffer[0][2] = buffer[0][0] * m.buffer[0][2] + buffer[0][1] * m.buffer[1][2] + buffer[0][2] * m.buffer[2][2] + buffer[0][3] * m.buffer[3][2];
    r.buffer[0][3] = buffer[0][0] * m.buffer[0][3] + buffer[0][1] * m.buffer[1][3] + buffer[0][2] * m.buffer[2][3] + buffer[0][3] * m.buffer[3][3];

    r.buffer[1][0] = buffer[1][0] * m.buffer[0][0] + buffer[1][1] * m.buffer[1][0] + buffer[1][2] * m.buffer[2][0] + buffer[1][3] * m.buffer[3][0];
    r.buffer[1][1] = buffer[1][0] * m.buffer[0][1] + buffer[1][1] * m.buffer[1][1] + buffer[1][2] * m.buffer[2][1] + buffer[1][3] * m.buffer[3][1];
    r.buffer[1][2] = buffer[1][0] * m.buffer[0][2] + buffer[1][1] * m.buffer[1][2] + buffer[1][2] * m.buffer[2][2] + buffer[1][3] * m.buffer[3][2];
    r.buffer[1][3] = buffer[1][0] * m.buffer[0][3] + buffer[1][1] * m.buffer[1][3] + buffer[1][2] * m.buffer[2][3] + buffer[1][3] * m.buffer[3][3];

    r.buffer[2][0] = buffer[2][0] * m.buffer[0][0] + buffer[2][1] * m.buffer[1][0] + buffer[2][2] * m.buffer[2][0] + buffer[2][3] * m.buffer[3][0];
    r.buffer[2][1] = buffer[2][0] * m.buffer[0][1] + buffer[2][1] * m.buffer[1][1] + buffer[2][2] * m.buffer[2][1] + buffer[2][3] * m.buffer[3][1];
    r.buffer[2][2] = buffer[2][0] * m.buffer[0][2] + buffer[2][1] * m.buffer[1][2] + buffer[2][2] * m.buffer[2][2] + buffer[2][3] * m.buffer[3][2];
    r.buffer[2][3] = buffer[2][0] * m.buffer[0][3] + buffer[2][1] * m.buffer[1][3] + buffer[2][2] * m.buffer[2][3] + buffer[2][3] * m.buffer[3][3];

    r.buffer[3][0] = buffer[3][0] * m.buffer[0][0] + buffer[3][1] * m.buffer[1][0] + buffer[3][2] * m.buffer[2][0] + buffer[3][3] * m.buffer[3][0];
    r.buffer[3][1] = buffer[3][0] * m.buffer[0][1] + buffer[3][1] * m.buffer[1][1] + buffer[3][2] * m.buffer[2][1] + buffer[3][3] * m.buffer[3][1];
    r.buffer[3][2] = buffer[3][0] * m.buffer[0][2] + buffer[3][1] * m.buffer[1][2] + buffer[3][2] * m.buffer[2][2] + buffer[3][3] * m.buffer[3][2];
    r.buffer[3][3] = buffer[3][0] * m.buffer[0][3] + buffer[3][1] * m.buffer[1][3] + buffer[3][2] * m.buffer[2][3] + buffer[3][3] * m.buffer[3][3];

    return r;
}
