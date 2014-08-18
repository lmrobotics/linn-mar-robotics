#include "BaseMessageClass.h"
#include "messageTransport.h"
#include <string.h>

namespace Messages
{


   BaseMessageClass::BaseMessageClass(MessageTypesClass::messageId msgId_, int size)
   {
       msgId = msgId_;
       message = new unsigned char[size];
       message[0] = (unsigned char)msgId;
       message[1] = (unsigned char)size;
   }
   
   BaseMessageClass::BaseMessageClass(unsigned char rawMsg[])
   {
      msgSize = rawMsg[1];
      message = new unsigned char[msgSize];
      memcpy(message, rawMsg, msgSize);
      msgId = (MessageTypesClass::messageId)message[0];
   }
   
   BaseMessageClass::~BaseMessageClass()
   {
      delete message;
   }
   
   void BaseMessageClass::sendData()
   {
	   messageTransport::send(message, message[1]);
   }
   
   MessageTypesClass::messageId BaseMessageClass::messageType()
   {
       return msgId;
   }

   int BaseMessageClass::messageSize()
   {
       return msgSize;
   }

} // namespace Messages
