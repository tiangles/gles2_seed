#include "camera.h"
#include "matrix4x4.h"
using namespace GLES2;

Camera::Camera()
{
    m_matrix = std::make_shared<Matrix4x4>();
    set(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
}

void Camera::set(vec3 eye, vec3 lookAt, vec3 up)
{
    Matrix4x4 m = Matrix4x4Util::BuildLookAtMatrix(eye, lookAt, up);
    memcpy(m_matrix->buffer, m.buffer, sizeof(Matrix4x4));
}

void Camera::move(float x, float y, float z)
{
    Matrix4x4 m = Matrix4x4Util::BuildTranslateMatrix(-x, -y, -z);
    update(m);
}

void Camera::roll(float angle)
{
    Matrix4x4 m = Matrix4x4Util::BuildRotateMatrix(vec3(1, 0, 0), -angle);
    update(m);
}

void Camera::pitch(float angle)
{
    Matrix4x4 m = Matrix4x4Util::BuildRotateMatrix(vec3(0, 0, 1), -angle);
    update(m);
}

void Camera::yaw(float angle)
{
    Matrix4x4 m = Matrix4x4Util::BuildRotateMatrix(vec3(0, 1, 0), -angle);
    update(m);
}

void Camera::update(const Matrix4x4 &mat)
{
    Matrix4x4 n = mat*(*m_matrix);
    memcpy(m_matrix->buffer, n.buffer, sizeof(Matrix4x4));
}
