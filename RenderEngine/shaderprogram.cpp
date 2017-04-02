#include "shaderprogram.h"
#include "matrix4x4.h"

using namespace GLES2;

ShaderProgram::ShaderProgram()
{
    initializeOpenGLFunctions();
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::setShaderSource(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    m_vertexSrc = vertexSrc;
    m_fragmentSrc = fragmentSrc;
}

bool ShaderProgram::build()
{
    if(m_glProgram != 0){
        glDeleteProgram(m_glProgram);
    }

    m_glProgram = 0;
    GLint vertexShader = compile(m_vertexSrc, GL_VERTEX_SHADER);
    GLint fragmentShader = compile(m_fragmentSrc, GL_FRAGMENT_SHADER);
    m_glProgram = link(vertexShader, fragmentShader);

    glUseProgram(m_glProgram);

    m_projMatLocation = glGetUniformLocation(m_glProgram, "u_mvMatrix");

    GLenum err = glGetError();
    if(err != 0){
        err = 0;
    }
    return true;
}

bool ShaderProgram::use(std::shared_ptr<Matrix4x4> projMatrix, std::shared_ptr<Matrix4x4> /*modelMatrix*/)
{
    glUseProgram(m_glProgram);
    glUniformMatrix4fv(m_projMatLocation, 1, 0, (const float*)projMatrix->buffer);
    return false;
}

void ShaderProgram::setUniformi(const std::string& name, int value)
{
    GLint loc = getLocation(name);
    glUniform1i(loc, value);
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
