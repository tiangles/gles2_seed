#include "vertex.h"

using namespace GLES2;

Vertex::Vertex()
    :m_vertexObject(0)
    ,m_colorObject(0)

{
    initializeOpenGLFunctions();

}

Vertex::~Vertex()
{
    glDeleteBuffers(1, &m_vertexObject);
}

void Vertex::build(std::vector<VertexDataPCNT> vert)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataPCNT)*vert.size(), vert.data(), GL_STATIC_DRAW);
}

void Vertex::build(const VertexDataPCNT* vert, int count)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataPCNT)*count, vert, GL_STATIC_DRAW);
}

void Vertex::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);

    glVertexPointer     (3, GL_FLOAT, sizeof(VertexDataPCNT), 0);
    glColorPointer      (4, GL_FLOAT, sizeof(VertexDataPCNT), (void*)(sizeof(vec3)));
    glNormalPointer     (   GL_FLOAT, sizeof(VertexDataPCNT), (void*)(sizeof(vec3) + sizeof(vec4)));
    glTexCoordPointer   (2, GL_FLOAT, sizeof(VertexDataPCNT), (void*)(sizeof(vec3) + sizeof(vec4) + sizeof(vec3)));
}

Indices::Indices()
    :m_indicesObject(0)
    ,m_count(0)
{
    initializeOpenGLFunctions();
}

Indices::~Indices()
{
    glDeleteBuffers(1, &m_indicesObject);
}

void Indices::build(const void *data, int size)
{
    glGenBuffers(1, &m_indicesObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    m_count = size/sizeof(short);
}

void Indices::draw()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesObject);
    glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_SHORT, 0);
}
