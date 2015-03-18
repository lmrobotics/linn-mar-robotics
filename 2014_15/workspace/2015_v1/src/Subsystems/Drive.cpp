#include "Drive.h"
#include "../RobotMap.h"

Drive::Drive (uint32_t channeld1, uint32_t channeld2,
		uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel):
	Subsystem("Drive"),
	driveL(channeld1),
	driveR(channeld2),
	shifter(shiftModuleNumber, shiftForwardChannel, shiftReverseChannel)
{
	accel=2;
	targetSpeedL = 0;
	targetSpeedR = 0;
	currentSpeedL = 0;
	currentSpeedR = 0;
}

void Drive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

Drive::~Drive (){
	stopdrive();
}

void Drive::test_motors(){
	driveL.Set(.3);
	Wait(3);
	driveL.Set(0);
	Wait(3);
	driveR.Set(.3);
	Wait(3);
	driveR.Set(0);
	Wait(3);
}

void Drive::Move(float LeftSpeed, float RightSpeed){

	targetSpeedR = -RightSpeed;
	targetSpeedL = LeftSpeed;

	if(currentSpeedL<(targetSpeedL-accel)){
		currentSpeedL+=accel;
		driveL.Set(currentSpeedL);
	}
	else if (currentSpeedL>(targetSpeedL+accel)){
		currentSpeedL-=accel;
		driveL.Set(currentSpeedL);
	}
	else {
		currentSpeedL=targetSpeedL;
		driveL.Set(targetSpeedL);
	}

	if(currentSpeedR<(targetSpeedR-accel)){
		currentSpeedR+=accel;
		driveR.Set(currentSpeedR);
	}
	else if (currentSpeedR>(targetSpeedR+accel)){
		currentSpeedR-=accel;
		driveR.Set(currentSpeedR);
	}
	else {
		currentSpeedR=targetSpeedR;
		driveR.Set(targetSpeedR);
	}
}

void Drive::MoveNoAccel(float LeftSpeed, float RightSpeed){
		driveL.Set(LeftSpeed);
		driveR.Set(-RightSpeed);
}

void Drive::stopdrive(){
	targetSpeedL = 0;
	targetSpeedR = 0;
	currentSpeedL = 0;
	currentSpeedR = 0;
	driveL.Set(0);
	driveR.Set(0);
}

void Drive::TeleDrive(float Xbox_y, float Xbox_x){

	float x=Xbox_x;
	float y=Xbox_y;
	float RightSpeed=0;
	float LeftSpeed=0;

	//******ARCADE DRIVE CODE*****
	//square the controller inputs
	if (y<0){
		y = -(y*y);
	}
	else{
		y = y*y;
	}
	if (x<0){
		x = -(x*x);
	}
	else {
		x = x*x;
	}
	if (y<=deadband && y>=-deadband){
		y=0;
	}
	if (x<=deadband && x>=-deadband){
		x=0;
	}
	//make sure power is not* over one
	if(y>1){
		y=1;
	}
	else if(y<-1){
		y=-1;
	}
	if(x>1){
		x=1;
	}
	else if(x<-1){
		x=-1;
	}

	LeftSpeed=x-y;
	RightSpeed=-x-y;

	Move(LeftSpeed,RightSpeed);
}


void Drive::shift(){
	if(shifter.Get()==DoubleSolenoid::Value::kReverse){
		shifter.Set(DoubleSolenoid::Value::kForward);
	}
	else {
		shifter.Set(DoubleSolenoid::Value::kReverse);
	}
}

void Drive::highGear(){
	shifter.Set(DoubleSolenoid::Value::kReverse);
}

void Drive::lowGear(){
	shifter.Set(DoubleSolenoid::Value::kForward);
}
void Drive::setAccel(float newAccel){
	accel=newAccel;
}

float Drive::getAccel(){
	return accel;
}

bool Drive::isHighGear(){
	return (shifter.Get()==DoubleSolenoid::Value::kReverse);
}
