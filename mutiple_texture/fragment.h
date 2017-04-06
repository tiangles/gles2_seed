#pragma once
#include <memory>
#include <vector>
#include <qopenglfunctions.h>

namespace GLES2{
    class Entity;
    class Texture;
    class ShaderProgram;
}

class Fragment: public QOpenGLFunctions
{
public:
    Fragment(const std::string& resRoot);
public:
    void resize(int width, int height);
    void render();

private:
    void build();
    std::vector<std::shared_ptr<GLES2::Texture> > loadTexture();

private:
    std::string m_resRoot;
    std::shared_ptr<GLES2::ShaderProgram> m_shaderProgram;
    std::shared_ptr<GLES2::Entity> m_entity;
};
