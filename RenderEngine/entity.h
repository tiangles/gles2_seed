#pragma once
#include <memory>
#include <vector>
#include "renderoperation.h"
namespace GLES2 {

class Mesh;
class SubEntity;

class Material;
struct Matrix4x4;
class RenderOperation;

class Entity
{
public:
    Entity(std::shared_ptr<Mesh> mesh);
    ~Entity();

public:
    void setMaterial(std::shared_ptr<Material> mat);

    std::vector<std::shared_ptr<RenderOperation> > getRenderOperation() const;
    auto getSubEntities() const { return m_subEntities; }
private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;

    std::vector<std::shared_ptr<SubEntity> > m_subEntities;
    std::shared_ptr<Matrix4x4> m_modelMatrix;
};

}
