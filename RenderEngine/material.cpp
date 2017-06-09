#include "material.h"
#include "textureunit.h"

using namespace GLES2;
Material::Material()
{

}

Material::~Material()
{

}

void Material::addTexture(std::shared_ptr<Texture> texture, unsigned int unit)
{
    m_textureUnits.emplace_back(std::make_shared<TextureUnit>(texture, unit));
}
