#include "camera.h"
#include "matrix4x4.h"
using namespace GLES2;

Camera::Camera()
    :m_dirty(true)
    ,m_needExtract(true)
{
    m_viewMatrix = std::make_shared<Matrix4x4>();
    m_projMatrix = std::make_shared<Matrix4x4>();
    set(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
}

std::shared_ptr<Matrix4x4>
Camera::viewMatrix() const {
    if(m_needExtract){
        auto m = extractMatrix();
        memcpy(m_viewMatrix->buffer[0], m.buffer[0], sizeof(m));
        m_needExtract = false;
    }
    return m_viewMatrix;
}

std::shared_ptr<Matrix4x4> Camera::projMatrix() const
{
    return m_projMatrix;
}

void Camera::set(vec3 eye, vec3 at, vec3 up)
{
    m_position = eye;

    m_direction = eye - at;
    m_direction.normalise();

    m_right = up.crossProduct(m_direction);
    m_right.normalise();

    m_up = m_direction.crossProduct(m_right);

    vec3 v1 = m_right.crossProduct(m_up);
    vec3 v2 = m_right.crossProduct(m_direction);
    vec3 v3 = m_up.crossProduct(m_direction);

    m_needExtract = true;
    m_dirty = true;
}

void Camera::setAsPrespective(float fovYDegrees, float aspect, float nearZ, float farZ)
{
    Matrix4x4 mat = Matrix4x4Util::BuildPerspectiveMatrix(fovYDegrees, aspect, nearZ, farZ);
    memcpy(m_projMatrix->buffer[0], mat.buffer[0], sizeof(mat));
}

void Camera::rotate(vec3 axis, float theta)
{
    Matrix4x4 transMat = Matrix4x4Util::BuildRotateMatrix(axis, theta);

    // merge current matrix to camera matrix
    m_right      = transMat * m_right;
    m_up         = transMat * m_up;
    m_direction  = transMat * m_direction;

    m_needExtract = true;
    m_dirty = true;
}

void Camera::rotate(vec3 axis, vec3 pos, float theta)
{
    vec3 vec = m_position - pos;

    Matrix4x4 transMat = Matrix4x4Util::BuildRotateMatrix(axis, theta);

    // merge current matrix to camera matrix
    vec          = transMat * vec;
    m_right      = transMat * m_right;
    m_up         = transMat * m_up;
    m_direction  = transMat * m_direction;

    m_position = vec + pos;

    m_needExtract = true;
    m_dirty = true;
}

void Camera::move(float x, float y, float z)
{
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;

    m_needExtract = true;
    m_dirty = true;
}

void Camera::slide(vec3 d)
{
    move(d.x, d.y, d.z);
}

void Camera::roll(float angle)
{
    rotate(m_direction, m_position, angle);
}

void Camera::pitch(float angle)
{
    rotate(m_right, m_position, angle);
}

void Camera::yaw(float angle)
{
    rotate(m_up, m_position, angle);
}

Matrix4x4 Camera::extractMatrix() const
{
    return Matrix4x4(
        m_right.x,      m_right.y,      m_right.z,      -m_right.dotProduct(m_position),
        m_up.x,         m_up.y,         m_up.z,         -m_up.dotProduct(m_position),
        m_direction.x,  m_direction.y,  m_direction.z,  -m_direction.dotProduct(m_position),
        0,              0,              0,              1);
}
