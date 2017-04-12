#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/camera.h"
#include "cube.h"
#include <QWheelEvent>

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_projMatrix = std::make_shared<Matrix4x4>();
    m_camera = std::make_shared<GLES2::Camera>();
    m_z = 2;
}

GLES2Widget::~GLES2Widget()
{
}

bool GLES2Widget::event(QEvent *event)
{
    qWarning("GLES2Widget::event: %d", event->type());
    if(event->type() == QEvent::KeyRelease){
        keyPressEvent(static_cast<QKeyEvent*>(event));
    }
    return QOpenGLWidget::event(event);
}

void GLES2Widget::wheelEvent(QWheelEvent *event)
{
    float d = 0;
    if(event->delta()>0){
        d = -1;
        m_z -= 0.5;
    } else if(event->delta()<0){
        m_z += 0.5;
        d = 1;
    }
    m_camera->move(0, 0, d);

    update();
    event->accept();
}

void GLES2Widget::keyPressEvent(QKeyEvent *event)
{
    keyReleaseEvent(event);
}

void GLES2Widget::keyReleaseEvent(QKeyEvent *event)
{
    float angle = 10*3.14/180;
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

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_cube = std::make_shared<Cube>("/home/btian/workspace/opengles2/");
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearDepthf(1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    m_camera->set(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
}

void GLES2Widget::resizeGL(int w, int h)
{
    Matrix4x4 mat = Matrix4x4Util::BuildPerspectiveMatrix(45.0, (float)w/h, 1.0f, 10000.0);
    memcpy(m_projMatrix->buffer, mat.buffer, sizeof(mat));
}

void GLES2Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_cube->resize(m_projMatrix);
    m_cube->render(m_camera->viewMatrix());
}
