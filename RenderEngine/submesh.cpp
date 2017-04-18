#include "submesh.h"
#include "vertex.h"
#include "shaderprogram.h"

using namespace GLES2;

SubMesh::SubMesh(std::shared_ptr<Vertex> vertex, std::shared_ptr<Indices> indices)
    :m_vertex(vertex)
    ,m_indices(indices)
{

}

SubMesh::~SubMesh()
{

}

void SubMesh::render(std::shared_ptr<ShaderProgram> shader)
{
    m_vertex->bind(shader);
    m_indices->draw();
}
