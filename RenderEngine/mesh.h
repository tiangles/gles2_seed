#pragma once
#include <vector>
#include <memory>

namespace GLES2 {
class SubMesh;
class Mesh
{
public:
    Mesh();
    ~Mesh();

public:
    void addSubMesh(std::shared_ptr<SubMesh> subMesh) { m_subMeshes.emplace_back(subMesh);}
    size_t subMeshCount() const {return m_subMeshes.size();}
    auto subMesh(size_t index) const { return m_subMeshes[index]; }
    auto subMeshes() const { return m_subMeshes;}
private:
    std::vector<std::shared_ptr<SubMesh> > m_subMeshes;
};
}
