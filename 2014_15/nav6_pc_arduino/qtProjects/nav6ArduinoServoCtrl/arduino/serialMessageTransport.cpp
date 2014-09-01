#include "serialMessageTransport.h"
#include "qdebug.h"
unsigned char serialMessageTransport::preamble[] = { 0xAA, 0x55, 0xC3,  0x3C };

serialMessageTransport::serialMessageTransport
                (QString portDeviceName, int baudRate) :
    serialState(searching_aa),
    msgByteCount(0)
{

    connect(portDeviceName, baudRate);
}

/** ***************************************************************************
* \brief
*/
serialMessageTransport::~serialMessageTransport()
{
    disconnect();
}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::connect(QString portDeviceName, int baudRate)
{
    serialPort.close();
    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       if(info.description().contains(portDeviceName))
       {
          serialPort.setPort(info);
          qDebug() << "Attempting to open Arduino serial Port";
          qDebug() << "Name        : " << info.portName();
          qDebug() << "Description : " << info.description();
          qDebug() << "Manufacturer: " << info.manufacturer();

          if (!serialPort.setBaudRate(baudRate) ||
              !serialPort.setDataBits(QSerialPort::Data8) ||
              !serialPort.setParity(QSerialPort::NoParity) ||
              !serialPort.setStopBits(QSerialPort::OneStop) ||
              !serialPort.setFlowControl(QSerialPort::NoFlowControl))
          {
              qDebug() << "Failed to configure serial port";
          }
          else
          {
              qDebug() << "serial configure worked!";
          }
          serialPort.close();
          serialPort.open(QIODevice::ReadWrite);
       }
    }

    if (!serialPort.isOpen())
    {
        qDebug() << "Serial port not opened :(";
    }
    else
    {
        qDebug() << "Serial port is opened :)";
    }

}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::disconnect()
{
    serialPort.close();
}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::send(BaseMessageClass& message)
{
    send(preamble, 4);
    send(message.message, message.messageSize());
}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::send(unsigned char byteArray[], int length)
{
    serialPort.waitForReadyRead(1);
    serialPort.write((char*)byteArray, length);
    serialPort.waitForBytesWritten(-1);
}

/** ***************************************************************************
* \brief
*/
bool serialMessageTransport::messageAvailable()
{
    readSerial();
    return msgQueue.messageAvailable();
}

/** ***************************************************************************
* \brief

*/
BaseMessageClass* serialMessageTransport::getMessage()
{
    readSerial();
    return msgQueue.getMessage();
}

/** ***************************************************************************
* \brief
*/
int serialMessageTransport::receive(unsigned char* buffer, int length)
{
    int chars = serialPort.read((char*)buffer, length);
    return chars;
}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::readSerial()
{
    unsigned char serialData;
    int size = receive(&serialData, 1);
    bool dataAvailable = size != -1;
    while (dataAvailable)
    {
        switch (serialState)
        {
            case searching_aa:
                if (serialData == 0xaa)
                    serialState = searching_55;
                break;

            case searching_55:
                if (serialData == 0x55)
                    serialState = searching_c3;
                else
                    serialState = searching_aa;
                break;

            case searching_c3:
                if (serialData == 0xC3)
                    serialState = searching_3c;
                else
                    serialState = searching_aa;
                break;

            case searching_3c:
                if (serialData == 0x3c)
                    serialState = readingId;
                else
                    serialState = searching_aa;
                break;

            case readingId:
                serialState = readingData;
                currentMsgId = (unsigned char)serialData;
                break;

            case readingData:
                if (msgByteCount == 0)
                {
                    msgByteCount = (unsigned char)serialData;
                    currentByte = 0;
                    currentMsg[currentByte++] = (unsigned char)currentMsgId;
                    currentMsg[currentByte++] = (unsigned char)serialData;
                }
                else if (currentByte < msgByteCount)
                {
                    currentMsg[currentByte++] = (unsigned char)serialData;
                }

                if (currentByte == msgByteCount)
                {
                    msgByteCount = 0;
                    serialState = searching_aa;
                    BaseMessageClass *tmp = new BaseMessageClass(currentMsg);
                    msgQueue.putMessage(tmp);

                }
                break;

        } // switch read state
        size = receive(&serialData, 1);
        dataAvailable = size != 0;
    } // while serial data available
} // readSerial

