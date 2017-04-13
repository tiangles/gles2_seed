#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLES2Widget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GLES2Widget* m_glWidget;

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
