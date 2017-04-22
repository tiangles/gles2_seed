#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/camera.h"
#include "RenderEngine/renderer.h"
#include "cube.h"
#include <QWheelEvent>

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_renderer = std::make_shared<Renderer>();
    m_camera = std::make_shared<Camera>();
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    QSurfaceFormat f = format();
    f.setSamples(49);
    setFormat(f);
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::wheelEvent(QWheelEvent *event)
{
    float d = 0;
    if(event->delta()>0){
        d = -1.5;
    } else if(event->delta()<0){
        d = 1.5;
    }
    m_camera->move(0, 0, d);
    update();
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_cube = std::make_shared<Cube>(m_renderer, "/home/btian/workspace/opengles2/");

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepth(1.0f);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearDepthf(1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    m_camera->set(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));
    m_timer->start(10);
}

void GLES2Widget::resizeGL(int w, int h)
{
    m_camera->setAsPrespective(45.0, (float)w/h, 0.1f, 100.0);
}

void GLES2Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_cube->render(m_camera);
}

void GLES2Widget::keyReleaseEvent(QKeyEvent *event)
{
    float angle = 5*3.14/180;
    switch(event->key()){
    case Qt::Key_Up:
        m_camera->roll(angle);
        break;
    case Qt::Key_Down:
        m_camera->roll(-angle);
        break;
    case Qt::Key_Left:
        m_camera->yaw(angle);
        break;
    case Qt::Key_Right:
        m_camera->yaw(-angle);
        break;
    case Qt::Key_A:
        m_camera->pitch(angle);
        break;
    case Qt::Key_S:
        m_camera->pitch(-angle);
        break;
    default:
        break;
    }
    update();
    event->accept();
}

void GLES2Widget::onTimer()
{
    m_camera->yaw(0.25*3.14159268/180);
    m_cube->rotate();
    update();
}
