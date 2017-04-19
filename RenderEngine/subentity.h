#pragma once
#include <memory>

namespace GLES2 {

class SubMesh;
class Material;
class RenderOperation;

class SubEntity{
public:
    SubEntity(std::shared_ptr<SubMesh> subMesh);

public:
    void setMaterial(std::shared_ptr<Material> material);

    std::shared_ptr<RenderOperation> getRenderOperation() const;

private:
    std::shared_ptr<SubMesh> m_subMesh;
    std::shared_ptr<Material> m_material;
};

}
