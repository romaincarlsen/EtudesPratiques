#-------------------------------------------------
#
# Project created by QtCreator 2014-03-27T14:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkers
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    Checkerboard.cpp \
    Player.cpp \
    PlayerCP.cpp \
    tools.cpp \
    game.cpp \
    labelcase.cpp

HEADERS  += mainwindow.h \
    Checkerboard.h \
    Player.h \
    PlayerCP.h \
    Tools.h \
    struct.h \
    include.h \
    game.h \
    labelcase.h

FORMS    += mainwindow.ui
