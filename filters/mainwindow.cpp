#include "mainwindow.h"
#include "gles2widget.h"
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_resourceFolder("/home/btian/workspace/opengles2/")
{
    setupMenu();

    m_glWidget = new GLES2Widget(m_resourceFolder, this);
    setCentralWidget(m_glWidget);
    this->setGeometry(0, 0, 638, 960);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMenu()
{

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuShaders = new QMenu(menuBar);

    QDir dir(m_resourceFolder + "shaders/fliters/");
    QFileInfoList list = dir.entryInfoList();
    foreach (QFileInfo info, list) {
        if(info.isFile() && info.fileName()!="Fliters.vert"){
            QAction *action = new QAction(this);
            action->setObjectName(info.fileName());
            action->setText(info.fileName());
            menuShaders->addAction(action);
        }
    }
    menuShaders->setObjectName(QStringLiteral("menuFile"));
    menuShaders->setTitle(QStringLiteral("Shaders"));

    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->addAction(menuShaders->menuAction());
    connect(menuShaders, &QMenu::triggered, this, &MainWindow::changeFliter);

    setMenuBar(menuBar);
    setWindowTitle(QStringLiteral("MainWindow"));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    m_glWidget->keyReleaseEvent(event);
}

void MainWindow::changeFliter(QAction *action)
{
    m_glWidget->setShader(action->text());
}
