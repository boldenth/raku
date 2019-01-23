#-------------------------------------------------
#
# Project created by QtCreator 2019-01-17T10:13:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raku
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -std=c++11



SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/editor.cpp \
        src/image.cpp \
        src/colorbox.cpp \
        src/imageview.cpp

HEADERS += \
        include/mainwindow.h \
        include/image.h \
        include/editor.h \
        include/colorbox.h \
        include/imageview.h

FORMS += \
        forms/mainwindow.ui \
        forms/imageview.ui

INCLUDEPATH += \
        include
