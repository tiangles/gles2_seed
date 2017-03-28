#pragma once
#include "vec.h"
#include <qopenglfunctions.h>

namespace GLES2 {

struct VertexDataPCNT{
    vec3 position;
    vec4 color;
    vec3 normal;
    vec2 tex;
};

class Vertex :public QOpenGLFunctions
{
public:
    Vertex();
    ~Vertex();

public:
    void build(std::vector<VertexDataPCNT> vert);
    void build(const VertexDataPCNT* vert, int count);
    void bind();

private:
    GLuint m_vertexObject;
    GLuint m_colorObject;
};

class Indices:public QOpenGLFunctions
{
public:
    Indices();
    ~Indices();
public:
    void build(const void* data, int size);
    void draw();

private:
    GLuint m_indicesObject;
    int m_count;
};
}
