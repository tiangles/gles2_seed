#include "cube.h"
#include "RenderEngine/vertex.h"
#include "RenderEngine/mesh.h"
#include "RenderEngine/entity.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/texture.h"
#include "RenderEngine/material.h"
#include "RenderEngine/matrix4x4.h"

Cube::Cube(const std::string& resRoot)
    :m_resRoot(resRoot)
{
    initializeOpenGLFunctions();
    m_modelViewMatrix = std::make_shared<GLES2::Matrix4x4>();
    build();
}

void Cube::resize(std::shared_ptr<GLES2::Matrix4x4> projMatrix)
{
    m_projMatrix = projMatrix;
}

void Cube::render()
{
    m_entity->render(m_projMatrix, m_modelViewMatrix);
}

void Cube::render(std::shared_ptr<GLES2::Matrix4x4> modelViewMatrix)
{
    m_entity->render(m_projMatrix, modelViewMatrix);
}

void Cube::build()
{
    static const GLES2::VertexDataPT vert[] = {
        // front
        {{-1.0f, -1.0f,  1.0f},{0.0, 1.0}},
        {{ 1.0f, -1.0f,  1.0f},{1.0, 1.0}},
        {{ 1.0f,  1.0f,  1.0f},{1.0, 0.0}},
        {{-1.0f,  1.0f,  1.0f},{0.0, 0.0}},

        //back
        {{-1.0f, -1.0f, -1.0f},{1.0, 0.0}},
        {{ 1.0f, -1.0f, -1.0f},{0.0, 0.0}},
        {{ 1.0f,  1.0f, -1.0f},{0.0, 1.0}},
        {{-1.0f,  1.0f, -1.0f},{1.0, 1.0}},

        //top
        {{ 1.0f,  1.0f,  1.0f},{1.0, 1.0}},
        {{-1.0f,  1.0f,  1.0f},{0.0, 1.0}},
        {{-1.0f,  1.0f, -1.0f},{0.0, 0.0}},
        {{ 1.0f,  1.0f, -1.0f},{1.0, 0.0}},

        //bottom
        {{ 1.0f, -1.0f,  1.0f},{0.0, 0.0}},
        {{-1.0f, -1.0f,  1.0f},{1.0, 0.0}},
        {{-1.0f, -1.0f, -1.0f},{1.0, 1.0}},
        {{ 1.0f, -1.0f, -1.0f},{0.0, 1.0}},

        //right
        {{ 1.0f, -1.0f,  1.0f},{0.0, 1.0}},
        {{ 1.0f,  1.0f,  1.0f},{1.0, 1.0}},
        {{ 1.0f,  1.0f, -1.0f},{1.0, 0.0}},
        {{ 1.0f, -1.0f, -1.0f},{0.0, 0.0}},

        //left
        {{-1.0f, -1.0f,  1.0f},{1.0, 0.0}},
        {{-1.0f,  1.0f,  1.0f},{0.0, 0.0}},
        {{-1.0f,  1.0f, -1.0f},{0.0, 1.0}},
        {{-1.0f, -1.0f, -1.0f},{1.0, 1.0}},
    };

    static const short indic[] = {
        0,  1,  2,  0,  2,  3,   // front
        4,  5,  6,  4,  6,  7,   // back
        8,  10, 9,  8,  11, 10,   //top
        12, 13, 14, 12, 14, 15,   //bottom
        16, 18, 17, 16, 19, 18,   //right
        20, 21, 22, 20, 22, 23,   //left
    };
    //create mesh
    std::shared_ptr<GLES2::Vertex> vertex = std::make_shared<GLES2::Vertex>();
    vertex->build(vert, sizeof(vert)/sizeof(GLES2::VertexDataPT));
    std::shared_ptr<GLES2::Indices> indices = std::make_shared<GLES2::Indices>();
    indices->build(indic, sizeof(indic));
    std::shared_ptr<GLES2::Mesh> mesh = std::make_shared<GLES2::Mesh>(vertex, indices);

    //create material
    m_shaderProgram = std::make_shared<GLES2::ShaderProgram>();
    m_shaderProgram->loadFromFile(m_resRoot + "shaders/cube.vert", m_resRoot + "shaders/cube.frag");
    m_shaderProgram->use();

    std::shared_ptr<GLES2::Material> mat = std::make_shared<GLES2::Material>(m_shaderProgram, loadTexture());
    m_entity = std::make_shared<GLES2::Entity>(mesh);
    m_entity->setMaterial(mat);
}

struct TextureUnit{
    const char* texture_name;
    const char* shaderLocation;
};

std::vector<std::shared_ptr<GLES2::Texture> > Cube::loadTexture()
{
    TextureUnit textures[] = {
        {"img/city.jpg", "u_texture0"},
    };

    std::vector<std::shared_ptr<GLES2::Texture> >  result;
    for(size_t i=0; i<sizeof(textures)/sizeof(TextureUnit); ++i){
        auto tex = std::make_shared<GLES2::Texture>();
        tex->build(m_resRoot + std::string(textures[i].texture_name));
        result.push_back(tex);
        m_shaderProgram->setUniformi(textures[i].shaderLocation, i);
    }
    return std::move(result);
}
