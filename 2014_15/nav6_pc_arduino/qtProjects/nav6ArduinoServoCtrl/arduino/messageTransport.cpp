#include "messageTransport.h"
#include "physicalInterfaceClass.h"
#include "messageQueueClass.h"

unsigned char messageTransport::currentMsgId;
int messageTransport::msgByteCount;
unsigned char messageTransport::currentMsg[256];

messageTransport::serialReadStateE messageTransport::serialState;
unsigned char messageTransport::currentByte;
unsigned char messageTransport::preamble[] = { 0xAA, 0x55, 0xC3,  0x3C };

messageTransport::messageTransport(){
	serialState = searching_aa;
	Utility::PhysicalInterfaceClass::connect();
}

messageTransport::~messageTransport()
{
	Utility::PhysicalInterfaceClass::disconnect();
}

void messageTransport::send(unsigned char* message, int length)
{
    Utility::PhysicalInterfaceClass::send(preamble, 4);
    Utility::PhysicalInterfaceClass::send(message, length);
}

bool messageTransport::messageAvailable(){
	readSerial();
	return messageQueueClass::messageAvailable();
}

BaseMessageClass* messageTransport::getMessage()
{
	readSerial();
 	return messageQueueClass::getMessage();
}


/** ***************************************************************************
* \brief
*/
void messageTransport::readSerial()
{
	unsigned char serialData;
	int size = Utility::PhysicalInterfaceClass::receive(&serialData, 1);
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
                    //BaseMessageClass tmp(currentMsg);  // = new BaseMessageClass(currentMsg);
                    BaseMessageClass *tmp = new BaseMessageClass(currentMsg);
                    messageQueueClass::putMessage(tmp);

                }
                break;

        } // switch read state
    	size = Utility::PhysicalInterfaceClass::receive(&serialData, 1);
        dataAvailable = size != 0;
    } // while serial data available
} // readSerial

