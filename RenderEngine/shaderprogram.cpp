#include "shaderprogram.h"
#include "matrix4x4.h"
#include <fstream>

using namespace GLES2;

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{

}

bool ShaderProgram::load(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    initializeOpenGLFunctions();
    if(vertexSrc.empty() || fragmentSrc.empty()){
        return false;
    }
    if(m_glProgram != 0){
        glDeleteProgram(m_glProgram);
    }

    m_glProgram = 0;
    GLint vertexShader = compile(vertexSrc, GL_VERTEX_SHADER);
    GLint fragmentShader = compile(fragmentSrc, GL_FRAGMENT_SHADER);
    m_glProgram = link(vertexShader, fragmentShader);
    GLenum err = glGetError();
    if(err != 0){
        return false;
    }
    return true;
}

std::string ShaderProgram::readShader(const std::string& path){
    std::ifstream file;
    file.open(path, std::ios::binary|std::ios::in|std::ios::ate);
    if(file.is_open()){
        size_t size = file.tellg();
        file.seekg (0, std::ios::beg);

        std::string res(size, 0);
        file.seekg (0, std::ios::beg);
        file.read (&res[0], size);
        file.close();
        return std::move(res);
    }
    return std::string("");
}

bool ShaderProgram::loadFromFile(const std::string &vertexFile, const std::string &fragmentFile)
{
    return load(readShader(vertexFile), readShader(fragmentFile));
}

bool ShaderProgram::use()
{
    if(m_glProgram != 0){
        glUseProgram(m_glProgram);
        return true;
    }
    return false;
}

void ShaderProgram::setUniformi(const std::string& name, int value)
{
    GLint loc = getLocation(name);
    glUniform1i(loc, value);
}

void ShaderProgram::setUniformf(const std::string &name, float value)
{
    GLint loc = getLocation(name);
    glUniform1f(loc, value);
}

void ShaderProgram::setUniform2f(const std::string &name, float x, float y)
{
    GLint loc = getLocation(name);
    glUniform2f(loc, x, y);
}

GLint ShaderProgram::getLocation(const std::string &name)
{
    if(m_locations.find(name) == m_locations.end()){
        GLint loc = glGetUniformLocation(m_glProgram, name.c_str());
        m_locations[name] = loc;
    }
    return m_locations[name];
}

GLuint ShaderProgram::compile(const std::string &src, GLenum type)
{
    GLuint result = glCreateShader(type);
    const GLchar* source = (const GLchar*) src.c_str();

    glShaderSource(result, 1, &source, NULL);
    glCompileShader(result);

    GLint isCompiled;
    glGetShaderiv(result, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint infoLength = 0;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &infoLength);

        if (infoLength > 1) {
            std::vector<GLchar> infoLog(infoLength);
            glGetShaderInfoLog(result, infoLength, NULL, &infoLog[0]);
            qWarning("%s", infoLog.data());
        }
        glDeleteShader(result);
        result = 0;
    }
    return result;
}

GLuint ShaderProgram::link(GLint vertexShader, GLint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, fragmentShader);
    glAttachShader(program, vertexShader);
    glLinkProgram(program);

    GLint isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint infoLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

        if (infoLength > 1) {
            std::vector<GLchar> infoLog(infoLength);
            glGetProgramInfoLog(program, infoLength, NULL, &infoLog[0]);
            qWarning("%s", infoLog.data());
        }
        program = 0;
        glDeleteProgram(program);
    }
    return program;
}
