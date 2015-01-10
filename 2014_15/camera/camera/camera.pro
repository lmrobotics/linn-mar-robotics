#-------------------------------------------------
#
# Project created by QtCreator 2015-01-10T11:54:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camera
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

INCLUDEPATH += "C:\OpenCV2.1\include\opencv"

LIBS += C:\OpenCV2.1\lib\cv210.lib \
C:\OpenCV2.1\lib\cv210d.lib \
C:\OpenCV2.1\lib\cvaux210.lib \
C:\OpenCV2.1\lib\cvaux210d.lib \
C:\OpenCV2.1\lib\cxcore210.lib \
C:\OpenCV2.1\lib\cxcore210d.lib \
C:\OpenCV2.1\lib\cxts210.lib \
C:\OpenCV2.1\lib\highgui210.lib \
C:\OpenCV2.1\lib\highgui210d.lib \
C:\OpenCV2.1\lib\ml210.lib \
C:\OpenCV2.1\lib\ml210d.lib \
C:\OpenCV2.1\lib\opencv_ffmpeg210.lib \
C:\OpenCV2.1\lib\opencv_ffmpeg210d.lib
