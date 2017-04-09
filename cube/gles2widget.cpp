#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "cube.h"
#include <QWheelEvent>

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_modelviewMatrix = std::make_shared<Matrix4x4>();
    m_projMatrix = std::make_shared<Matrix4x4>();
    m_z = 0;
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0){
        m_z -= 0.5;
    } else if(event->delta()<0){
        m_z += 0.5;
    }
    m_modelviewMatrix->buffer[2][3] = m_z;
    update();
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_cube = std::make_shared<Cube>("/home/btian/workspace/opengles2/");
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    glCullFace(GL_BACK);
//    glEnable(GL_CULL_FACE);

    glClearDepthf(1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
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
    m_cube->render(m_modelviewMatrix);
}
