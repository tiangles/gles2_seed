#pragma once
#include <memory>

namespace GLES2 {
class Vertex;
class Indices;
class Mesh
{
public:
    Mesh(std::shared_ptr<Vertex> vertex, std::shared_ptr<Indices> indices);
    ~Mesh();

public:
    auto getVertex() const {return m_vertex; }

    auto getIndices() const {return m_indices; }

    void render();
private:
    std::shared_ptr<Vertex> m_vertex;
    std::shared_ptr<Indices> m_indices;
};
}
