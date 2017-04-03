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

void Entity::render()
{
    for(auto mat: m_materials)
    {
        auto texures = mat->textures();
        int unit = 0;
        for(auto tex: texures){
            tex->bind(unit++);
        }
        auto shader = mat->shaderProgram();
        shader->use();
        m_mesh->render();
    }
}
