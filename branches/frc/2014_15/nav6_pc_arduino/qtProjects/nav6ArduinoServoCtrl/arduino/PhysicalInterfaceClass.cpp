#include "PhysicalInterfaceClass.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <QDebug>
QT_USE_NAMESPACE


using namespace Utility;

bool PhysicalInterfaceClass::portConnected;
QSerialPort PhysicalInterfaceClass::serial;

/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::connect()
{
    serial.close();
    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       if(info.description().contains("Arduino"))
       {
          serial.setPort(info);
          qDebug() << "Attempting to open Arduino serial Port";
          qDebug() << "Name        : " << info.portName();
          qDebug() << "Description : " << info.description();
          qDebug() << "Manufacturer: " << info.manufacturer();

          if (!serial.setBaudRate(QSerialPort::Baud9600) ||
              !serial.setDataBits(QSerialPort::Data8) ||
              !serial.setParity(QSerialPort::NoParity) ||
              !serial.setStopBits(QSerialPort::OneStop) ||
              !serial.setFlowControl(QSerialPort::NoFlowControl))
          {
              qDebug() << "Failed to configure serial port";
          }
          else
          {
              qDebug() << "serial configure worked!";
          }
          serial.close();
          serial.open(QIODevice::ReadWrite);
       }
    }

    if (!serial.isOpen())
    {
        qDebug() << "Serial port not opened :(";
    }
    else
    {
        qDebug() << "Serial port is opened :)";
    }

   portConnected = true;
}
   
/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::disconnect()
{
    serial.close();
    portConnected = false;
}
   
/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::send(unsigned char byteArray[], int length)
{
    serial.waitForReadyRead(1);
    int stat = serial.write((char*)byteArray, length);
    //qDebug() << "sent " << stat << " chars of data";
    serial.waitForBytesWritten(-1);
}
   
int PhysicalInterfaceClass::receive(unsigned char* buffer, int length)
{
    //qDebug() << serial.bytesAvailable() << " bytes available to read";
    int chars = serial.read((char*)buffer, length);
   // qDebug() << "read " << chars << " bytes of data";
    return chars;
}
