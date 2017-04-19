#include "entity.h"
#include "material.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "submesh.h"
#include "matrix4x4.h"
#include "submesh.h"
#include "textureunit.h"
#include "subentity.h"

using namespace GLES2;
Entity::Entity(std::shared_ptr<Mesh> mesh)
    :m_mesh(mesh)
{
    for(auto subMesh: m_mesh->subMeshes()){
        auto subEntity = std::make_shared<SubEntity>(subMesh);
        m_subEntities.emplace_back(subEntity);
    }
}

Entity::~Entity()
{
}

void Entity::setMaterial(std::shared_ptr<Material> mat)
{
    m_material = mat;
    for(auto subEntity: m_subEntities){
        subEntity->setMaterial(mat);
    }
}

std::vector<std::shared_ptr<RenderOperation> >
Entity::getRenderOperation() const
{
    std::vector<std::shared_ptr<RenderOperation> > result;
    for(auto subEntity: m_subEntities){
        auto ro = subEntity->getRenderOperation();
        result.emplace_back(ro);
    }

    return std::move(result);
}
