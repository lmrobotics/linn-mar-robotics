#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

class Motors
{
	Talon drive1,drive2,drive3,drive4;
	
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
	Compressor compressor;
	Solenoid shifter1,shifter2;
	AnalogChannel *Pot;
	Encoder Test_Encoder;
	NetworkTable *Camtable;
	Gyro gyro;

public:
	RobotDemo():
		xbox(1),
		xbox2(2),
		motors(),
		compressor(3,1),
		shifter1(3),
		shifter2(4),
		Test_Encoder(4,5),
		gyro(2)
	{
		Pot= new AnalogChannel(1);
		Test_Encoder.SetMaxPeriod(.1);
		Test_Encoder.SetDistancePerPulse(.06);
		Test_Encoder.Start();
		Camtable = NetworkTable::GetTable("SmartDashboard");
//		Pot->SetAverageBits(4);
	}

	void Autonomous() {
		gyro.Reset();
		int LeftInt=2;
		int RightInt=2;
		int timer=0;
		int counter=0;
		const float autoMotorSpeed=0.0;
		const float gyroAngleRatio=1.0/50.0;
		const float gyroDeadband=6.5;
		float angle = 0;
		printf("Autonomous");
		while (true/*timer<800*/) {
			angle= gyro.GetAngle();
			if (angle<=-15){
				angle=-15;
			}
			if (angle>=15){
				angle=15;
			}
			if (angle>-gyroDeadband & angle < gyroDeadband){
				angle=0.0;
			}
			motors.drive(autoMotorSpeed-(angle*gyroAngleRatio),-autoMotorSpeed-(angle*gyroAngleRatio));
			/*
			if (Camtable->ContainsKey("LeftBool")){
				Camtable->GetNumber("LeftBool",LeftInt);
			}
			if (Camtable->ContainsKey("RightBool")){
				Camtable->GetNumber("RightBool",RightInt);
			}
			if (counter>=5){
				printf("LeftBool: %d   ",LeftInt);
				printf("RightBool: %d \n",RightInt);
				counter=0;
			}
			counter++;
			*/
			timer++;
			Wait(.005);
		}
		motors.drive(0,0);
	}
	
	void OperatorControl() {
		printf("Before Loop");
		gyro.Reset();
		float deadband = .2;
		float LeftSpeed,RightSpeed;
		float maxout = 1;
		int counter=0;
		float angle = 0;
		int gyroResetDelay=0;
		while (IsOperatorControl())
		{
			//*********VARIABLE DEFINITIONS************
			//Axes**
			float y = xbox.GetY(GenericHID::kLeftHand);
			float x = xbox.GetRawAxis(4);
			//******
					
			//Buttons on controller 1
			bool l1_button = xbox.GetRawButton(5);
			bool A_button = xbox.GetRawButton(1);
			
			if(!compressor.GetPressureSwitchValue()){
				compressor.Start();
			}
			else {
				compressor.Stop();
			}
			
			if(l1_button==true){
				shifter1.Set(true);
				shifter2.Set(false);
			}
			else {
				shifter1.Set(false);
				shifter2.Set(true);
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
					LeftSpeed=-max(x,-y)*maxout;
					RightSpeed=(x+y)*maxout;
				}
				else if(x < -deadband) {
					LeftSpeed=(y-x)*maxout;
					RightSpeed=-max(-x,-y)*maxout;
				}
				else {
					LeftSpeed = y*maxout;
					RightSpeed = y*maxout;
				}
			}
			else {
				if(x > deadband) {
					LeftSpeed=-x*maxout;
					RightSpeed=x*maxout;
				}
				else if(x < -deadband){
					LeftSpeed=-x*maxout;
					RightSpeed=x*maxout;
				}
				else {
					LeftSpeed = 0;
					RightSpeed = 0;
				}
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
			motors.drive(-LeftSpeed,RightSpeed);
			
			//Reset of gyro value in case of goof up
			if (A_button & gyroResetDelay>=100){
				gyro.Reset();
				gyroResetDelay=0;
			}
			
			counter++;
			gyroResetDelay++;
			if (counter>=5){
				angle = gyro.GetAngle();
				//printf("Potentiometer Count: %f   ",(float)(Pot->GetValue()));
				printf("Gyro Angle: %f \n",angle);
				//printf("Encoder Count: %f \n",(float)(Test_Encoder.Get()));
				counter=0;
			}
			Wait(.005);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);
