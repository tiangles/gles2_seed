#include "vertex.h"
#include "shaderprogram.h"

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

void Vertex::bind(std::shared_ptr<ShaderProgram> shader)
{
    if(!shader || m_vertexObject == 0){
        return;
    }

    GLint position = shader->getAttribLocation("a_position");
    GLint color = shader->getAttribLocation("a_color");
    GLint normal = shader->getAttribLocation("a_normal");
    GLint texCoord = shader->getAttribLocation("a_texCoord0");

    size_t possitionOffset = 0;
    size_t colorOffset = 0;
    size_t normalOffset = 0;
    size_t texCoordOffset = 0;
    size_t stride = 0;

    switch(m_vertexType){
    case PCNT:
        possitionOffset = 0;
        colorOffset = sizeof(vec3);
        normalOffset = sizeof(vec3) + sizeof(vec4);
        texCoordOffset = sizeof(vec3) + sizeof(vec4) + sizeof(vec3);
        stride = sizeof(VertexDataPCNT);
        break;
    case PNT:
        possitionOffset = 0;
        normalOffset = sizeof(vec3);
        texCoordOffset = sizeof(vec3) + sizeof(vec3);
        stride = sizeof(VertexDataPNT);
        break;
    case PT:
        possitionOffset = 0;
        texCoordOffset = sizeof(vec3);
        stride = sizeof(VertexDataPT);
        break;
        break;
    default:
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    if(position != -1){
        glEnableVertexAttribArray(position);
        glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, (void*)(possitionOffset));
    }
    if(color != -1){
        glEnableVertexAttribArray(color);
        glVertexAttribPointer(color,    4, GL_FLOAT, GL_FALSE, stride, (void*)(colorOffset));
    }
    if(normal != -1){
        glEnableVertexAttribArray(normal);
        glVertexAttribPointer(normal,   3,  GL_FLOAT, GL_FALSE, stride, (void*)(normalOffset));
    }
    if(texCoord != -1){
        glEnableVertexAttribArray(texCoord);
        glVertexAttribPointer(texCoord, 2,  GL_FLOAT, GL_FALSE, stride, (void*)(texCoordOffset));
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
