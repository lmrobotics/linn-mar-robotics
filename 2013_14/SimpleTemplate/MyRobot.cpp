#include "WPILib.h"
#include "GenericHID.h"
//#include "C:\WindRiver\vxworks-6.3\target\h\WPILib\SmartDashboard\SmartDashboard.h"
#include "dualMotor.h"
#include "dataLogger.h"

class Motors
{
	Victor drive1,drive2,drive3,drive4;
	
public:
	Motors(void):
		drive1(1,1),
		drive2(1,2),
		drive3(1,3),
		drive4(1,4)
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
};

class RobotDemo : public SimpleRobot
{
	
	Joystick xbox,xbox2;
	Motors motors;
	Encoder shooter_encoder;
	Compressor compressor;
	Solenoid shooter2, shooter1, lifter1, lifter2;
	dualMotor <Talon> shooter_motors;
	PIDController shootControl;
	dataLogger motorRecord;
	dataLogger encoderRecord;

public:
	RobotDemo(void):
		xbox(1),
		xbox2(2),
		motors(),
		shooter_encoder(1,2),
		compressor(3,1),
		shooter2(1),
		shooter1(2),
		lifter1(3),
		lifter2(4),
		shooter_motors(1,5,6),
		shootControl(0.2, 0.02, 0.0, &shooter_encoder, &shooter_motors),
		motorRecord("MotorData.txt"),
		encoderRecord("EncoderData.txt")
	{
		shooter_encoder.SetMaxPeriod(.1);
		shooter_encoder.SetDistancePerPulse(.06);
		shooter_encoder.SetPIDSourceParameter(Encoder::kRate);
		shootControl.SetOutputRange(-0.50, 0.50);
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
			//*********VARIABLE DEFINITIONS************
			//Axes**
			float y = xbox.GetY(GenericHID::kLeftHand);
			float x = xbox.GetRawAxis(4);
			//******
			
			//Buttons on controller 1
			bool a_button = xbox.GetRawButton(1);
			
			//Buttons on controller 2
			bool second_a_button = xbox2.GetRawButton(1);
			bool second_left_button = xbox2.GetRawButton(5);
			
			//Variables from sensors
			double encoder_count = shooter_encoder.GetRate();
			
			
			//Starts compressor, charges to switch value
			if(!compressor.GetPressureSwitchValue()){
				compressor.Start();
			}
			else {
				compressor.Stop();
			}
			
			//Wheel Speed
			if(second_a_button==true) {
				shootControl.SetSetpoint(20);
				shootControl.Enable();
			}
			else {
				shootControl.Disable();
			}
			
			//Lifter Cylinders
			if(second_left_button == true) {
				lifter1.Set(true);
				lifter2.Set(false);
			}
			else {
				lifter1.Set(false);
				lifter2.Set(true);
			}
			
			//Shooter Cylinder
			if(a_button==true){
				shooter1.Set(true);
				shooter2.Set(false);
			}
			else {
				shooter1.Set(false);
				shooter2.Set(true);
			}
			
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
			//make sure power is not over one
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
			
			
			//Print Statements to Console
			printf("EncoderCount %f \n",encoder_count);
			//SmartDashboard::PutNumber("battery_voltage",12.45);
			
			
			motors.drive(-LeftSpeed,RightSpeed);
			
			if (shootControl.IsEnabled()){
				motorRecord.write_(shooter_motors.Get());
				encoderRecord.write_(shooter_encoder.GetRate());
			}
			
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
