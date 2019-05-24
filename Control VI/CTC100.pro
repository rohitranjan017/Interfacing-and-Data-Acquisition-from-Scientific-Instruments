#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T02:28:20
#
#-------------------------------------------------

QT       += core gui sql
QT      += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTC100
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ke6221.cpp \
    ke2182a.cpp \
    power.cpp \
    controlpid.cpp

HEADERS  += mainwindow.h \
    ke6221.h \
    ke2182a.h \
    Scriptwrite.h \
    scriptwrite2.h \
    power.h \
    controlpid.h

FORMS    += mainwindow.ui \
    ke6221.ui \
    ke2182a.ui \
    power.ui \
    controlpid.ui

DISTFILES += \
    button_ctc100.png

RESOURCES += \
    resource.qrc
