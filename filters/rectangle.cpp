#include "rectangle.h"
#include "RenderEngine/vertex.h"
#include "RenderEngine/mesh.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/entity.h"
#include "RenderEngine/material.h"
#include "RenderEngine/texture.h"
#include "RenderEngine/submesh.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/renderer.h"


Rectangle::Rectangle(const std::string& resourceFolder,
                     std::shared_ptr<GLES2::Renderer> renderer)
    :m_resourceFolder(resourceFolder)
    ,m_renderer(renderer)
{
    build();
    setShader("embossment");

    m_modelMatrix = std::make_shared<GLES2::Matrix4x4>();
    m_modelMatrix->buffer[0][0] = 6.38;
    m_modelMatrix->buffer[1][1] = 9.6;
}

void Rectangle::build()
{
    static const GLES2::VertexDataPT vert[] = {
        // front
        {{-1.0f, -1.0f,  -1.0f},{0.0, 1.0}},
        {{ 1.0f, -1.0f,  -1.0f},{1.0, 1.0}},
        {{ 1.0f,  1.0f,  -1.0f},{1.0, 0.0}},
        {{-1.0f,  1.0f,  -1.0f},{0.0, 0.0}},
    };
    static const short indic[] = {
        0,  1,  2,  0,  2,  3
    };

    //create mesh
    auto vertex = std::make_shared<GLES2::Vertex>();
    vertex->build(vert, sizeof(vert)/sizeof(GLES2::VertexDataPT));

    auto indices = std::make_shared<GLES2::Indices>();
    indices->build(indic, sizeof(indic));

    auto subMesh = std::make_shared<GLES2::SubMesh>(vertex, indices);

    auto mesh = std::make_shared<GLES2::Mesh>();
    mesh->addSubMesh(subMesh);

    m_entity = std::make_shared<GLES2::Entity>(mesh);


    m_texture = std::make_shared<GLES2::Texture>();
    m_texture->build(m_resourceFolder + "img/succulent.jpeg");
}

void Rectangle::setShader(const std::string &name)
{
    //create material
    m_shaderProgram = std::make_shared<GLES2::ShaderProgram>();
    std::string fileName = m_resourceFolder + "shaders/fliters/" + name;
    m_shaderProgram->loadFromFile(fileName + ".vert",
                                  fileName + ".frag");
    m_shaderProgram->use();

    auto mat = std::make_shared<GLES2::Material>();
    mat->addTexture(m_texture);
    mat->setShaderProgram(m_shaderProgram);
    m_entity->setMaterial(mat);
}

void Rectangle::draw(std::shared_ptr<GLES2::Camera> camera) const
{
    m_renderer->render(camera, m_modelMatrix, m_entity->getRenderOperation());
}
