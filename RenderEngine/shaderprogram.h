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
    void loadFromFile(const std::string& vertexFile, const std::string& fragmentFile);
    bool build();
    bool use();

    void setUniformi(const std::string& name, int value);
    void setUniformf(const std::string& name, float value);
    void setUniform2f(const std::string& name, float x, float y);

private:
    GLint getLocation(const std::string& name);
    GLuint compile(const std::string &src, GLenum type);
    GLuint link(GLint vertexShader, GLint fragmentShader);

    std::string readShader(const std::string& path);
private:
    GLuint m_glProgram = 0;
    std::string m_vertexSrc;
    std::string m_fragmentSrc;

//    GLint m_projMatLocation;
    std::map<std::string, GLint> m_locations;
};

}
