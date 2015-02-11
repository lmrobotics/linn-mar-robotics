#include <Subsystems/Elevator.h>
#include "../RobotMap.h"

Elevator::Elevator(uint32_t winchChannel, uint32_t armLChannel, uint32_t armRChannel, uint32_t conveyorChannel,
		uint8_t pneumaticsModuleNumber, uint32_t winchShiftForwardChannel, uint32_t winchShiftReverseChannel,
		uint32_t magShiftForwardChannel, uint32_t magShiftReverseChannel,
		uint32_t armShiftForwardChannel, uint32_t armShiftReverseChannel,
		uint8_t pneumaticsModuleNumber2, uint32_t winchBrakeForwardChannel, uint32_t winchBrakeReverseChannel) :
	Subsystem("elevator"),
	winchMotor(winchChannel),
	armMotorR(armRChannel),
	armMotorL(armLChannel),
	conveyorMotor(conveyorChannel),
	winchShifter(pneumaticsModuleNumber, winchShiftForwardChannel, winchShiftReverseChannel),
	magShifter(pneumaticsModuleNumber, magShiftForwardChannel, magShiftReverseChannel),
	armShifter(pneumaticsModuleNumber, armShiftForwardChannel, armShiftReverseChannel),
	winchBrake(pneumaticsModuleNumber2, winchBrakeForwardChannel, winchBrakeReverseChannel)
{

}

Elevator::~Elevator(){

}

void Elevator::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::openMagazine(){
	magShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::closeMagazine(){
	magShifter.Set(DoubleSolenoid::Value::kReverse);
}
bool Elevator::isMagazineOpen(){
	if (magShifter.Get() == DoubleSolenoid::Value::kForward){
		return true;
	}
	else {
		return false;
	}
}
void Elevator::shiftMagazine(){
	if (magShifter.Get()==DoubleSolenoid::Value::kForward){
		magShifter.Set(DoubleSolenoid::Value::kReverse);
	}
	else{
		magShifter.Set(DoubleSolenoid::Value::kForward);
	}
}

void Elevator::setElevator(double power){
	winchMotor.Set(power);
	if(power != 0){
		brakeElevator();
	}
	else{
		unbrakeElevator();
	}
}
void Elevator::highGearElevator(){
	winchShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::lowGearElevator(){
	winchShifter.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::shiftElevatorGear(){
	if(winchShifter.Get()==DoubleSolenoid::Value::kForward){
		winchShifter.Set(DoubleSolenoid::Value::kReverse);
	}
	else{
		winchShifter.Set(DoubleSolenoid::Value::kForward);
	}
}
bool Elevator::isElevatorHighGear(){
	if (winchShifter.Get() == DoubleSolenoid::Value::kForward){
		return true;
	}
	else {
		return false;
	}
}
void Elevator::brakeElevator(){
	winchBrake.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::unbrakeElevator(){
	winchBrake.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::openArms(){
	armShifter.Set(DoubleSolenoid::Value::kForward);
}
void Elevator::closeArms(){
	armShifter.Set(DoubleSolenoid::Value::kReverse);
}
void Elevator::shiftArms(){//
	if (armShifter.Get()==DoubleSolenoid::Value::kForward){
		armShifter.Set(DoubleSolenoid::Value::kReverse);
	}
	else{
		armShifter.Set(DoubleSolenoid::Value::kForward);
	}
}
bool Elevator::isArmsOpen(){
	if (armShifter.Get() == DoubleSolenoid::Value::kForward){
		return true;
	}
	else {
		return false;
	}
}
void Elevator::setRollers(double power){//
	armMotorL.Set(power);
	armMotorR.Set(-power);
}
void Elevator::setLRollers(double power){
	armMotorL.Set(power);

}
void Elevator::setRRollers(double power){
	armMotorR.Set(-power);

}

void Elevator::setConveyor(double power){
	conveyorMotor.Set(power);
}
/*void Elevator::moveElevator(double power){
	eMotor.Set(power);
}

void Elevator::moveElevatorToHeight(float height){
	//skip for now
}

void Elevator::autoCloseMagizine(){
	//skip for now
	if (magShifter.Get() == DoubleSolenoid::Value::kReverse){
		magShifter.Set(DoubleSolenoid::Value::kForward);
	}

}
void Elevator::elevatorStop(){
	eMotor.Set(0);
}
void Elevator::resetElevatorAndMagazine(){
	//skip for now
}

bool Elevator::isMagazineOpen(){
	if (magShifter.Get() == DoubleSolenoid::Value::kForward){
		return true;
	}
	else {
		return false;
	}
}
void Elevator::shiftMag(){
	if (magShifter.Get()==DoubleSolenoid::Value::kForward){
		magShifter.Set(DoubleSolenoid::Value::kReverse);
		}
	else{
		magShifter.Set(DoubleSolenoid::Value::kForward);
		}
	}
void Elevator::shiftWinch(){
	if(winchShifter.Get()==DoubleSolenoid::Value::kForward){
		winchShifter.Set(DoubleSolenoid::Value::kReverse);
	}
	else{
		winchShifter.Set(DoubleSolenoid::Value::kForward);
	}
}*/
