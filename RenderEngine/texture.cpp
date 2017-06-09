#include "texture.h"
#include <QImage>
#include <QOpenGLWidget>

using namespace GLES2;

Texture::Texture():
    m_texID(0)
{
}

Texture::~Texture()
{
    if(m_texID != 0)
    {
        glDeleteTextures(1, &m_texID);
    }
}

void Texture::build(const std::string& path)
{
    initializeOpenGLFunctions();

    GLuint tex_id;
    GLint alignment;

    QImage tex;
    tex.load(path.c_str());
    tex = tex.convertToFormat(QImage::Format_RGBA8888);
    glGenTextures(1, &tex_id);
    glBindTexture( GL_TEXTURE_2D, tex_id );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glGetIntegerv (GL_UNPACK_ALIGNMENT, &alignment);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(),
                  0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );
    glPixelStorei (GL_UNPACK_ALIGNMENT, alignment);

    GLenum err = glGetError();
    if(err != 0){
        glDeleteTextures(1, &tex_id);
        tex_id = 0;
    }
    m_texID = tex_id;
}
