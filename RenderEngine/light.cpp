#include "light.h"
#include "shaderprogram.h"

using namespace GLES2;

void Light::apply(std::shared_ptr<ShaderProgram> shader)
{
    shader->use();
    shader->setUniformfv("u_ambient", 4, (float*)&m_ambient);
    shader->setUniformfv("u_diffuse", 4, (float*)&m_diffuse);
    shader->setUniformfv("u_specular", 4, (float*)&m_specular);
    shader->setUniformfv("u_lightPos", 3, (float*)&m_lightPos);
}
