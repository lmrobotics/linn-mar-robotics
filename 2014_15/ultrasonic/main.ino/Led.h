#ifndef LED_H
#define LED_H

#define LED_PORT1 1
#define LED_PORT2 2

class Led{
public:
Led();
~Led(void);
  void WriteDistanceToLed(int Distance);
};

#endif
