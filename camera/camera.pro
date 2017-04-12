QT       += core gui opengl widgets

TARGET = camera
TEMPLATE = app
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++14

include (../RenderEngine/RenderEngine.pro)

INCLUDEPATH += ./ \
   ../

SOURCES += main.cpp\
    mainwindow.cpp \
    gles2widget.cpp \
    cube.cpp

HEADERS  += mainwindow.h \
    gles2widget.h \
    cube.h

OTHER_FILES +=

DISTFILES += \
    ../shaders/cube.frag \
    ../shaders/cube.vert
