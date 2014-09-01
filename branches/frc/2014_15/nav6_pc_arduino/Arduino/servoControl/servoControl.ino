#include <Servo.h> 
#include <string.h>
#include "BaseMessageClass.h"
#include "MessageTypesClass.h"
#include "msgSetServoPosition.h"
#include "msgSetServoPositionResp.h"
#include "MessageTypesClass.h"
#include "messageTransport.h"
#include "serialMessageTransport.h"

/** ***************************************************************************
 * \brief Perform initialization.  
 *
 */

const int servoPin = 9;          
Servo myServo;
serialMessageTransport *interface;

void setup()
{
  interface = new serialMessageTransport(9600);
  myServo.attach(servoPin);
  myServo.write(90); 
  delay(100);

} // setup


/** ***************************************************************************
 * \brief 
 *
 */
void rxMessageProcessing()
{

   while (interface->messageAvailable())
   {
      BaseMessageClass *tmp = interface->getMessage();
      MessageTypesClass::messageId msgType = tmp->messageType();
      switch (msgType)
      {
         case Messages::MessageTypesClass::msgSetServoPositionId:
         {
            Messages::msgSetServoPosition msgServoCtrl (tmp->message);
            uint8 servoCtrl = msgServoCtrl.servoPosition;
            
            Messages::msgSetServoPositionResp servoResponse;
            interface->send((Messages::BaseMessageClass&)servoResponse);
            myServo.write(servoCtrl); 
            
         }     
         break;

         default:
         break;
      } // switch message type
      delete tmp;

   } // while messages available

} // rxMessageProcessing

/** ***************************************************************************
 * \brief 
 *
 */
void loop()
{
   // delay is needed to make serial port work.  Not sure why. Just can't poll to fast. 
   delay(2);
   rxMessageProcessing();
} // loop

