#include "message.h"
#include "Led.h"

message* gMsg;
Led* gLed;
int gDistance;

void setup() {
  pinMode(CRIO_PORT1, INPUT);
  pinMode(CRIO_PORT2, INPUT);
  pinMode(CRIO_PORT3, INPUT);
  pinMode(LED_PORT1, OUTPUT);
  pinMode(LED_PORT2, OUTPUT);
  gMsg = new message();
  gLed = new Led();
}
void loop() {
 if(gMsg->ifAvalable()){
   gDistance = gMsg->getMessage();
   gLed->WriteDistanceToLed(gDistance);
 }
}
