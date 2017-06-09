#pragma once
#include <memory>
#include <vector>

namespace GLES2{

class Vertex;
class Indices;
class ShaderProgram;
class TextureUnit;

struct RenderOperation{
    std::shared_ptr<Vertex>                 vertex;
    std::shared_ptr<Indices>                indices;
    std::shared_ptr<ShaderProgram>          shader;
    std::vector<std::shared_ptr<TextureUnit> >  textureUnits;
};
}
