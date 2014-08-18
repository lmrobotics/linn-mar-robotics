#ifndef MSG_SET_SERVO_POSITION_H
#define MSG_SET_SERVO_POSITION_H
#include "MessageTypesClass.h"

namespace Messages
{

   class msgSetServoPosition : public BaseMessageClass
   {
      public:
         uint8 servoPosition;

         msgSetServoPosition(unsigned char rawMessage[])
            : BaseMessageClass(rawMessage)
         {
               memcpy((char*)&servoPosition, &message[2], 1);
         }

         msgSetServoPosition(
            uint8 servoPosition
            ) : BaseMessageClass(MessageTypesClass::msgSetServoPositionId, 3)
         {
               memcpy(&message[2], (char*)&servoPosition, 1);
         }
   };


}

#endif
