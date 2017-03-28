#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T16:23:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gles2seed
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    gles2widget.cpp \
    gles2rectangle.cpp \
    matrix4x4.cpp \
    entity.cpp \
    material.cpp \
    mesh.cpp \
    shaderprogram.cpp \
    texture.cpp

HEADERS  += mainwindow.h \
    gles2widget.h \
    shadersource.h \
    gles2rectangle.h \
    matrix4x4.h \
    entity.h \
    material.h \
    mesh.h \
    shaderprogram.h \
    texture.h \
    vec.h \
    vertex.h
