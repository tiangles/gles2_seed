#ifndef GLES2WIDGET_H
#define GLES2WIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <memory>

namespace GLES2 {
class Matrix4x4;
class Camera;
class Renderer;
}

class Rectangle;
class GLES2Widget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLES2Widget(const QString& resourceRoot, QWidget *parent = 0);
    ~GLES2Widget();

public:
    void setShader(const QString& shaderName);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void wheelEvent(QWheelEvent *event);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QString m_resourceRoot;

    std::shared_ptr<GLES2::Renderer> m_renderer;
    std::shared_ptr<GLES2::Camera> m_camera;

    std::shared_ptr<Rectangle> m_rectangle;
};

#endif // GLES2WIDGET_H
