#-------------------------------------------------
#
# Project created by QtCreator 2014-08-16T16:38:07
#
#-------------------------------------------------

QT       += serialport
QT       += core gui
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nav6ArduinoServoCtrl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nav6/IMU.cpp \
    nav6/IMUAdvanced.cpp \
    arduino/BaseMessageClass.cpp \
    arduino/messageQueueClass.cpp \
    arduino/serialMessageTransport.cpp \
    arduino/messageTransport.cpp

HEADERS  += mainwindow.h \
    nav6/IMU.h \
    nav6/IMUAdvanced.h \
    nav6/IMUProtocol.h \
    arduino/BaseMessageClass.h \
    arduino/messageQueueClass.h \
    arduino/MessageTypesClass.h \
    arduino/msgSetServoPosition.h \
    arduino/msgSetServoPositionResp.h \
    arduino/serialMessageTransport.h \
    arduino/serialmessagetransport.h \
    arduino/messageTransport.h

FORMS    += mainwindow.ui
