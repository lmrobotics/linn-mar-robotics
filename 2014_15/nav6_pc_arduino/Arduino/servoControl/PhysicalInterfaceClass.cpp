#include "PhysicalInterfaceClass.h"
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

using namespace Utility;

/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::connect()
{
   Serial.begin(9600);
}
   
/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::disconnect()
{
    Serial.end();
}
   
/** ***************************************************************************
* \brief 
*/
void PhysicalInterfaceClass::send(unsigned char byteArray[], int length)
{
   Serial.write(byteArray, length);
}
   
int PhysicalInterfaceClass::receive(unsigned char* buffer, int length) 
{
   if (Serial.available() > 0) 
   {
      buffer[0] = Serial.read();
      return 1;
   }
   else
   {
      return 0;
   }
}
