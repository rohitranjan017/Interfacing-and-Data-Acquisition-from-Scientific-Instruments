#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T02:28:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTC100
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wk.cpp \
    measureset.cpp \
    traceset.cpp \
    wkmeter.cpp

HEADERS  += mainwindow.h \
    wk.h \
    measureset.h \
    traceset.h \
    wkmeter.h \
    allfun.h \
    allfun3.h

FORMS    += mainwindow.ui \
    wk.ui \
    measureset.ui \
    traceset.ui \
    wkmeter.ui

DISTFILES += \
    button_ctc100.png

RESOURCES += \
    resource.qrc
