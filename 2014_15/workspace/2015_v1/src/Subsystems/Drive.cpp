#include "Drive.h"
#include "../RobotMap.h"

Drive::Drive (uint32_t channeld1, uint32_t channeld2,
		uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel):
	Subsystem("Drive"),
	drive1(channeld1),
	drive2(channeld2),
	shifter(shiftModuleNumber, shiftForwardChannel, shiftReverseChannel)
{
	targetSpeedL = 0;
	targetSpeedR = 0;
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
	drive1.Set(.3);
	Wait(3);
	drive1.Set(0);
	Wait(3);
	drive2.Set(.3);
	Wait(3);
	drive2.Set(0);
	Wait(3);
}

void Drive::Move(float LeftSpeed, float RightSpeed){

	targetSpeedR = RightSpeed;
	targetSpeedL = LeftSpeed;

	if(drive1.Get()<(targetSpeedL-accel)){
		drive1.Set(drive1.Get() + accel);
	}
	else if (drive1.Get()>(targetSpeedL+accel)){
		drive1.Set(drive1.Get() - accel);
	}
	else {
		drive1.Set(targetSpeedL);
	}

	if(drive2.Get()<(targetSpeedR-accel)){
		drive2.Set(drive2.Get() + accel);
	}
	else if (drive2.Get()>(targetSpeedR+accel)){
		drive2.Set(drive2.Get() - accel);
	}
	else {
		drive2.Set(targetSpeedR);
	}

	drive1.Set(LeftSpeed);
	drive2.Set(-RightSpeed);
}

void Drive::stopdrive(){
	drive1.Set(0);
	drive2.Set(0);
}

void Drive::TeleDrive(float Xbox_y, float Xbox_x){
//Ben and Ryley's mess********************************************************



	/*
	enum DRIVE_STATES{
		DRIVE_STOPPED,
		DRIVE_MOVE,
		//DRIVE_SLOW = 2
	};
	//int startSpeed =.1;
	float targetSpeed = Xbox_y;
	float speed = 0;
	//float targetSpeed = y;

	if(Xbox_y > deadband || Xbox_y < -deadband){
		driveState = DRIVE_MOVE;
	}
	else{
		driveState = DRIVE_STOPPED;
	}

	if(driveState == DRIVE_STOPPED){
		drive1.Set(0);
		drive2.Set(0);
	}

	if(driveState == DRIVE_MOVE && speed > targetSpeed){
		speed = speed - .001;
	}
	else if(driveState == DRIVE_MOVE && speed < targetSpeed){
		speed = speed + .001;
	}
	else if(driveState == DRIVE_MOVE && speed == targetSpeed){
		drive1.Set(targetSpeed);
		drive2.Set(targetSpeed);
	}
	else{
		drive1.Set(0);
		drive2.Set(0);
	}

	if(driveState == DRIVE_MOVE){
		drive1.Set(speed);
		drive2.Set(speed);
	}
	*/

//Ben and Ryley's mess********************************************************


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

	LeftSpeed=x+y;
	RightSpeed=-x+y;

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

