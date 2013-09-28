#include "WPILib.h"
#include "GenericHID.h"
#include "Dashboard.h"

class Motors
{
	Victor drive1,drive2,drive3,drive4;
	Talon shooter1, shooter2;
	
public:
	Motors(void):
		drive1(1,1),
		drive2(1,2),
		drive3(1,3),
		drive4(1,4),
		shooter1(1,5),
		shooter2(1,6)
		{
		}
	
	void drive(float LeftSpeed,float RightSpeed){
		drive1.Set(LeftSpeed);
		drive2.Set(LeftSpeed);
		drive3.Set(RightSpeed);
		drive4.Set(RightSpeed);
	}
	
	void test_motors(){
		drive1.Set(.3);
		Wait(3);
		drive1.Set(0);
		Wait(3);
		drive2.Set(.3);
		Wait(3);
		drive2.Set(0);
		Wait(3);
		drive3.Set(.3);
		Wait(3);
		drive3.Set(0);
		Wait(3);
		drive4.Set(.3);
		Wait(3);
		drive4.Set(0);
	}
	
	void stopdrive(){
		drive1.Set(0);
		drive2.Set(0);
		drive3.Set(0);
		drive4.Set(0);
	}
	
	void spinshooter(float speed){
		shooter1.Set(speed);
		shooter2.Set(speed);
	}
};


class RobotDemo : public SimpleRobot
{
	
	Joystick xbox,xbox2;
	Motors motors;
	Encoder shooter_encoder;
	Compressor compressor;
	Solenoid shooter2, shooter1;

public:
	RobotDemo(void):
		xbox(1),
		xbox2(2),
		motors(),
		shooter_encoder(1,2),
		compressor(3,1),
		shooter2(1),
		shooter1(2)
	{
		shooter_encoder.SetMaxPeriod(.1);
		shooter_encoder.SetDistancePerPulse(.06);
		shooter_encoder.Start();
	}

	void Autonomous(void)
	{
		motors.test_motors();
	}

	
	void OperatorControl(void)
	{
		float deadband = .2;
		float maxout = 1;
		float LeftSpeed,RightSpeed;
		while (IsOperatorControl())
		{
			float y = xbox.GetY(GenericHID::kLeftHand);
			float x = xbox.GetRawAxis(4);
			bool second_a_button = xbox2.GetRawButton(1);
			bool a_button = xbox.GetRawButton(1);
			double encoder_count = shooter_encoder.GetRate();
			
			if(!compressor.GetPressureSwitchValue()){
				compressor.Start();
			}
			else {
				compressor.Stop();
			}
			
			
			if(second_a_button==true) {
				motors.spinshooter(.35);
			}
			else {
				motors.spinshooter(0);
			}
			
			if(a_button==true){
				shooter1.Set(true);
				shooter2.Set(false);
			}
			else {
				shooter1.Set(false);
				shooter2.Set(true);
			}
			
			if(y >= deadband) {
				if(x > deadband) {
					LeftSpeed=max(x,y)*maxout;
					RightSpeed=(y+x)*maxout;

				}
				else if(x < -deadband){
					LeftSpeed=(-x+y)*maxout;
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
			printf("EncoderCount %f \n",encoder_count);
			
			
			motors.drive(-LeftSpeed,RightSpeed);
			
			Wait(0.005);
		}
		shooter_encoder.Stop();
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);
