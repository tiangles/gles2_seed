#pragma once
#include <memory>
namespace GLES2 {
class Entity;
class Matrix4x4;
}

class GLES2Rectangle
{
public:
    GLES2Rectangle();
    ~GLES2Rectangle();

public:
    void render(std::shared_ptr<GLES2::Matrix4x4> projMatrix);

private:
    std::shared_ptr<GLES2::Entity> m_entity;
};
