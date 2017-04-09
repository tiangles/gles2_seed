#pragma once
#include <memory>
#include <vector>

namespace GLES2 {

class Mesh;
class Material;
struct Matrix4x4;

class Entity
{
public:
    Entity(std::shared_ptr<Mesh> mesh);
    ~Entity();

public:
    void setMaterial(std::shared_ptr<Material> mat);
    //TODO: the model matrix reflect to model location
    //it is better to have a node object(in scene tree) to matain this location
    void render(std::shared_ptr<Matrix4x4> projMatrix,
                std::shared_ptr<Matrix4x4> modelViewMatrix);
private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Matrix4x4> m_modelMatrix;
};

}
