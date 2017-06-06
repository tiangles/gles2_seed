QT       += core gui opengl widgets

TARGET = filters
TEMPLATE = app

CONFIG += c++14

include (../RenderEngine/RenderEngine.pro)

INCLUDEPATH += ./ \
   ../

SOURCES += main.cpp\
    mainwindow.cpp \
    gles2widget.cpp \
    rectangle.cpp

HEADERS  += mainwindow.h \
    gles2widget.h \
    rectangle.h

OTHER_FILES +=

DISTFILES += \
    ../shaders/fliters/Fliters.vert \
    ../shaders/fliters/Embossment.frag \
    ../shaders/fliters/GaussianBlur.frag \
    ../shaders/fliters/Brightness.frag
