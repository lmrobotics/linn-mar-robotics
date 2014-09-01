#include "serialMessageTransport.h"
#include <SoftwareSerial.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
unsigned char serialMessageTransport::preamble[] = { 0xAA, 0x55, 0xC3,  0x3C };

serialMessageTransport::serialMessageTransport (int baudRate) :
    serialState(searching_aa),
    msgByteCount(0)
{

    connect(baudRate);
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
void serialMessageTransport::connect(int baudRate)
{
   Serial.begin(baudRate);
   while (!Serial); 
}

/** ***************************************************************************
* \brief
*/
void serialMessageTransport::disconnect()
{
    Serial.end();
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
   Serial.write(byteArray, length);
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
   if (Serial.available() > 0) 
   {
      buffer[0] = Serial.read();
      return 1;
   }
   else
   {
      return 0;
   }
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

