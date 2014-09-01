#ifndef BASE_MESSAGE_CLASS_H
#define BASE_MESSAGE_CLASS_H
#include "MessageTypesClass.h"

namespace Messages
{
   typedef signed char int8;         /* 8 bit signed */
   typedef unsigned char uint8;      /* 8 bit unsigned */
   typedef short int16;              /* 16 bit signed */
   typedef unsigned short uint16;    /* 16 bit unsigned */
   typedef int int32;                /* 32 bit signed */
   typedef unsigned int uint32;      /* 32 bit unsigned */

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
