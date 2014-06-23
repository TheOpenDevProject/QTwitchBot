#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T15:17:23
#
#-------------------------------------------------

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTwitchBot
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
SOURCES += main.cpp\
        mainwindow.cpp \
    monitor.cpp \
    twitchmanager.cpp \
    twitchcommandlist.cpp \
    musicplayer.cpp \
    popupdisplaywindow.cpp

HEADERS  += mainwindow.h \
    monitor.h \
    twitchmanager.h \
    twitchcommandlist.h \
    musicplayer.h \
    popupdisplaywindow.h

FORMS    += mainwindow.ui \
    monitor.ui \
    popupdisplaywindow.ui

RESOURCES += \
    localRes.qrc
