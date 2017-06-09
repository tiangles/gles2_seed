#include "renderer.h"
#include "renderstate.h"
#include "matrix4x4.h"
#include "renderoperation.h"
#include "camera.h"
#include "shaderprogram.h"
#include "vertex.h"
#include "textureunit.h"

using namespace GLES2;

Renderer::Renderer()
{
    m_modelViewMatrix = std::make_shared<Matrix4x4>();
    m_modelViewProjMatrix = std::make_shared<Matrix4x4>();
    m_renderState = new RenderState();
}

RenderState &Renderer::getRenderState()
{
    return *m_renderState;
}

void Renderer::updateProjection(std::shared_ptr<Camera> camera, std::shared_ptr<Matrix4x4> modelMatrix)
{
    auto projMatrix = camera->projMatrix();
    auto viewMatrix = camera->viewMatrix();

    *m_modelViewMatrix = *viewMatrix * *modelMatrix;
    *m_modelViewProjMatrix = *projMatrix * *m_modelViewMatrix;

    m_shader->setUniformMatrix4fv("u_projMatrix", true, projMatrix->buffer[0]);
    m_shader->setUniformMatrix4fv("u_modelMatrix", true, modelMatrix->buffer[0]);
    m_shader->setUniformMatrix4fv("u_viewMatrix", true, viewMatrix->buffer[0]);
    m_shader->setUniformMatrix4fv("u_modelViewMatrix", true, m_modelViewMatrix->buffer[0]);
    m_shader->setUniformMatrix4fv("u_modelViewProjMatrix", true, m_modelViewProjMatrix->buffer[0]);
}

void Renderer::render(std::shared_ptr<RenderOperation> ro)
{
    ro->vertex->bind(m_shader);
    for(std::shared_ptr<TextureUnit>& textureUnit: ro->textureUnits){
        textureUnit->bind(getRenderState());
    }

    ro->indices->draw();
}

void Renderer::render(std::shared_ptr<Camera> /*cam*/, std::shared_ptr<Matrix4x4> /*modelMatrix*/, std::shared_ptr<Batch> /*batch*/)
{

}

void Renderer::render(std::shared_ptr<Camera> camera, std::shared_ptr<Matrix4x4> modelMatrix, std::shared_ptr<RenderOperation> ro)
{
    m_shader = ro->shader;
    m_shader->use(*this);
    updateProjection(camera, modelMatrix);
    render(ro);
}

void Renderer::render(std::shared_ptr<Camera> camera, std::shared_ptr<Matrix4x4> modelMatrix, std::vector<std::shared_ptr<RenderOperation> > ros)
{
    for(auto ro: ros){
        render(camera, modelMatrix, ro);
    }
}

