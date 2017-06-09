#include "textureunit.h"
#include "texture.h"
#include "renderstate.h"

GLES2::TextureUnit::TextureUnit(std::shared_ptr<GLES2::Texture> texture, GLuint unit)
    :m_texture(texture)
    ,m_unit(unit)
{
}

void GLES2::TextureUnit::bind(RenderState& renderState) const
{
    renderState.textureUnit(m_unit);
    renderState.texture(m_texture->target(), m_texture->texId());
}
