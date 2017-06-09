#pragma once
#include <memory>
#include <vector>

namespace GLES2{

class Batch;
class RenderOperation;
class Camera;
class Matrix4x4;
class ShaderProgram;
class RenderState;

class Renderer
{
public:
    Renderer();

public:
    RenderState& getRenderState();

    void render(std::shared_ptr<RenderOperation> ros);
    void updateProjection(std::shared_ptr<Camera> cam, std::shared_ptr<Matrix4x4> modelMatrix);

    void render(std::shared_ptr<Camera> cam, std::shared_ptr<Matrix4x4> modelMatrix, std::shared_ptr<Batch> batch);
    void render(std::shared_ptr<Camera> cam, std::shared_ptr<Matrix4x4> modelMatrix, std::shared_ptr<RenderOperation> ro);
    void render(std::shared_ptr<Camera> cam, std::shared_ptr<Matrix4x4> modelMatrix, std::vector<std::shared_ptr<RenderOperation> > ro);


private:
    RenderState* m_renderState;
    std::shared_ptr<ShaderProgram> m_shader;
    std::shared_ptr<Matrix4x4> m_modelViewMatrix;
    std::shared_ptr<Matrix4x4> m_modelViewProjMatrix;
};


}
