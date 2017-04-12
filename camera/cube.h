#pragma once
#include <memory>
#include <vector>
#include <qopenglfunctions.h>

namespace GLES2{
    class Entity;
    class Texture;
    class ShaderProgram;
    struct Matrix4x4;
}

class Cube: public QOpenGLFunctions
{
public:
    Cube(const std::string& resRoot);

public:
    void resize(std::shared_ptr<GLES2::Matrix4x4> projMatrix);

    void render();
    void render(std::shared_ptr<GLES2::Matrix4x4> modelViewMatrix);

private:
    void build();
    std::vector<std::shared_ptr<GLES2::Texture> > loadTexture();

private:
    std::string m_resRoot;
    std::shared_ptr<GLES2::ShaderProgram> m_shaderProgram;
    std::shared_ptr<GLES2::Entity> m_entity;
    std::shared_ptr<GLES2::Matrix4x4> m_projMatrix;
    std::shared_ptr<GLES2::Matrix4x4> m_modelViewMatrix;
};
