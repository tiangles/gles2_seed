#include "mesh.h"
#include "vertex.h"
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

void Mesh::render(std::shared_ptr<ShaderProgram> shader)
{
    m_vertex->bind(shader);
    m_indices->draw();
}
