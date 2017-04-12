#include "vertex.h"

using namespace GLES2;

Vertex::Vertex()
    :m_vertexObject(0)
    ,m_colorObject(0)
    ,m_vertexType(NONE)

{
    initializeOpenGLFunctions();

}

Vertex::~Vertex()
{
    glDeleteBuffers(1, &m_vertexObject);
}

void Vertex::build(std::vector<VertexDataPCNT> vert)
{
    build(vert.data(), vert.size());
}

void Vertex::build(const VertexDataPCNT* vert, int count)
{
    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataPCNT)*count, vert, GL_STATIC_DRAW);
    m_vertexType = PCNT;
}

void Vertex::build(std::vector<VertexDataPNT> vert)
{
    build(vert.data(), vert.size());
}

void Vertex::build(const VertexDataPNT *vert, int count)
{
    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataPNT)*count, vert, GL_STATIC_DRAW);
    m_vertexType = PNT;
}

void Vertex::build(std::vector<VertexDataPT> vert)
{
    build(vert.data(), vert.size());
}

void Vertex::build(const VertexDataPT* vert, int count)
{
    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDataPT)*count, vert, GL_STATIC_DRAW);
    m_vertexType = PT;
}

void Vertex::bind(GLint position, GLint color, GLint normal, GLint texCoord)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);

    if(m_vertexType == PCNT){
        if(position != -1){
            glEnableVertexAttribArray(position);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPCNT), 0);
        }
        if(color != -1){
            glEnableVertexAttribArray(color);
            glVertexAttribPointer(color,    4, GL_FLOAT, GL_FALSE, sizeof(VertexDataPCNT), (void*)(sizeof(vec3)));
        }
        if(normal != -1){
            glEnableVertexAttribArray(normal);
            glVertexAttribPointer(normal,   3,  GL_FLOAT, GL_FALSE, sizeof(VertexDataPCNT), (void*)(sizeof(vec3) + sizeof(vec4)));
        }
        if(texCoord != -1){
            glEnableVertexAttribArray(texCoord);
            glVertexAttribPointer(texCoord, 2,  GL_FLOAT, GL_FALSE, sizeof(VertexDataPCNT), (void*)(sizeof(vec3) + sizeof(vec4) + sizeof(vec3)));
        }
    } else if(m_vertexType == PNT){
        if(position != -1){
            glEnableVertexAttribArray(position);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPNT), 0);
        }
        if(normal != -1){
            glEnableVertexAttribArray(normal);
            glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPNT), (void*)(sizeof(vec3)));
        }
        if(texCoord != -1){
            glEnableVertexAttribArray(texCoord);
            glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataPNT), (void*)(sizeof(vec3) + sizeof(vec3)));
        }
    } else if(m_vertexType == PT){
        if(position != -1){
            glEnableVertexAttribArray(position);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPT), 0);
        }
        if(texCoord != -1){
            glEnableVertexAttribArray(texCoord);
            glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataPT), (void*)(sizeof(vec3)));
        }
    }
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
