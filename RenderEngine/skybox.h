#pragma once
#include <vector>
#include <string>
#include <memory>

namespace GLES2 {

class Camera;
class Entity;
class Matrix4x4;
class ShaderProgram;
class Renderer;

class Skybox{
public:
    Skybox(std::shared_ptr<Renderer> renderer);

public:
    void create(const std::string& resRoot, std::vector<std::string> textureFiles);
    void render(std::shared_ptr<Camera> camera);

private:
    std::shared_ptr<Renderer> m_renderer;
    std::shared_ptr<Entity> m_entity;
    std::shared_ptr<Matrix4x4> m_modelMatrix;
    std::shared_ptr<ShaderProgram> m_shaderProgram;

};

}
