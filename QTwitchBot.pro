#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T15:17:23
#
#-------------------------------------------------

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTwitchBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monitor.cpp \
    twitchmanager.cpp \
    twitchcommandlist.cpp \
    musicplayer.cpp \
    notewindow.cpp

HEADERS  += mainwindow.h \
    monitor.h \
    twitchmanager.h \
    twitchcommandlist.h \
    musicplayer.h \
    notewindow.h

FORMS    += mainwindow.ui \
    monitor.ui

RESOURCES += \
    localRes.qrc
