#include "entity.h"
#include "material.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "texture.h"

using namespace GLES2;
Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat)
    :m_mesh(mesh)
    ,m_material(mat)
{

}

Entity::~Entity()
{

}

void Entity::render(std::shared_ptr<Matrix4x4> projMatrix)
{
    auto tex = m_material->texture();
    tex->bind();
    auto shader = m_material->shaderProgram();
    shader->use(projMatrix, m_modelMatrix);
    m_mesh->render();
}
