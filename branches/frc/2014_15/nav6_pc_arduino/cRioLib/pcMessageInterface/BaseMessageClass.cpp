#include "BaseMessageClass.h"
#include "messageTransport.h"
#include <string.h>
#include <math.h>

namespace Messages
{

/** ***************************************************************************
* \brief Constructor
*/
BaseMessageClass::BaseMessageClass(MessageTypesClass::messageId msgId_, int size)
{
    msgId = msgId_;
    message = new unsigned char[size];
    msgSize = size;
    message[0] = (unsigned char)msgId;
    message[1] = (unsigned char)size;
}
   
/** ***************************************************************************
* \brief Constructor
*/
BaseMessageClass::BaseMessageClass(unsigned char rawMsg[])
{
   msgSize = rawMsg[1];
   message = new unsigned char[msgSize];
   memcpy(message, rawMsg, msgSize);
   msgId = (MessageTypesClass::messageId)message[0];
}
   
/** ***************************************************************************
* \brief Destructor
*/
BaseMessageClass::~BaseMessageClass()
{
   delete message;
}
      
/** ***************************************************************************
* \brief return message ID
*/
MessageTypesClass::messageId BaseMessageClass::messageType()
{
   return msgId;
}

/** ***************************************************************************
* \brief return message Size
*/
int BaseMessageClass::messageSize()
{
   return msgSize;
}

} // namespace Messages

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
float BaseMessageClass::getFloat(int msgOffset)
{
   int16 exp = getInt16(msgOffset);
   int32 mantissa = getInt32(msgOffset+2);
   return ldexp(((float)mantissa)/(float)2147483647.0, exp);
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putFloat (float val, int msgOffset)
{
   int exp;
   float mantissa = frexp(val, &exp);
   putInt16(exp, msgOffset);
   putInt32((int32)(mantissa*2147483647.0), msgOffset+2);
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
char BaseMessageClass::getChar(int msgOffset)
{
   return message[msgOffset];
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
int8 BaseMessageClass::getInt8(int msgOffset)
{
   return message[msgOffset];
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
int16 BaseMessageClass::getInt16(int msgOffset)
{
   return (message[msgOffset+1]<<8) + message[msgOffset];
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
int32 BaseMessageClass::getInt32(int msgOffset)
{
   return  ((int32)message[msgOffset+3]<<24) +
           ((int32)message[msgOffset+2]<<16) +
           ((int32)message[msgOffset+1]<<8) +
            (int32)message[msgOffset];
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
uint8 BaseMessageClass::getUint8(int msgOffset)
{
   return message[msgOffset];
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
uint16 BaseMessageClass::getUint16(int msgOffset)
{
   return  (((uint16)message[msgOffset+1]<<8)&0xFF00) +
           (((uint16)message[msgOffset])     &0x00FF);
}

/** ***************************************************************************
* \brief Get value from message from indicated offset
*/
uint32 BaseMessageClass::getUint32(int msgOffset)
{
   return  (((uint32)message[msgOffset+3]<<24)&0xFF000000) +
           (((uint32)message[msgOffset+2]<<16)&0x00FF0000) +
           (((uint32)message[msgOffset+1]<<8)&0x0000FF00) +
           (((uint32)message[msgOffset])     &0x000000FF);
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putChar(char val, int msgOffset)
{
   message[msgOffset] = val & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putInt8(int8 val, int msgOffset)
{
   message[msgOffset] = val & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putInt16(int16 val, int msgOffset)
{
   message[msgOffset] = val & 0xFF;
   message[msgOffset+1] = (val>>8) & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putInt32(int32 val, int msgOffset)
{
   message[msgOffset]   = val & 0xFF;
   message[msgOffset+1] = (val>>8) & 0xFF;
   message[msgOffset+2] = (val>>16) & 0xFF;
   message[msgOffset+3] = (val>>24) & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putUint8(uint8 val, int msgOffset)
{
   message[msgOffset] = val & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putUint16(uint16 val, int msgOffset)
{
   message[msgOffset] = val & 0xFF;
   message[msgOffset+1] = (val>>8) & 0xFF;
}

/** ***************************************************************************
* \brief Write value in message at indicated offset
*/
void BaseMessageClass::putUint32(uint32 val, int msgOffset)
{
   message[msgOffset]   = val & 0xFF;
   message[msgOffset+1] = (val>>8) & 0xFF;
   message[msgOffset+2] = (val>>16) & 0xFF;
   message[msgOffset+3] = (val>>24) & 0xFF;
}
