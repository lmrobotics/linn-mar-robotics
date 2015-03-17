#include <Subsystems/Elevator.h>
#include "../RobotMap.h"

Elevator::Elevator(uint32_t winchChannel, uint32_t armLChannel, uint32_t armRChannel,
		uint8_t pneumaticsModuleNumber, uint32_t winchShiftForwardChannel, uint32_t winchShiftReverseChannel,
		uint32_t armShiftForwardChannel, uint32_t armShiftReverseChannel,
		uint32_t winchBrakeChannel,
		uint32_t magShiftForwardChannel, uint32_t magShiftReverseChannel) :
		Subsystem("elevator"), winchMotor(winchChannel), armMotorR(armRChannel), armMotorL(armLChannel),
				winchShifter(pneumaticsModuleNumber, winchShiftForwardChannel,winchShiftReverseChannel),
				armShifter(pneumaticsModuleNumber,armShiftForwardChannel, armShiftReverseChannel),
				winchBrake(winchBrakeChannel),
				magShifter(pneumaticsModuleNumber, magShiftForwardChannel, magShiftReverseChannel){

}

Elevator::~Elevator() {

}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::setElevator(double power) {
	winchMotor.Set(power);
	if (power == 0) {
		brakeElevator();
	} else {
		unbrakeElevator();
	}
}
void Elevator::highGearElevator() {
	winchShifter.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::lowGearElevator() {
	winchShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::shiftElevatorGear() {
	if (winchShifter.Get() == DoubleSolenoid::Value::kForward) {
		winchShifter.Set(DoubleSolenoid::Value::kReverse);
	} else {
		winchShifter.Set(DoubleSolenoid::Value::kForward);
	}
}
bool Elevator::isElevatorHighGear() {
	if (winchShifter.Get() == DoubleSolenoid::Value::kForward) {
		return true;
	} else {
		return false;
	}
}
void Elevator::brakeElevator() {
	winchBrake.Set(Relay::Value::kForward);
}
void Elevator::unbrakeElevator() {
	winchBrake.Set(Relay::Value::kReverse);
}
void Elevator::openArms() {
	armShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::closeArms() {
	armShifter.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::shiftArms() {	//
	if (armShifter.Get() == DoubleSolenoid::Value::kForward) {
		armShifter.Set(DoubleSolenoid::Value::kReverse);
	} else {
		armShifter.Set(DoubleSolenoid::Value::kForward);
	}
}
bool Elevator::isArmsOpen() {
	if (armShifter.Get() == DoubleSolenoid::Value::kForward) {
		return true;
	} else {
		return false;
	}
}
void Elevator::openMag() {
	magShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::closeMag() {
	magShifter.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::shiftMag() {	//
	if (magShifter.Get() == DoubleSolenoid::Value::kForward) {
		magShifter.Set(DoubleSolenoid::Value::kReverse);
	} else {
		magShifter.Set(DoubleSolenoid::Value::kForward);
	}
}
bool Elevator::isMagOpen() {
	if (magShifter.Get() == DoubleSolenoid::Value::kForward) {
		return true;
	} else {
		return false;
	}
}
void Elevator::setRollers(double power) {	//
	armMotorL.Set(-power);
	armMotorR.Set(power);
}
void Elevator::setLRollers(double power) {
	armMotorL.Set(-power);
}
void Elevator::setRRollers(double power) {
	armMotorR.Set(power);
}
