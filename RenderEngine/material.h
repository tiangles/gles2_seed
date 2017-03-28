#pragma once
#include <memory>

namespace GLES2 {

class ShaderProgram;
class Texture;

class Material
{
public:
    Material(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture);
    ~Material();

public:
    auto shaderProgram() const { return m_shaderProgram; }
    auto texture() const { return m_texture; }

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<Texture> m_texture;
};

}
