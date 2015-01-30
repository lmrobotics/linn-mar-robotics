#include "Drive.h"
#include "../RobotMap.h"

Drive::Drive (uint32_t channeld1, uint32_t channeld2,
		uint8_t shiftModuleNumber, uint32_t shiftForwardChannel, uint32_t shiftReverseChannel):
	Subsystem("Drive"),
	drive1(channeld1),
	drive2(channeld2),
	shifter(shiftModuleNumber, shiftForwardChannel, shiftReverseChannel)
{
	deadband = .2;
	maxout = 1;
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
	drive1.Set(LeftSpeed);
	drive2.Set(RightSpeed);
}

void Drive::stopdrive(){
	drive1.StopMotor();
	drive2.StopMotor();
}

void Drive::TeleDrive(float Xbox_x, float Xbox_y){

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
	LeftSpeed=x+y;
	RightSpeed=-x+y;
	/*
	//calculate the power for each side of drive
	//up on y-axis is negative
	if(y >= deadband) {
		if(x > deadband) {
			LeftSpeed=max(x,y)*maxout;
			RightSpeed=(y-x)*maxout;
		}
		else if(x < -deadband){
			LeftSpeed=(y+x)*maxout;
			RightSpeed=max(-x,y)*maxout;
		}
		else {
			LeftSpeed = y*maxout;
			RightSpeed = y*maxout;
		}
	}
	else if(y <= -deadband){
		if(x > deadband) {
			LeftSpeed=(x+y)*maxout;
			RightSpeed=-max(x,-y)*maxout;
		}
		else if(x < -deadband) {
			LeftSpeed=-max(-x,-y)*maxout;
			RightSpeed=(y-x)*maxout;
		}
		else {
			LeftSpeed = y*maxout;
			RightSpeed = y*maxout;
		}
	}
	else {
		if(x > deadband) {
			LeftSpeed=x*maxout;
			RightSpeed=-x*maxout;
		}
		else if(x < -deadband){
			LeftSpeed=x*maxout;
			RightSpeed=-x*maxout;
		}
		else {
			LeftSpeed = 0;
			RightSpeed = 0;
		}
	}
	*/
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
