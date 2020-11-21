#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T21:16:16
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = ../../PacmanSingle_Player_Qt_Cplusplus/executable/Pacman
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game_map.cpp \
    game_window.cpp \
    main.cpp \
    pacman.cpp \
    foodball.cpp \
    powerball.cpp \
    ghost.cpp \
    sounds.cpp \
    score_display.cpp \
    screen_text_display.cpp \
    log_manager.cpp

HEADERS += \
    game_map.h \
    game_window.h \
    pacman.h \
    foodball.h \
    powerball.h \
    ghost.h \
    sounds.h \
    utilities.h \
    score_display.h \
    screen_text_display.h \
    log_manager.h

FORMS += \
    game_window.ui

RESOURCES += \
    images.qrc \
    sounds.qrc

DISTFILES +=
