#include "mesh.h"
#include "vertex.h"

using namespace GLES2;

Mesh::Mesh(std::shared_ptr<Vertex> vertex, std::shared_ptr<Indices> indices)
    :m_vertex(vertex)
    ,m_indices(indices)
{

}

Mesh::~Mesh()
{

}

void Mesh::render()
{
    m_vertex->bind();
    m_indices->draw();
}
