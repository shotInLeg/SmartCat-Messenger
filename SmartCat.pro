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
    smartcatbrowser.cpp \
    Json/json.cpp \
    vkAPI/vkapi.cpp


HEADERS  += smartcat.h \
    smartcatbrowser.h \
    Json/json.h \
    vkAPI/vkapi.h

FORMS    += smartcat.ui \
    smartcatbrowser.ui
