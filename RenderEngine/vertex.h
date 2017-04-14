#pragma once
#include "vec.h"
#include <qopenglfunctions.h>
#include <memory>

namespace GLES2 {

struct VertexDataPCNT{
    vec3 position;
    vec4 color;
    vec3 normal;
    vec2 tex;
};

struct VertexDataPNT{
    vec3 position;
    vec3 normal;
    vec2 tex;
};

struct VertexDataPT{
    vec3 position;
    vec2 tex;
};

class ShaderProgram;

class Vertex :public QOpenGLFunctions
{
public:
    Vertex();
    ~Vertex();

public:
    void build(std::vector<VertexDataPCNT> vert);
    void build(const VertexDataPCNT* vert, int count);
    void build(std::vector<VertexDataPNT> vert);
    void build(const VertexDataPNT* vert, int count);
    void build(std::vector<VertexDataPT> vert);
    void build(const VertexDataPT* vert, int count);

    void bind(std::shared_ptr<ShaderProgram> shader);

private:
    enum VertexType{
        NONE,
        PCNT,
        PNT,
        PT
    };

    GLuint m_vertexObject;
    GLuint m_colorObject;
    VertexType m_vertexType;
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
