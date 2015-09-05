#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T20:46:39
#
#-------------------------------------------------

QT       += webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCat
TEMPLATE = app


SOURCES += main.cpp\
        smartcat.cpp \
    Browser/smartcatbrowser.cpp

HEADERS  += smartcat.h \
    Browser/smartcatbrowser.h

FORMS    += smartcat.ui \
    Browser/smartcatbrowser.ui
