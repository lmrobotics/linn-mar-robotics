#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T11:17:18
#
#-------------------------------------------------

QT       += core gui
QT		+= serialport
QT		+= core
QT		+= network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clientNav6Widget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nav6/IMU.cpp \
    nav6/IMUAdvanced.cpp \
    robotMessages/BaseMessageClass.cpp \
    robotMessages/messageQueueClass.cpp \
    robotMessages/messageTransport.cpp \
    robotMessages/serialMessageTransport.cpp \
    robotMessages/udpMessageTransport.cpp

HEADERS  += mainwindow.h \
    nav6/IMU.h \
    nav6/IMUAdvanced.h \
    nav6/IMUProtocol.h \
    robotMessages/BaseMessageClass.h \
    robotMessages/messageQueueClass.h \
    robotMessages/messageTransport.h \
    robotMessages/MessageTypesClass.h \
    robotMessages/msgSetServoPosition.h \
    robotMessages/msgSetServoPositionResp.h \
    robotMessages/nav6.h \
    robotMessages/nav6Resp.h \
    robotMessages/serialMessageTransport.h \
    robotMessages/udpMessageTransport.h

FORMS    += mainwindow.ui
