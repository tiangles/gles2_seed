#include "material.h"

using namespace GLES2;
Material::Material(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Texture> texture)
    :m_shaderProgram(shaderProgram)
    ,m_texture(texture)
{

}

Material::~Material()
{

}
