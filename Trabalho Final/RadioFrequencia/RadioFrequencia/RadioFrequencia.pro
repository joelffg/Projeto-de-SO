#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T09:31:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RadioFrequencia
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialoglogin.cpp

HEADERS  += mainwindow.h \
    dialoglogin.h

FORMS    += mainwindow.ui \
    dialoglogin.ui

QMAKE_CXXFLAGS	= -lctacs
QMAKE_CFLAGS	= -lctacs

INCLUDEPATH += usr/lib