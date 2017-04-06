#ifndef GLES2WIDGET_H
#define GLES2WIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions.h>
#include <memory>

namespace GLES2 {
class Matrix4x4;
}

class Fragment;
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
    std::shared_ptr<Fragment> m_fragment;
};

#endif // GLES2WIDGET_H
