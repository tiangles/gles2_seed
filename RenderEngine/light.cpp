#include "light.h"
#include "shaderprogram.h"

using namespace GLES2;

void Light::apply(Renderer& renderer, std::shared_ptr<ShaderProgram> shader)
{
    shader->use(renderer);
    shader->setUniform4f("u_ambient", m_ambient.r, m_ambient.g, m_ambient.b, m_ambient.a);
    shader->setUniform4f("u_diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b, m_diffuse.a);
    shader->setUniformfv("u_lightPos", 3, (float*)&m_lightPos);
}
