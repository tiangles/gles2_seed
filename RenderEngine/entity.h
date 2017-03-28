#pragma once
#include <memory>
#include <vector>

namespace GLES2 {

class Mesh;
class Material;
class Matrix4x4;

class Entity
{
public:
    Entity(std::shared_ptr<Mesh> mesh);
    ~Entity();

public:
    void addMaterial(std::shared_ptr<Material> mat);
    void render(std::shared_ptr<Matrix4x4> projMatrix);
private:
    std::shared_ptr<Mesh> m_mesh;
    std::vector<std::shared_ptr<Material> > m_materials;
    std::shared_ptr<Matrix4x4> m_modelMatrix;
};

}
