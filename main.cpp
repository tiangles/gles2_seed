#include "mainwindow.h"
#include <QApplication>

float z=0.5;
static const float vert[] = {
    -0.5f, -0.5f, z, 0, 0, -1.f, 0, 0,
     0.5f, -0.5f, z, 0, 0, -1.f, 0, 0,
     0.5f,  0.5f, z, 0, 0, -1.f, 0, 0,
    -0.5f,  0.5f, z, 0, 0, -1.f, 0, 0,
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
