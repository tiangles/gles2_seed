#include "subentity.h"
#include "renderoperation.h"
#include "submesh.h"
#include "material.h"

using namespace GLES2;


SubEntity::SubEntity(std::shared_ptr<SubMesh> subMesh)
    :m_subMesh(subMesh)
{

}

void SubEntity::setMaterial(std::shared_ptr<Material> material)
{
    m_material = material;
}

std::shared_ptr<RenderOperation> SubEntity::getRenderOperation() const
{
    auto ro = std::make_shared<RenderOperation>();
    ro->vertex = m_subMesh->getVertex();
    ro->indices = m_subMesh->getIndices();
    ro->shader = m_material->shaderProgram();
    ro->textures = m_material->textures();
    return std::move(ro);
}
