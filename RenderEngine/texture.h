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
    void bind(GLuint texUnit);

private:
    GLuint m_texID;
};

}
