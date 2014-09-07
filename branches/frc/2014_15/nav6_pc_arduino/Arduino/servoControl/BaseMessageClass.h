#ifndef BASE_MESSAGE_CLASS_H
#define BASE_MESSAGE_CLASS_H
#include "MessageTypesClass.h"

namespace Messages
{
   typedef char int8;
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

          float getFloat(int msgOffset);
          char getChar(int msgOffset);
          int8 getInt8(int msgOffset);
          int16 getInt16(int msgOffset);
          int32 getInt32(int msgOffset);
          uint8 getUint8(int msgOffset);
          uint16 getUint16(int msgOffset);
          uint32 getUint32(int msgOffset);

          void putFloat (float val, int msgOffset);
          void putChar(char val, int msgOffset);
          void putInt8(int8 val, int msgOffset);
          void putInt16(int16 val, int msgOffset);
          void putInt32(int32 val, int msgOffset);
          void putUint8(uint8 val, int msgOffset);
          void putUint16(uint16 val, int msgOffset);
          void putUint32(uint32 val, int msgOffset);

       private: 

    }; // class BaseMessageClass

} // namespace 

#endif
