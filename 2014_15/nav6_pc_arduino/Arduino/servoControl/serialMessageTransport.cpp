#include "serialMessageTransport.h"
#include <SoftwareSerial.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
unsigned char serialMessageTransport::preamble[] = { 0xAA, 0x55, 0xC3,  0x3C };

/** ***************************************************************************
* \brief Constructor
*/
serialMessageTransport::serialMessageTransport (int baudRate) :
    serialState(searching_aa),
    msgByteCount(0)
{

    connect(baudRate);
}

/** ***************************************************************************
* \brief Destructor
*/
serialMessageTransport::~serialMessageTransport()
{
    disconnect();
}

/** ***************************************************************************
* \brief Search for serial port by device name and open it.
*
* Baud rate is set to parameter passed in.  The other serial port parameters
* are hard coded to the most used values: 8 data bits; no parity; one stop bit;
* no flow control.
*/
void serialMessageTransport::connect(int baudRate)
{
   Serial.begin(baudRate);
   while (!Serial); 
}

/** ***************************************************************************
* \brief Disconnect serial port
*/
void serialMessageTransport::disconnect()
{
    Serial.end();
}

/** ***************************************************************************
* \brief Send whole message, including header
*/
void serialMessageTransport::send(BaseMessageClass& message)
{
    send(preamble, 4);
    send(message.message, message.messageSize());
}

/** ***************************************************************************
* \brief Send array of bytes
*/
void serialMessageTransport::send(unsigned char byteArray[], int length)
{
   Serial.write(byteArray, length);
}

/** ***************************************************************************
* \brief Provide an indication if whether a message is available or not.
*/
bool serialMessageTransport::messageAvailable()
{
    readSerial();
    return msgQueue.messageAvailable();
}

/** ***************************************************************************
* \brief Return a message from message queue.
*/
BaseMessageClass* serialMessageTransport::getMessage()
{
    readSerial();
    return msgQueue.getMessage();
}

/** ***************************************************************************
* \brief Read 1 byte from serial stream.
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
* \brief Read and parse serial stream data.
*
* Pramble is discarded and whole messages are placed in the message queue.
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
            case searching_aa: // first preamble byte
                if (serialData == 0xaa)
                    serialState = searching_55;
                break;

            case searching_55: // second preamble byte
                if (serialData == 0x55)
                    serialState = searching_c3;
                else
                    serialState = searching_aa;
                break;

            case searching_c3: // third preamble byte
                if (serialData == 0xC3)
                    serialState = searching_3c;
                else
                    serialState = searching_aa;
                break;

            case searching_3c: // fourth preamble byte
                if (serialData == 0x3c)
                    serialState = readingId;
                else
                    serialState = searching_aa;
                break;

            case readingId: // Getting message ID
                serialState = readingData;
                currentMsgId = (unsigned char)serialData;
                break;

           case readingData: // Getting message Data
                // first byte is the message size.
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

                // check for end of message
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

