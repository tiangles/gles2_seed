#pragma once
#include <string>
#include <memory>
#include <qopengl.h>
#include <qopenglfunctions.h>

namespace GLES2 {
class Matrix4x4;
class Renderer;

class ShaderProgram: private QOpenGLFunctions
{
public:
    ShaderProgram();
    ~ShaderProgram();

public:
    bool load(const std::string& vertexSrc, const std::string& fragmentSrc);
    bool loadFromFile(const std::string& vertexFile, const std::string& fragmentFile);
    bool use(Renderer& render);

    void setUniformi(const std::string& name, int value);
    void setUniformf(const std::string& name, float value);
    void setUniform4f(const std::string& name, float x, float y, float z, float w);
    void setUniformfv(const std::string& name, int count, const float* value);
    void setUniform2f(const std::string& name, float x, float y);
    void setUniformMatrix4fv(const std::string& name, bool transpose, const float* value);

    GLint getUniformLocation(const std::string& name);
    GLint getAttribLocation(const std::string& name);
private:
    GLuint compile(const std::string &src, GLenum type);
    GLuint link(GLint vertexShader, GLint fragmentShader);

    std::string readShader(const std::string& path);
private:
    GLuint m_glProgram = 0;
    std::map<std::string, GLint> m_uniformLocations;
    std::map<std::string, GLint> m_attribLocations;
};

}
