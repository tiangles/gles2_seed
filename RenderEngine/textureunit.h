#pragma once
#include <memory>

namespace GLES2 {

class Texture;

class TextureUnit
{
public:
    TextureUnit(std::shared_ptr<Texture> texture, unsigned int unit);

public:
    void bind() const;

private:
    std::shared_ptr<Texture> m_texture;
    unsigned int m_unit;
};

}
