#ifndef NAV6_H
#define NAV6_H
#include "MessageTypesClass.h"

namespace Messages
{

   class nav6 : public BaseMessageClass
   {
      public:
         float nav6Yaw;
         float nav6Roll;
         float nav6Pich;

         nav6(unsigned char rawMessage[])
            : BaseMessageClass(rawMessage)
         {
               nav6Yaw = getFloat(2);
               nav6Roll = getFloat(8);
               nav6Pich = getFloat(14);
         }

         nav6(
            float nav6Yaw,
            float nav6Roll,
            float nav6Pich
            ) : BaseMessageClass(MessageTypesClass::nav6Id, 20)
         {
               putFloat(nav6Yaw, 2);
               putFloat(nav6Roll, 8);
               putFloat(nav6Pich, 14);
         }
   };


}

#endif
