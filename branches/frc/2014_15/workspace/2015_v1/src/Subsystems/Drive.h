#ifndef Drive_H
#define Drive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"


class Drive: public Subsystem
{
private:
	Talon drive1, drive2;
	DoubleSolenoid shifter;

	const float deadband = .1;
	const float maxout = 1;
	float accel;
	float targetSpeedL;
	float targetSpeedR;
	float currentSpeedL;
	float currentSpeedR;


public:
	Drive (uint32_t channeld1, uint32_t channeld2,
			uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel);
	~Drive();
	void test_motors();
	void Move(float LeftSpeed, float RightSpeed);
	void MoveNoAccel(float LeftSpeed, float RightSpeed);
	void stopdrive();
	void TeleDrive(float Xbox_x, float Xbox_y);
	void InitDefaultCommand();
	void setAccel(float newAccel);
	float getAccel();
	void shift();
	void highGear();
	void lowGear();
};

#endif
