#pragma once
#include <memory>

namespace GLES2 {
class Vertex;
class Indices;
class ShaderProgram;
class SubMesh
{
public:
    SubMesh(std::shared_ptr<Vertex> vertex, std::shared_ptr<Indices> indices);
    ~SubMesh();

public:
    auto getVertex() const {return m_vertex; }
    auto getIndices() const {return m_indices; }
    void render(std::shared_ptr<ShaderProgram> shader);
private:
    std::shared_ptr<Vertex> m_vertex;
    std::shared_ptr<Indices> m_indices;
};
}
