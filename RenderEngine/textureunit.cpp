#include "textureunit.h"
#include "texture.h"

GLES2::TextureUnit::TextureUnit(std::shared_ptr<GLES2::Texture> texture, GLuint unit)
    :m_texture(texture)
    ,m_unit(unit)
{
}

void GLES2::TextureUnit::bind() const
{
    m_texture->bind(m_unit);
}
