#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "gles2rectangle.h"
#include "RenderEngine/matrix4x4.h"

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_projMatrix = std::make_shared<Matrix4x4>();
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_rect = new GLES2Rectangle();


    glClearColor(0.f, 0.5f, 0.5f, 1.f);
}

void GLES2Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    Matrix4x4 mat = Matrix4x4Util::BuildPerspectiveMatrix(65.0, (float)w/h, -10, 10);
    memcpy(m_projMatrix->buffer, mat.buffer, sizeof(mat));
}

void GLES2Widget::paintGL()
{
    m_rect->render(m_projMatrix);
}
