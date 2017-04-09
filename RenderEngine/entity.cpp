#include "entity.h"
#include "material.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "texture.h"
#include "matrix4x4.h"

using namespace GLES2;
Entity::Entity(std::shared_ptr<Mesh> mesh)
    :m_mesh(mesh)
{

}

Entity::~Entity()
{
}

void Entity::setMaterial(std::shared_ptr<Material> mat)
{
    m_material = mat;
}

void Entity::render(std::shared_ptr<Matrix4x4> projMatrix,
                    std::shared_ptr<Matrix4x4> modelViewMatrix)
{
    auto texures = m_material->textures();
    int unit = 0;
    for(auto tex: texures){
        tex->bind(unit++);
    }
    auto shader = m_material->shaderProgram();
    shader->use();
    shader->setUniformMatrix4fv("u_projMatrix",         projMatrix->buffer[0]);
    shader->setUniformMatrix4fv("u_modelViewMatrix",    modelViewMatrix->buffer[0]);
    m_mesh->render(m_material);
}
