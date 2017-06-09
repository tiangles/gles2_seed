#include "skybox.h"
#include "camera.h"
#include "matrix4x4.h"
#include "entity.h"
#include "vertex.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "submesh.h"
#include "texture.h"
#include "textureunit.h"
#include "material.h"
#include "renderoperation.h"
#include "subentity.h"
#include "renderer.h"

using namespace GLES2;


Skybox::Skybox(std::shared_ptr<Renderer> renderer)
    :m_renderer(renderer)
{
    m_modelMatrix = std::make_shared<Matrix4x4>();
}

void Skybox::create(const std::string& resRoot, std::vector<std::string> textureFiles)
{
    static const VertexDataPT vert[] = {
        // front
        {{-500.0f, -500.0f,  500.0f}, {1.0, 1.0}},
        {{ 500.0f, -500.0f,  500.0f}, {0.0, 1.0}},
        {{ 500.0f,  500.0f,  500.0f}, {0.0, 0.0}},
        {{-500.0f,  500.0f,  500.0f}, {1.0, 0.0}},
        //back
        {{-500.0f, -500.0f, -500.0f}, {0.0, 1.0}},
        {{ 500.0f, -500.0f, -500.0f}, {1.0, 1.0}},
        {{ 500.0f,  500.0f, -500.0f}, {1.0, 0.0}},
        {{-500.0f,  500.0f, -500.0f}, {0.0, 0.0}},
        //top
        {{ 500.0f,  500.0f,  500.0f}, {1.0, 1.0}},
        {{-500.0f,  500.0f,  500.0f}, {1.0, 0.0}},
        {{-500.0f,  500.0f, -500.0f}, {0.0, 0.0}},
        {{ 500.0f,  500.0f, -500.0f}, {0.0, 1.0}},
        //bottom
        {{ 500.0f, -500.0f,  500.0f}, {1.0, 0.0}},
        {{-500.0f, -500.0f,  500.0f}, {1.0, 1.0}},
        {{-500.0f, -500.0f, -500.0f}, {0.0, 1.0}},
        {{ 500.0f, -500.0f, -500.0f}, {0.0, 0.0}},
        //right
        {{ 500.0f, -500.0f,  500.0f}, {1.0, 1.0}},
        {{ 500.0f,  500.0f,  500.0f}, {1.0, 0.0}},
        {{ 500.0f,  500.0f, -500.0f}, {0.0, 0.0}},
        {{ 500.0f, -500.0f, -500.0f}, {0.0, 1.0}},
        //left
        {{-500.0f, -500.0f,  500.0f}, {0.0, 1.0}},
        {{-500.0f,  500.0f,  500.0f}, {0.0, 0.0}},
        {{-500.0f,  500.0f, -500.0f}, {1.0, 0.0}},
        {{-500.0f, -500.0f, -500.0f}, {1.0, 1.0}},
    };

    static const short indic[] = {
        0,  2,  1,  0,  3,  2,   // front
        4,  5,  6,  4,  6,  7,   // back
        8,  9, 10,  8,  10, 11,   //top
        12, 14, 13, 12, 15, 14,   //bottom
        16, 17, 18, 16, 18, 19,   //right
        20, 22, 21, 20, 23, 22,   //left
    };
    //create mesh
    auto mesh = std::make_shared<Mesh>();
    for(int i=0; i<6; ++i){
        auto vertex = std::make_shared<Vertex>();
        vertex->build(vert, sizeof(vert)/sizeof(VertexDataPT));
        auto indices = std::make_shared<Indices>();
        indices->build(indic+i*6, sizeof(short)*6);
        auto subMesh = std::make_shared<SubMesh>(vertex, indices);

        mesh->addSubMesh(subMesh);
    }

    //create entity
    m_entity = std::make_shared<Entity>(mesh);

    //create and set material
    m_shaderProgram = std::make_shared<ShaderProgram>();
    m_shaderProgram->loadFromFile(resRoot + "shaders/skybox.vert", resRoot + "shaders/skybox.frag");
    //load textures
    for(size_t i=0; i<textureFiles.size(); ++i){
        auto tex = std::make_shared<Texture>();
        tex->build(resRoot + std::string(textureFiles[i]));

        auto mat = std::make_shared<Material>();
        mat->setShaderProgram(m_shaderProgram);

        mat->addTexture(tex, 0);
        m_entity->getSubEntities()[i]->setMaterial(mat);
    }
}

void Skybox::render(std::shared_ptr<Camera> camera)
{
    m_shaderProgram->use(*m_renderer);
    vec3 cameraPos = camera->position();
    m_modelMatrix->buffer[0][3] = cameraPos.x;
    m_modelMatrix->buffer[1][3] = cameraPos.y;
    m_modelMatrix->buffer[2][3] = cameraPos.z;
    m_renderer->render(camera, m_modelMatrix, m_entity->getRenderOperation());
}
