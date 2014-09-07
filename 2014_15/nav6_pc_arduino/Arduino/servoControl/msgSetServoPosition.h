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
               servoPosition = getUint8(2);
         }

         msgSetServoPosition(
            uint8 servoPosition
            ) : BaseMessageClass(MessageTypesClass::msgSetServoPositionId, 3)
         {
               putUint8(servoPosition, 2);
         }
   };


}

#endif
