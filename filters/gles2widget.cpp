#include "gles2widget.h"
#include "RenderEngine/shaderprogram.h"
#include "RenderEngine/matrix4x4.h"
#include "RenderEngine/camera.h"
#include "RenderEngine/renderer.h"
#include "rectangle.h"

#include <QWheelEvent>

using namespace GLES2;

GLES2Widget::GLES2Widget(const QString& resourceRoot, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_resourceRoot(resourceRoot)
{
    m_renderer = std::make_shared<Renderer>();
    m_camera = std::make_shared<Camera>();
    QSurfaceFormat f = format();
    f.setSamples(49);
    setFormat(f);
}

GLES2Widget::~GLES2Widget()
{
}

void GLES2Widget::setShader(const QString &shaderName)
{
    m_rectangle->setShader(shaderName.toStdString());
    update();
}

void GLES2Widget::wheelEvent(QWheelEvent */*event*/)
{
    update();
}

void GLES2Widget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepth(1.0f);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearDepthf(1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    m_camera->set(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));

    m_rectangle = std::make_shared<Rectangle>(m_resourceRoot.toStdString(), m_renderer);
}

void GLES2Widget::resizeGL(int w, int h)
{
    m_camera->setAsPrespective(45.0, (float)w/h, 0.1f, 100.0);
}

void GLES2Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    m_rectangle->draw(m_camera);
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
