#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T12:15:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorSistema_Aplicacion
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    consultar_info.cpp \
    struct_cpuinfo.cpp \
    monitor_sistema.cpp

HEADERS  += mainwindow.h \
    consultar_info.h \
    struct_cpuinfo.h \
    monitor_sistema.h

FORMS    += mainwindow.ui

DISTFILES += \
    Imagenes/3.jpg \
    Imagenes/4.jpeg \
    Imagenes/2.png

RESOURCES += \
    imagenes.qrc
