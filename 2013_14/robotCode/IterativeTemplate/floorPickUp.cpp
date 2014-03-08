#include "floorPickUp.h"

FloorPickUp::FloorPickUp (uint8_t moduleNumber1, uint32_t channel1, uint8_t moduleNumber2, uint32_t channel2, 
		uint8_t moduleNumber3, uint32_t channel3):
	armLeft(moduleNumber1,channel1),
	armRight(moduleNumber2,channel2),
	armWheel(moduleNumber3,channel3)
{	
}

FloorPickUp::~FloorPickUp() {
	armLeft.Set(0);
	armRight.Set(0);
	armWheel.Set(0);
}

void FloorPickUp::holdPos(float pos, float currentPos) {
	if ((abs((int)(currentPos-pos)) < 15) || (currentPos < 1)) {
		armRight.Set(0);
		armLeft.Set(0);		
	}
	else if (currentPos < pos) {
		//Move Down
		armRight.Set(-.35);
		armLeft.Set(.35);
	}
	else if (currentPos > pos) {
		armRight.Set(.35);
		armLeft.Set(-.35);
	}
	else {
		armRight.Set(0);
		armLeft.Set(0);	
	}
}

void FloorPickUp::goToPos(float pos, float currentPos) {
	if ((abs((int)(currentPos-pos)) < 30) || (currentPos < 1)) {
		holdPos(pos, currentPos);
	}
	else if (currentPos < pos) {
		//Move Down
		armRight.Set(-.6);
		armLeft.Set(.6);
	}
	else if (currentPos > pos) {
		armRight.Set(.6);
		armLeft.Set(-.6);
	}
}

void FloorPickUp::stop() {
	armRight.Set(0);
	armLeft.Set(0);
}

void FloorPickUp::moveAngle(float power, int direction) {
	if (direction == 1) { // MOVE UP
		armRight.Set(power);
		armLeft.Set(-power);
	}
	else if (direction == 0) { // MOVE DOWN
		armRight.Set(-power);
		armLeft.Set(power);
	}
	else {
		armRight.Set(0);
		armLeft.Set(0);
	}
}

void FloorPickUp::moveWheels(float power) {
	armWheel.Set(power);
}
