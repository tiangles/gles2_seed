#include "mesh.h"
#include "vertex.h"
#include "material.h"
#include "shaderprogram.h"

using namespace GLES2;

Mesh::Mesh(std::shared_ptr<Vertex> vertex, std::shared_ptr<Indices> indices)
    :m_vertex(vertex)
    ,m_indices(indices)
{

}

Mesh::~Mesh()
{

}

void Mesh::render(std::shared_ptr<Material> material)
{
    auto shader = material->shaderProgram();
    m_vertex->bind(shader->getAttribLocation("a_position"), -1, shader->getAttribLocation("a_normal"), shader->getAttribLocation("a_tex0"));
    m_indices->draw();
}
