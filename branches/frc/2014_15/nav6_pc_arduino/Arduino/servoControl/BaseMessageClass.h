#ifndef BASE_MESSAGE_CLASS_H
#define BASE_MESSAGE_CLASS_H
#include "MessageTypesClass.h"

namespace Messages
{
   typedef int int16;
   typedef long int32;
   typedef unsigned char uint8;
   typedef unsigned int uint16;
   typedef unsigned long uint32;

   class BaseMessageClass
   {
      public:
         BaseMessageClass(MessageTypesClass::messageId msgId_, int size);
         BaseMessageClass(unsigned char* rawMsg);
         virtual ~BaseMessageClass();
         MessageTypesClass::messageId messageType();
         int messageSize();
         unsigned char* message;
		
       protected:
          MessageTypesClass::messageId msgId;
          int msgSize;
          
       private: 

    }; // class BaseMessageClass

} // namespace 

#endif
