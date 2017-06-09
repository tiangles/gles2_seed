#pragma once
#include <memory>
#include <vector>

namespace GLES2 {

class ShaderProgram;
class TextureUnit;
class Texture;

class Material
{
public:
    Material();
    ~Material();

public:
    void setShaderProgram(std::shared_ptr<ShaderProgram> shader) { m_shader = shader; }
    void addTexture(std::shared_ptr<Texture> texture, unsigned int unit);
    void addTextureUnit(std::shared_ptr<TextureUnit> textureUnit) { m_textureUnits.emplace_back(textureUnit); }

    auto shaderProgram() const { return m_shader; }
    auto textureUnits() const { return m_textureUnits; }

private:
    std::shared_ptr<ShaderProgram> m_shader;
    std::vector<std::shared_ptr<TextureUnit> > m_textureUnits;
};

}
