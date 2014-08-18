#ifndef MSG_SET_SERVO_POSITION_RESP_H
#define MSG_SET_SERVO_POSITION_RESP_H
#include "MessageTypesClass.h"

namespace Messages
{

   class msgSetServoPositionResp : public BaseMessageClass
   {
      public:

         msgSetServoPositionResp(unsigned char rawMessage[])
            : BaseMessageClass(rawMessage)
         {
         }

         msgSetServoPositionResp(

            ) : BaseMessageClass(MessageTypesClass::msgSetServoPositionRespId, 2)
         {
         }
   };


}

#endif
