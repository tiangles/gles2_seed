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
class Mesh;
class Material;
}

class Rectangle
{
public:
    Rectangle(const std::string& resourceFolder,
              std::shared_ptr<GLES2::Renderer> renderer);

public:
    void setShader(const std::string& name);
    void draw(std::shared_ptr<GLES2::Camera> camera) const;

private:
    void build();
    std::shared_ptr<GLES2::Mesh> createMesh();
    std::shared_ptr<GLES2::Texture> loadTexture();

    std::shared_ptr<GLES2::ShaderProgram> loadShader(const std::string& name);

private:
    std::string m_resourceFolder;
    std::shared_ptr<GLES2::Renderer> m_renderer;
    std::shared_ptr<GLES2::Texture> m_texture;
    std::shared_ptr<GLES2::ShaderProgram> m_shaderProgram;
    std::shared_ptr<GLES2::Material> m_material;
    std::shared_ptr<GLES2::Entity> m_entity;

    std::shared_ptr<GLES2::Matrix4x4> m_modelMatrix;
};
