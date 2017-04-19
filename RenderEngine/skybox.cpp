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

using namespace GLES2;


Skybox::Skybox()
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
        0,  1,  2,  0,  2,  3,   // front
        4,  6,  5,  4,  7,  6,   // back
        8,  10, 9,  8,  11, 10,   //top
        12, 13, 14, 12, 14, 15,   //bottom
        16, 18, 17, 16, 19, 18,   //right
        20, 21, 22, 20, 22, 23,   //left
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
        mat->addTexture(tex);
        m_entity->getSubEntities()[i]->setMaterial(mat);
    }
}

void Skybox::render(std::shared_ptr<Camera> camera)
{
    auto projMatrix = camera->projMatrix();
    auto viewMatrix = camera->viewMatrix();
    auto modelViewMatrix = std::make_shared<Matrix4x4>();
    auto modelViewProjMatrix = std::make_shared<Matrix4x4>();

    vec3 cameraPos = camera->position();
    m_modelMatrix->buffer[0][3] = cameraPos.x;
    m_modelMatrix->buffer[1][3] = cameraPos.y;
    m_modelMatrix->buffer[2][3] = cameraPos.z;

    *modelViewMatrix = *viewMatrix *(*m_modelMatrix);
    *modelViewProjMatrix = *projMatrix * *modelViewMatrix;

    m_shaderProgram->use();
    m_shaderProgram->setUniformMatrix4fv("u_modelViewProjMatrix", modelViewProjMatrix->buffer[0]);
    for(auto ro: m_entity->getRenderOperation()){
        ro->vertex->bind(m_shaderProgram);
        ro->textures[0]->bind(0);
        ro->indices->draw();
    }

}
