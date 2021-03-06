#include "gles2widget.h"
#include "RenderEngine/flyingcamera.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/camera.h"
#include "RenderEngine/skybox.h"
#include "RenderEngine/renderer.h"
#include "cube.h"
#include <QWheelEvent>

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_camera = std::make_shared<Camera>();
    FlyingCamera::KeySetting keySetting;
    keySetting.keyBackward = Qt::Key_S;
    keySetting.keyForwad= Qt::Key_W;
    keySetting.keyLeft = Qt::Key_A;
    keySetting.keyRight = Qt::Key_D;
    keySetting.rotateSensitivity = 0.1*3.14159267f/180.f;
    keySetting.slideSensitivity = 1;

    m_flyingCamera = std::make_shared<FlyingCamera>(m_camera, keySetting);
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    QSurfaceFormat f = format();
    f.setSamples(49);
    setFormat(f);
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();

    m_renderer = std::make_shared<Renderer>();
    m_skybox = std::make_shared<Skybox>(m_renderer);
    std::vector<std::string> textures;
    textures.push_back("img/skybox/front.jpg");
    textures.push_back("img/skybox/back.jpg");
    textures.push_back("img/skybox/up.jpg");
    textures.push_back("img/skybox/down.jpg");
    textures.push_back("img/skybox/right.jpg");
    textures.push_back("img/skybox/left.jpg");
    m_skybox->create("/home/btian/workspace/opengles2/", textures);

    m_cube = std::make_shared<Cube>(m_renderer, "/home/btian/workspace/opengles2/");

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);


    m_camera->set(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));
    m_timer->start(10);
}

void GLES2Widget::resizeGL(int w, int h)
{
    m_flyingCamera->onViewSize(w, h);
    m_camera->setAsPrespective(65.0, (float)w/h, 1.f, 1000.0f);
}

void GLES2Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_skybox->render(m_camera);
    m_cube->render(m_camera);
}

void GLES2Widget::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    m_flyingCamera->onMouseDown(pos.x(), pos.y());
}

void GLES2Widget::keyReleaseEvent(QKeyEvent *event)
{
    m_flyingCamera->onKeyRelease(event->key());
    update();
    event->accept();
}

void GLES2Widget::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    m_flyingCamera->onMouseMove(pos.x(), pos.y());
}

void GLES2Widget::wheelEvent(QWheelEvent *event)
{
    float d = 0;
    if(event->delta()>0){
        d = -1.5;
    } else if(event->delta()<0){
        d = 1.5;
    }
    m_camera->translate(vec3(0, 0, d));
    update();
}

void GLES2Widget::onTimer()
{
    m_cube->rotate();
    update();
}
