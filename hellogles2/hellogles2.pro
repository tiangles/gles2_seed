QT       += core gui opengl widgets

TARGET = hello_opengles2
TEMPLATE = app
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++14

include (../RenderEngine/RenderEngine.pro)

INCLUDEPATH += ./ \
   ../

SOURCES += main.cpp\
    mainwindow.cpp \
    gles2widget.cpp \
    gles2rectangle.cpp

HEADERS  += mainwindow.h \
    gles2widget.h \
    shadersource.h \
    gles2rectangle.h
