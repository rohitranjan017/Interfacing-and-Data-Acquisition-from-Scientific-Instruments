#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T02:28:20
#
#-------------------------------------------------

QT       += core gui sql
QT      +=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTC100
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    measureset.cpp \
    traceset.cpp

HEADERS  += mainwindow.h \
    measureset.h \
    traceset.h \
    allfun.h \
    allfun3.h \
    allfun6.h

FORMS    += mainwindow.ui \
    measureset.ui \
    traceset.ui

DISTFILES += \
    button_ctc100.png

RESOURCES += \
    resource.qrc
