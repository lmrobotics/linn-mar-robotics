#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T15:52:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dimamicMessages
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Message.cpp \
    MessageInterface.cpp \
    MessageInterfaceServer.cpp \
    MessageLoader.cpp

HEADERS += \
    Message.h \
    MessageInterface.h \
    MessageInterfaceServer.h \
    MessageLoader.h
