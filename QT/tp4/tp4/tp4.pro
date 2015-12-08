#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T14:27:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tp4
TEMPLATE = app


SOURCES += main.cpp\
        editeurhtml.cpp \
    widgetDocument.cpp \
    widgetVue.cpp \ 
    widgetStat.cpp

HEADERS  += editeurhtml.h \
    widgetDocument.h \
    widgetVue.h \ 
    widgetStat.h

FORMS    += editeurhtml.ui

RESOURCES += \
    pictures/pictures.qrc
