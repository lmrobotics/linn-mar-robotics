#ifndef PhysicalInterfaceClass_h
#define PhysicalInterfaceClass_h
#include "MessageTypesClass.h"
#include "BaseMessageClass.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Utility
{

   class PhysicalInterfaceClass
   {
      public:
         static void connect();
         static void disconnect();
         static void send(unsigned char byteArray[], int length);
         static int receive(unsigned char* buffer, int length);
         static QSerialPort serial;

      private:
         static bool portConnected;

      }; // class PhysicalInterfaceClass

} // namespace 

#endif
