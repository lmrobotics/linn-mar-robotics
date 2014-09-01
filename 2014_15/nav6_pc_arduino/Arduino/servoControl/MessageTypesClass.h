#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

namespace Messages
{

   class MessageTypesClass
   {
      public:

         enum messageId {
            msgSetServoPositionId = 0x01,
            msgSetServoPositionRespId = 0x81,
         };

   };

}

#endif
