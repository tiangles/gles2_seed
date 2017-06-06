#include "mainwindow.h"
#include "gles2widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_glWidget = new GLES2Widget(this);
    setCentralWidget(m_glWidget);
    this->setGeometry(0, 0, 638, 960);
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    m_glWidget->keyReleaseEvent(event);
}
