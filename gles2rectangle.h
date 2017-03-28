#pragma once
#include <qopenglfunctions.h>

namespace GLES2 {
class Texture;
}

class GLES2Rectangle:public QOpenGLFunctions
{
public:
    GLES2Rectangle();
    ~GLES2Rectangle();

public:
    void render();

private:
    GLuint m_vertexObject;
    GLuint m_colorObject;
    GLuint m_indicesObject;

    GLES2::Texture* m_tex;
};
