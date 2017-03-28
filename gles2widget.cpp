#include "gles2widget.h"
#include "shadersource.h"
#include "shaderprogram.h"
#include "gles2rectangle.h"
#include "matrix4x4.h"

using namespace GLES2;

GLES2Widget::GLES2Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_projMatrix = new Matrix4x4();
}

GLES2Widget::~GLES2Widget()
{
    delete m_projMatrix;
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    m_rect = new GLES2Rectangle();
    m_program = new ShaderProgram();
    m_program->setShaderSource(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
    m_program->build();

    Matrix4x4 mat = Matrix4x4Util::BuildOrthoMatrix(-1, 1, -1, 1, -1, 1.);
    memcpy(m_projMatrix, &mat, sizeof(mat));

    glClearColor(0.f, 0.5f, 0.5f, 1.f);
}

void GLES2Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLES2Widget::paintGL()
{
    m_program->use(*m_projMatrix);
    m_rect->render();

}
