#pragma once
#include <memory>
#include <vector>

namespace GLES2 {

class ShaderProgram;
class Texture;

class Material
{
public:
    Material(std::shared_ptr<ShaderProgram> shaderProgram,
             std::vector<std::shared_ptr<Texture> > textures);
    ~Material();

public:
    auto shaderProgram() const { return m_shaderProgram; }
    auto textures() const { return m_textures; }

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::vector<std::shared_ptr<Texture> > m_textures;
};

}
