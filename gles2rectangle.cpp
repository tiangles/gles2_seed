#include "gles2rectangle.h"
#include "texture.h"
#include "vec.h"
#include "vertex.h"

using namespace GLES2;

static const float z = -0.1f;

static const vertex vert[] = {
    {{-0.5f, -0.5f, z}, {1.f, 1.f, 1.f, 1.f}, {0, 0, -1.f}, {0, 1}},
    {{ 0.5f, -0.5f, z}, {1.f, 1.f, 1.f, 1.f}, {0, 0, -1.f}, {1, 1}},
    {{ 0.5f,  0.5f, z}, {1.f, 1.f, 1.f, 1.f}, {0, 0, -1.f}, {1, 0}},
    {{-0.5f,  0.5f, z}, {1.f, 1.f, 1.f, 1.f}, {0, 0, -1.f}, {0, 0}},
};

static const short indices[] = {
    0, 1, 2, 0, 2, 3
};

GLES2Rectangle::GLES2Rectangle()
{
    initializeOpenGLFunctions();

    m_tex = new Texture("/home/btian/workspace/crate.jpg");
    m_tex->build();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glGenBuffers(1, &m_vertexObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glGenBuffers(1, &m_indicesObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

GLES2Rectangle::~GLES2Rectangle()
{

}

void GLES2Rectangle::render()
{
    m_tex->bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), 0);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), (void*)(sizeof(vec3) + sizeof(vec4) + sizeof(vec3)));

    glColorPointer(4, GL_FLOAT, sizeof(vertex), (void*)(sizeof(vec3)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesObject);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(short), GL_UNSIGNED_SHORT, 0);
}
