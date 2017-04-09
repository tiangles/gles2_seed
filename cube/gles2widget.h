#ifndef GLES2WIDGET_H
#define GLES2WIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <memory>

namespace GLES2 {
class Matrix4x4;
}
class Cube;
class GLES2Widget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLES2Widget(QWidget *parent = 0);
    ~GLES2Widget();
signals:

public slots:

protected:
    void wheelEvent(QWheelEvent *event);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    std::shared_ptr<Cube> m_cube;
    std::shared_ptr<GLES2::Matrix4x4> m_projMatrix;
    std::shared_ptr<GLES2::Matrix4x4> m_modelviewMatrix;

    float m_z;
};

#endif // GLES2WIDGET_H
