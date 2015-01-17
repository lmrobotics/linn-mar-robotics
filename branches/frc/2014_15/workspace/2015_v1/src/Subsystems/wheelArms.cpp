#include "wheelArms.h"
#include "../RobotMap.h"

wheelArms::wheelArms(uint32_t channelw1, uint32_t channelw2,
		uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel) :
		Subsystem("ExampleSubsystem"),
		armSol(shiftModuleNumber, shiftForwardChannel, shiftReverseChannel),
		wheel1(channelw1),
		wheel2(channelw2)
{

}

void wheelArms::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

wheelArms::~wheelArms(){
	armSol.Set(DoubleSolenoid::Value::kOff);
	stopWheels();
}

void wheelArms::grab(){
	//NOT SURE IF THIS IS CORRECT
	armSol.Set(DoubleSolenoid::Value::kForward);
}

void wheelArms::release(){
	//NOT SURE IF THIS IS CORRECT
	armSol.Set(DoubleSolenoid::Value::kReverse);
}

void wheelArms::shift(){
	if (armSol.Get()==DoubleSolenoid::Value::kReverse){
		armSol.Set(DoubleSolenoid::Value::kForward);
	}
	else {
		armSol.Set(DoubleSolenoid::Value::kReverse);
	}
}

void wheelArms::shifterOff(){
	armSol.Set(DoubleSolenoid::Value::kOff);
}

void wheelArms::pull(){
	wheel1.Set(-1);
	wheel2.Set(1);
}

void wheelArms::push(){
	wheel1.Set(1);
	wheel2.Set(-1);
}

void wheelArms::stopWheels(){
	wheel1.Set(0);
	wheel2.Set(0);
}
