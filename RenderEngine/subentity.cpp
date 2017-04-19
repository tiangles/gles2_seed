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
    ro->m_vertex = m_subMesh->getVertex();
    ro->m_indices = m_subMesh->getIndices();
    ro->m_shader = m_material->shaderProgram();
    ro->m_textures = m_material->textures();
    return std::move(ro);
}
