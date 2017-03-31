#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T16:23:01
#
#-------------------------------------------------

QT       += core gui opengl widgets

TARGET = hello_opengles2
TEMPLATE = app
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++14


INCLUDEPATH += ./ \
   ../

SOURCES += main.cpp\
    mainwindow.cpp \
    gles2widget.cpp \
    gles2rectangle.cpp \
    ../RenderEngine/matrix4x4.cpp \
    ../RenderEngine/entity.cpp \
    ../RenderEngine/material.cpp \
    ../RenderEngine/mesh.cpp \
    ../RenderEngine/shaderprogram.cpp \
    ../RenderEngine/texture.cpp \
    ../RenderEngine/vertex.cpp

HEADERS  += mainwindow.h \
    gles2widget.h \
    shadersource.h \
    gles2rectangle.h \
    ../RenderEngine/matrix4x4.h \
    ../RenderEngine/entity.h \
    ../RenderEngine/material.h \
    ../RenderEngine/mesh.h \
    ../RenderEngine/shaderprogram.h \
    ../RenderEngine/texture.h \
    ../RenderEngine/vec.h \
    ../RenderEngine/vertex.h
