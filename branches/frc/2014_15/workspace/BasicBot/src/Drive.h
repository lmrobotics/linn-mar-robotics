#ifndef DRIVE_H
#define DRIVE_H
#include "WPILib.h"

class Drive {
public:
	Drive (uint32_t channel1, uint32_t channel2);
	~Drive();
	void test_motors();
	void Move(float LeftSpeed, float RightSpeed);
	void stopdrive();
	void TeleDrive(float Xbox_x, float Xbox_y);
private:
	Talon drive1,drive2;
	float deadband;
	float maxout;
};

#endif
