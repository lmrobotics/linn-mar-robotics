#ifndef NAV6_RESP_H
#define NAV6_RESP_H
#include "MessageTypesClass.h"

namespace Messages
{

   class nav6Resp : public BaseMessageClass
   {
      public:

         nav6Resp(unsigned char rawMessage[])
            : BaseMessageClass(rawMessage)
         {
         }

         nav6Resp(

            ) : BaseMessageClass(MessageTypesClass::nav6RespId, 2)
         {
         }
   };


}

#endif
