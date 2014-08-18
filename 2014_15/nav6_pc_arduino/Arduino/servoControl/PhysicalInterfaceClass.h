#ifndef PhysicalInterfaceClass_h
#define PhysicalInterfaceClass_h
#include "MessageTypesClass.h"
#include "BaseMessageClass.h"

namespace Utility
{

   class PhysicalInterfaceClass
   {
      public:
         static void connect();
         static void disconnect();
         static void send(unsigned char byteArray[], int length);
         static int receive(unsigned char* buffer, int length);

      private:
      }; // class PhysicalInterfaceClass

} // namespace 

#endif
