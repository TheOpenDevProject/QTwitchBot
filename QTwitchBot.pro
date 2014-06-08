#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T15:17:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTwitchBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monitor.cpp

HEADERS  += mainwindow.h \
    monitor.h

FORMS    += mainwindow.ui \
    monitor.ui
