#-------------------------------------------------
#
# Project created by QtCreator 2017-06-18T19:57:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = CubeTimer
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    timer.cpp \
    timec.cpp \
    scrambler.cpp \
    puzzle.cpp \
    db.cpp \
    resultwidget.cpp

HEADERS += \
        mainwindow.h \
    timer.h \
    timec.h \
    scrambler.h \
    puzzle.h \
    db.h \
    resultwidget.h

FORMS += \
        mainwindow.ui \
    resultwidget.ui

DISTFILES += \
    puzzles/template \
    puzzles/3x3.puz \
    puzzles/idsystem \
    puzzles/2x2.puz \
    puzzles/4x4.puz \
    puzzles/5x5.puz \
    puzzles/6x6.puz \
    puzzles/7x7.puz \
    puzzles/8x8.puz \
    puzzles/9x9.puz \
    puzzles/10x10.puz \
    puzzles/11x11.puz \
    puzzles/12x12.puz \
    puzzles/13x13.puz \
    puzzles/megaminx.puz \
    icons/replay.png \
    icons/delete.svg

RESOURCES += \
    puzzles.qrc \
    icons.qrc

