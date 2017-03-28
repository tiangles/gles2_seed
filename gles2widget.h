#ifndef GLES2WIDGET_H
#define GLES2WIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions.h>

namespace GLES2 {
class ShaderProgram;
class Matrix4x4;
}

class GLES2Rectangle;
class GLES2Widget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLES2Widget(QWidget *parent = 0);
    ~GLES2Widget();
signals:

public slots:

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    GLES2::ShaderProgram* m_program;
    GLES2Rectangle* m_rect;

    GLES2::Matrix4x4* m_projMatrix;
};

#endif // GLES2WIDGET_H
