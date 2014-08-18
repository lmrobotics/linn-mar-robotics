#include <Servo.h> 
#include <string.h>
#include "MessageTypesClass.h"
#include "BaseMessageClass.h"
#include "PhysicalInterfaceClass.h"
#include "msgSetServoPosition.h"
#include "msgSetServoPositionResp.h"
#include "MessageTypesClass.h"
#include "messageTransport.h"

using namespace Utility;

/** ***************************************************************************
 * \brief Perform initialization.  
 *
 */

const int servoPin = 9;          
Servo myServo;

void setup()
{
  Utility::PhysicalInterfaceClass::connect();
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

   while (messageTransport::messageAvailable())
   {
      //myServo.write(0); 
      BaseMessageClass *tmp = messageTransport::getMessage();
      MessageTypesClass::messageId msgType = tmp->messageType();
      switch (msgType)
      {
         case Messages::MessageTypesClass::msgSetServoPositionId:
         {
            Messages::msgSetServoPosition msgServoCtrl (tmp->message);
            uint8 servoCtrl = msgServoCtrl.servoPosition;
            
            Messages::msgSetServoPositionResp *servoResponse = 
              new Messages::msgSetServoPositionResp();
            servoResponse->sendData();
            delete servoResponse;  
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

