#pragma once
#include <memory>
#include <vector>

namespace GLES2 {

class ShaderProgram;
class Texture;

class Material
{
public:
    Material();
    ~Material();

public:
    void setShaderProgram(std::shared_ptr<ShaderProgram> shader) { m_shader = shader; }
    void addTexture(std::shared_ptr<Texture> texture) { m_textures.emplace_back(texture); }

    auto shaderProgram() const { return m_shader; }
    auto textures() const { return m_textures; }

private:
    std::shared_ptr<ShaderProgram> m_shader;
    std::vector<std::shared_ptr<Texture> > m_textures;
};

}
