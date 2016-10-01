#-------------------------------------------------
#
# Project created by QtCreator 2016-09-24T20:47:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorSistema
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    information.cpp \
    meminfo.cpp \
    readerthread.cpp \
    interruptsthread.cpp \
    interruptwindow.cpp \
    dispositivosthread.cpp \
    dispositivoswindow.cpp

HEADERS  += mainwindow.h \
    information.h \
    meminfo.h \
    readerthread.h \
    interruptsthread.h \
    interruptwindow.h \
    dispositivosthread.h \
    dispositivoswindow.h

FORMS    += mainwindow.ui \
    information.ui \
    meminfo.ui \
    interruptwindow.ui \
    dispositivoswindow.ui

RESOURCES += \
    iconos.qrc
