#-------------------------------------------------
#
# Project created by QtCreator 2020-04-13T17:40:10
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    authorizationwidget.cpp \
    mainwidget.cpp \
    registrationwidget.cpp \
    applicationwidget.cpp \
    menuwidget.cpp \
    createeventwidget.cpp \
    createtemplatewidget.cpp \
    networkclient.cpp

HEADERS  += \
    mainwindow.h \
    authorizationwidget.h \
    mainwidget.h \
    registrationwidget.h \
    applicationwidget.h \
    menuwidget.h \
    createeventwidget.h \
    createtemplatewidget.h \
    networkclient.h

FORMS    +=

DISTFILES +=

RESOURCES += \
    images.qrc
