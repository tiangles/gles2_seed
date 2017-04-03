#include "material.h"

using namespace GLES2;
Material::Material(std::shared_ptr<ShaderProgram> shaderProgram,
                   std::vector<std::shared_ptr<Texture> > textures)
    :m_shaderProgram(shaderProgram)
    ,m_textures(textures)
{

}

Material::~Material()
{

}
