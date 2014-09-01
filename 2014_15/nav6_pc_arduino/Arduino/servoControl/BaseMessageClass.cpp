#include "BaseMessageClass.h"
#include "messageTransport.h"
#include <string.h>

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
