#pragma once
#include <memory>
#include "vec.h"

namespace GLES2 {
class ShaderProgram;
class Renderer;

class Light
{
public:
    enum Type{
        AMBIENT,
        DIRECTIONAL,
        POINT,
        SPOT
    };
    Light(Type type): m_type(type){}

public:
    void apply(Renderer& renderer, std::shared_ptr<ShaderProgram> shader);

    void setPosition(const vec3& pos) { m_lightPos = pos;}
    void setAmbient(const vec4& ambient){ m_ambient = ambient; }
    void setDiffuse(const vec4& diffuse){ m_diffuse = diffuse; }
    void setSpecular(const vec4& specular){ m_specular = specular; }
private:
    Type m_type;

    vec4 m_ambient;
    vec4 m_diffuse;
    vec4 m_specular;

    vec3 m_lightPos;
};


}
