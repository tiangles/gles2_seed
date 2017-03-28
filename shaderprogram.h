#pragma once
#include <string>
#include <memory>
#include <qopengl.h>
#include <qopenglfunctions.h>

namespace GLES2 {
class Matrix4x4;

class ShaderProgram: private QOpenGLFunctions
{
public:
    ShaderProgram();
    ~ShaderProgram();

public:
    void setShaderSource(const std::string& vertexSrc, const std::string& fragmentSrc);
    bool build();
    bool use(std::shared_ptr<Matrix4x4> projMatrix, std::shared_ptr<Matrix4x4> modelMatrix);
private:
    GLuint compile(const std::string &src, GLenum type);
    GLuint link(GLint vertexShader, GLint fragmentShader);

private:
    GLuint m_glProgram = 0;
    std::string m_vertexSrc;
    std::string m_fragmentSrc;

    GLint m_projMatLocation;
};

}
