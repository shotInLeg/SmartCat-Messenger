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
    vkAPI/vkapi.cpp \
    Widgets/authwidget.cpp \
    Widgets/mainwidget.cpp \
    Widgets/settingswidget.cpp \
    Widgets/uithread.cpp \
    vkAPI/class_user.cpp \
    vkAPI/class_message.cpp \
    vkAPI/class_dialog.cpp \
    boxmessage.cpp \
    vkAPI/class_attachment.cpp \
    Widgets/pollthread.cpp


HEADERS  += smartcat.h \
    smartcatbrowser.h \
    Json/json.h \
    vkAPI/vkapi.h

FORMS    += smartcat.ui \
    smartcatbrowser.ui
