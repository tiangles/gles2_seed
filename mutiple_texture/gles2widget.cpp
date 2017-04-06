#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "fragment.h"

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_fragment = std::make_shared<Fragment>("/home/btian/workspace/opengles2/");

    glClearColor(1.f, 1.f, 1.f, 1.f);
}

void GLES2Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w/2, h/2);
    m_fragment->resize(w, h);
}

void GLES2Widget::paintGL()
{
    m_fragment->render();
}
