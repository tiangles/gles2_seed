#pragma once
#include <memory>
#include <vector>
#include <qopenglfunctions.h>
#include <QObject>
#include <QTimer>

namespace GLES2{
    class Entity;
    class Texture;
    class ShaderProgram;
    struct Matrix4x4;
    class Light;
    class Camera;
    class Renderer;
}

class Cube: public QObject, public QOpenGLFunctions
{
    Q_OBJECT
public:
    Cube(std::shared_ptr<GLES2::Renderer> renderer, const std::string& resRoot);

public:
    void render(std::shared_ptr<GLES2::Camera> camera);

public slots:
    void rotate();

private:
    void build();
    std::shared_ptr<GLES2::Texture> loadTexture();

private:
    std::shared_ptr<GLES2::Renderer> m_renderer;
    std::shared_ptr<GLES2::ShaderProgram> m_shaderProgram;
    std::shared_ptr<GLES2::Entity> m_entity;
    std::shared_ptr<GLES2::Light> m_light;

    std::shared_ptr<GLES2::Matrix4x4> m_projMatrix;
    std::shared_ptr<GLES2::Matrix4x4> m_modelMatrix;

    std::string m_resRoot;
    float m_rotate;

    std::shared_ptr<GLES2::Texture> m_texture;
};
