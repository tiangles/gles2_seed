#include "mainwindow.h"
#include "gles2widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_glWidget = new GLES2Widget(this);
    setCentralWidget(m_glWidget);
}

MainWindow::~MainWindow()
{

}
