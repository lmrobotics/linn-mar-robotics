#ifndef wheelArms_H
#define wheelArms_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class wheelArms: public Subsystem
{
private:
	DoubleSolenoid armSol;
	Talon wheel1, wheel2;
public:
	wheelArms(uint32_t channelw1, uint32_t channelw2,
			uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel);
	~wheelArms();
	void InitDefaultCommand();

	void grab();
	void release();
	void shift();
	void shifterOff();

	void pull();
	void push();
	void stopWheels();
};

#endif
