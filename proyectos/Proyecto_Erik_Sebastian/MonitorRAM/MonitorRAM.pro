#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T08:11:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorRAM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    process.cpp

HEADERS  += mainwindow.h \
    process.h \
    pidlib.h \
    colib.h

FORMS    += mainwindow.ui
