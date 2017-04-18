#pragma once
#include "vec.h"
#include <memory>

namespace GLES2 {

class Matrix4x4;

class Camera
{
public:
    Camera();

public:
    std::shared_ptr<Matrix4x4> viewMatrix() const;
    std::shared_ptr<Matrix4x4> projMatrix() const;

    void set(vec3 eye, vec3 lookAt, vec3 up);

    void setAsPrespective(float fovYDegrees, float aspect, float nearZ, float farZ);

    void rotate(vec3 axis, float theta);
    void rotate(vec3 axis, vec3 pos, float theta);
    void slide(vec3 d);
    void move(float x, float y, float z);
    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);

    vec3 position() const { return m_position; }
    vec3 right() const { return m_right; }
    vec3 up() const { return m_up; }
    vec3 direction() const { return m_direction; }

    bool dirty() const { return m_dirty; }
    void unSetDirty() const { m_dirty = false; }

private:
    Matrix4x4 extractMatrix() const;
private:
    mutable bool m_dirty;
    mutable bool m_needExtract;

    vec3 m_position;
    vec3 m_right;         //u
    vec3 m_up;            //v
    vec3 m_direction;     //n

    std::shared_ptr<Matrix4x4> m_viewMatrix;
    std::shared_ptr<Matrix4x4> m_projMatrix;
};


}
