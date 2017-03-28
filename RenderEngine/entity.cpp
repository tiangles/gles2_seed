#include "entity.h"
#include "material.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "texture.h"

using namespace GLES2;
Entity::Entity(std::shared_ptr<Mesh> mesh)
    :m_mesh(mesh)
{

}

Entity::~Entity()
{
    m_materials.clear();
}

void Entity::addMaterial(std::shared_ptr<Material> mat)
{
    m_materials.push_back(mat);
}

void Entity::render(std::shared_ptr<Matrix4x4> projMatrix)
{
    for(auto mat: m_materials)
    {
        auto tex = mat->texture();
        tex->bind();
        auto shader = mat->shaderProgram();
        shader->use(projMatrix, m_modelMatrix);
        m_mesh->render();
    }
}
