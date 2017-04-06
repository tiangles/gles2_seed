#include "fragment.h"
#include "RenderEngine/vertex.h"
#include "RenderEngine/mesh.h"
#include "RenderEngine/entity.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/texture.h"
#include "RenderEngine/material.h"

Fragment::Fragment(const std::string& resRoot)
    :m_resRoot(resRoot)
{
    initializeOpenGLFunctions();
    build();
}

void Fragment::resize(int width, int height)
{
    m_shaderProgram->setUniform2f("u_resolution", width, height);
}

void Fragment::render()
{
    m_entity->render();
}

void Fragment::build()
{
    static float z=0.;
    static const GLES2::VertexDataPT vert[] = {
        {{-1.0f, -1.0f, z}, {0, 1}},
        {{ 1.0f, -1.0f, z}, {1, 1}},
        {{ 1.0f,  1.0f, z}, {1, 0}},
        {{-1.0f,  1.0f, z}, {0, 0}},
    };

    static const short indic[] = {
        0, 1, 2, 0, 2, 3
    };
    //create mesh
    std::shared_ptr<GLES2::Vertex> vertex = std::make_shared<GLES2::Vertex>();
    vertex->build(vert, sizeof(vert)/sizeof(GLES2::VertexDataPT));
    std::shared_ptr<GLES2::Indices> indices = std::make_shared<GLES2::Indices>();
    indices->build(indic, sizeof(indic));
    std::shared_ptr<GLES2::Mesh> mesh = std::make_shared<GLES2::Mesh>(vertex, indices);

    //create material
    m_shaderProgram = std::make_shared<GLES2::ShaderProgram>();
    m_shaderProgram->loadFromFile(m_resRoot + "shaders/mt.vert", m_resRoot + "shaders/mt.frag");
    m_shaderProgram->use();

    std::shared_ptr<GLES2::Material> mat = std::make_shared<GLES2::Material>(m_shaderProgram, loadTexture());
    m_entity = std::make_shared<GLES2::Entity>(mesh);
    m_entity->addMaterial(mat);
}

struct TextureUnit{
    const char* texture_name;
    const char* shaderLocation;
};

std::vector<std::shared_ptr<GLES2::Texture> > Fragment::loadTexture()
{
    TextureUnit textures[] = {
        {"img/color.png", "u_textureFg"},
        {"img/crate.jpg", "u_textureBg"}
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
