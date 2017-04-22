#include "cube.h"
#include "RenderEngine/vertex.h"
#include "RenderEngine/mesh.h"
#include "RenderEngine/entity.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/texture.h"
#include "RenderEngine/material.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/light.h"
#include "RenderEngine/vec.h"
#include "RenderEngine/camera.h"
#include "RenderEngine/submesh.h"
#include "RenderEngine/renderer.h"

Cube::Cube(std::shared_ptr<GLES2::Renderer> renderer, const std::string& resRoot)
    :m_renderer(renderer)
    ,m_resRoot(resRoot)
    ,m_rotate(0)
    ,m_updated(true)
{
    initializeOpenGLFunctions();

    build();

    m_projMatrix = std::make_shared<GLES2::Matrix4x4>();
    m_modelMatrix = std::make_shared<GLES2::Matrix4x4>();

    m_light = std::make_shared<GLES2::Light>(GLES2::Light::DIRECTIONAL);
    m_light->setAmbient(GLES2::vec4(0.4, 0.4, 0.4, 1.0));
    m_light->setDiffuse(GLES2::vec4(1., 1., 1., 1.0));
    m_light->setPosition(GLES2::vec3(1000, 1000, 1000));
    m_light->apply(m_shaderProgram);
}

void Cube::resize(std::shared_ptr<GLES2::Matrix4x4> projMatrix)
{
    m_projMatrix = projMatrix;
    m_shaderProgram->setUniformMatrix4fv("u_projMatrix", m_projMatrix->buffer[0]);
    m_updated = true;
}

void Cube::rotate()
{
    m_rotate += 1*3.14/180;
    GLES2::Matrix4x4 m = GLES2::Matrix4x4Util::BuildRotateMatrix(GLES2::vec3(1, 1, 1), m_rotate);
    m_modelMatrix->operator =(m);
    m_updated = true;
}

void Cube::render(std::shared_ptr<GLES2::Camera> camera)
{
    m_renderer->render(camera, m_modelMatrix, m_entity->getRenderOperation());
    m_updated = false;
}

void Cube::build()
{
    static const GLES2::VertexDataPNT vert[] = {
        // front
        {{-1.0f, -1.0f,  1.0f}, {0, 0, 1}, {0.0, 1.0}},
        {{ 1.0f, -1.0f,  1.0f}, {0, 0, 1}, {1.0, 1.0}},
        {{ 1.0f,  1.0f,  1.0f}, {0, 0, 1}, {1.0, 0.0}},
        {{-1.0f,  1.0f,  1.0f}, {0, 0, 1}, {0.0, 0.0}},
        //back {0, 0, 0},
        {{-1.0f, -1.0f, -1.0f}, {0, 0, -1}, {1.0, 0.0}},
        {{ 1.0f, -1.0f, -1.0f}, {0, 0, -1}, {0.0, 0.0}},
        {{ 1.0f,  1.0f, -1.0f}, {0, 0, -1}, {0.0, 1.0}},
        {{-1.0f,  1.0f, -1.0f}, {0, 0, -1}, {1.0, 1.0}},
        //top {0, 0, 0},
        {{ 1.0f,  1.0f,  1.0f}, {0, 1, 0}, {1.0, 1.0}},
        {{-1.0f,  1.0f,  1.0f}, {0, 1, 0}, {0.0, 1.0}},
        {{-1.0f,  1.0f, -1.0f}, {0, 1, 0}, {0.0, 0.0}},
        {{ 1.0f,  1.0f, -1.0f}, {0, 1, 0}, {1.0, 0.0}},
        //bottom {0, 0, 0},
        {{ 1.0f, -1.0f,  1.0f}, {0, -1, 0}, {0.0, 0.0}},
        {{-1.0f, -1.0f,  1.0f}, {0, -1, 0}, {1.0, 0.0}},
        {{-1.0f, -1.0f, -1.0f}, {0, -1, 0}, {1.0, 1.0}},
        {{ 1.0f, -1.0f, -1.0f}, {0, -1, 0}, {0.0, 1.0}},
        //right {0, 0, 0},
        {{ 1.0f, -1.0f,  1.0f}, {1, 0, 0}, {0.0, 1.0}},
        {{ 1.0f,  1.0f,  1.0f}, {1, 0, 0}, {1.0, 1.0}},
        {{ 1.0f,  1.0f, -1.0f}, {1, 0, 0}, {1.0, 0.0}},
        {{ 1.0f, -1.0f, -1.0f}, {1, 0, 0}, {0.0, 0.0}},
        //left {0, 0, 0},
        {{-1.0f, -1.0f,  1.0f}, {-1, 0, 0}, {1.0, 0.0}},
        {{-1.0f,  1.0f,  1.0f}, {-1, 0, 0}, {0.0, 0.0}},
        {{-1.0f,  1.0f, -1.0f}, {-1, 0, 0}, {0.0, 1.0}},
        {{-1.0f, -1.0f, -1.0f}, {-1, 0, 0}, {1.0, 1.0}},
    };

    static const short indic[] = {
        0,  1,  2,  0,  2,  3,   // front
        4,  6,  5,  4,  7,  6,   // back
        8,  10, 9,  8,  11, 10,   //top
        12, 13, 14, 12, 14, 15,   //bottom
        16, 18, 17, 16, 19, 18,   //right
        20, 21, 22, 20, 22, 23,   //left
    };
    //create mesh
    auto vertex = std::make_shared<GLES2::Vertex>();
    vertex->build(vert, sizeof(vert)/sizeof(GLES2::VertexDataPNT));
    auto indices = std::make_shared<GLES2::Indices>();
    indices->build(indic, sizeof(indic));
    auto subMesh = std::make_shared<GLES2::SubMesh>(vertex, indices);

    auto mesh = std::make_shared<GLES2::Mesh>();
    mesh->addSubMesh(subMesh);

    //create material
    m_shaderProgram = std::make_shared<GLES2::ShaderProgram>();
    m_shaderProgram->loadFromFile(m_resRoot + "shaders/light.vert", m_resRoot + "shaders/light.frag");
    m_shaderProgram->use();

    std::shared_ptr<GLES2::Material> mat = std::make_shared<GLES2::Material>();
    mat->addTexture(loadTexture());
    mat->setShaderProgram(m_shaderProgram);

    m_entity = std::make_shared<GLES2::Entity>(mesh);
    m_entity->setMaterial(mat);
}

struct TextureUnit{
    const char* texture_name;
    const char* shaderLocation;
};

std::shared_ptr<GLES2::Texture> Cube::loadTexture()
{
//    auto tex = std::make_shared<GLES2::Texture>();
//    tex->build(m_resRoot + "img/crate.jpg");
//    return std::move(tex);
    m_texture = std::make_shared<GLES2::Texture>();
    m_texture->build(m_resRoot + "img/crate.jpg");
    return m_texture;
}
