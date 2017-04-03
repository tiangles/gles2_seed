#pragma once
#include <QString>
#include <qopenglfunctions.h>

namespace GLES2 {

class Texture: private QOpenGLFunctions
{
public:
    Texture(const QString& path);
    ~Texture();
public:
    void build();
    void bind(int texUnit);

private:
    QString m_texFileName;
    GLuint m_texID;
};

}
