#pragma once
#include <memory>

namespace GLES2 {

class Mesh;
class Material;

class Entity
{
public:
    Entity();

public:

private:
    Mesh* m_mesh;
    Material* m_material;
};

}
