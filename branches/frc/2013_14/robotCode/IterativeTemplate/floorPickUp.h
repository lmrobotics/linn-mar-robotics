#ifndef FloorPickUp_H
#define FloorPickUp_H
#include "WPILib.h"

class FloorPickUp {
public:
	FloorPickUp (uint8_t moduleNumber1, uint32_t channel1, uint8_t moduleNumber2, uint32_t channel2,
			uint8_t moduleNumber3, uint32_t channel3, uint8_t moduleNumber4, uint32_t channel4);
	~FloorPickUp();
	void holdPos(float pos, float currentPos);
	void goToPos(float pos, float currentPos);
	void stop();
	void moveAngle(float power, int direction);
	void moveWheels(float power);
private:
	Talon armLeft, armRight;
	Victor armWheel1, armWheel2;
	AnalogChannel *Pot;
};
	
#endif
