#-------------------------------------------------
#
# Project created by QtCreator 2019-07-21T15:28:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WarthogHolidayWork
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        game.cpp \
        locations.cpp \
        main.cpp \
        mainwindow.cpp \
        obstacle.cpp \
        player.cpp \
        position.cpp \
        robot.cpp \
        team.cpp

HEADERS += \
        game.h \
        locations.h \
        mainwindow.h \
        obstacle.h \
        player.h \
        position.h \
        robot.h \
        team.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
