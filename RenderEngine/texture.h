#pragma once
#include <qopenglfunctions.h>
#include <string>

namespace GLES2 {

class Texture: private QOpenGLFunctions
{
public:
    Texture();
    ~Texture();
public:
    void build(const std::string& path);
    GLuint texId(){ return m_texID; }
    GLenum target() { return GL_TEXTURE_2D; }

private:
    GLuint m_texID;
};

}
