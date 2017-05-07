#pragma once
#include <string>
#include <memory>

namespace GLES2 {
class Entity;
class ShaderProgram;
class Camera;
class Texture;
class Renderer;
class Matrix4x4;
}

class Rectangle
{
public:
    Rectangle(const std::string& resourceFolder,
              std::shared_ptr<GLES2::Renderer> renderer);

public:
    void build();
    void setShader(const std::string& name);
    void draw(std::shared_ptr<GLES2::Camera> camera) const;

private:
    std::string m_resourceFolder;
    std::shared_ptr<GLES2::Renderer> m_renderer;
    std::shared_ptr<GLES2::Texture> m_texture;
    std::shared_ptr<GLES2::ShaderProgram> m_shaderProgram;
    std::shared_ptr<GLES2::Entity> m_entity;

    std::shared_ptr<GLES2::Matrix4x4> m_modelMatrix;
};
