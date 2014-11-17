#include "message.h"
#include "Led.h"

message* gMsg;
Led* gLed;

void setup() {
  pinMode(CRIO_PORT1, INPUT);
  pinMode(CRIO_PORT2, INPUT);
  pinMode(CRIO_PORT3, INPUT);
  gMsg = new message();
  gLed = new Led();
}
void loop() {
 
}
