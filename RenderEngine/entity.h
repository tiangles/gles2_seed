#pragma once
#include <memory>

namespace GLES2 {

class Mesh;
class Material;
class Matrix4x4;

class Entity
{
public:
    Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat);
    ~Entity();

public:
    auto mesh() const {return m_mesh; }
    auto material() const {return m_material; }

    void render(std::shared_ptr<Matrix4x4> projMatrix);
private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Matrix4x4> m_modelMatrix;
};

}
