#include <Subsystems/Elevator.h>
#include "../RobotMap.h"

Elevator::Elevator(uint32_t winchChannel, uint32_t armLChannel, uint32_t armRChannel,
		uint8_t pneumaticsModuleNumber, uint32_t winchShiftForwardChannel, uint32_t winchShiftReverseChannel,
		uint32_t armShiftForwardChannel, uint32_t armShiftReverseChannel,
		uint32_t winchBrakeForwardChannel, uint32_t winchBrakeReverseChannel) :
		Subsystem("elevator"), winchMotor(winchChannel), armMotorR(armRChannel), armMotorL(armLChannel),
				winchShifter(pneumaticsModuleNumber, winchShiftForwardChannel,winchShiftReverseChannel),
				armShifter(pneumaticsModuleNumber,armShiftForwardChannel, armShiftReverseChannel),
				winchBrake(pneumaticsModuleNumber, winchBrakeForwardChannel,winchBrakeReverseChannel) {

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
	winchShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::lowGearElevator() {
	winchShifter.Set(DoubleSolenoid::Value::kReverse);
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
	winchBrake.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::unbrakeElevator() {
	winchBrake.Set(DoubleSolenoid::Value::kReverse);
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
void Elevator::setRollers(double power) {	//
	armMotorL.Set(power);
	armMotorR.Set(-power);
}
void Elevator::setLRollers(double power) {
	armMotorL.Set(power);
}
void Elevator::setRRollers(double power) {
	armMotorR.Set(-power);
}
