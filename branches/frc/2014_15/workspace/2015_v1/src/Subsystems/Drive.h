#ifndef Drive_H
#define Drive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drive: public Subsystem
{
private:
	Talon drive1, drive2;
	DoubleSolenoid shifter;

	float deadband;
	float maxout;
public:
	Encoder encoder;
	Drive (uint32_t channeld1, uint32_t channeld2,
			uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel,
			uint32_t encoderAChannel, uint32_t encoderBChannel);
	~Drive();
	void test_motors();
	void Move(float LeftSpeed, float RightSpeed);
	void stopdrive();
	void TeleDrive(float Xbox_x, float Xbox_y);
	void InitDefaultCommand();

	void shift();
	void highGear();
	void lowGear();
};

#endif
