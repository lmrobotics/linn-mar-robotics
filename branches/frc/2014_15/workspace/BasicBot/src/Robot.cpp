#include "WPILib.h"
#include "Drive.h"
#include "myUltrasonic.h"
#include "LIDAR.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
private:
	Joystick xbox; // only joystick
	Drive drive;
	DoubleSolenoid shifter, arm;
	Compressor compressor;
	SmartDashboard *dash;
	DriverStation *ds;
//	Encoder encoder;
	myUltrasonic ultSonic;
	Talon wheel1, wheel2;
	LIDAR lidar;
	int counter;

public:
	Robot() :
			xbox(0),		// as they are declared above.
			drive(0, 1),
			shifter(0,0,1),
			arm(0,2,3),
			compressor(0),
			ultSonic(0),
			wheel1(2),
			wheel2(3),
			lidar(),
			counter(0)
//			encoder()
	{
		ds = DriverStation::GetInstance();
		SmartDashboard::init();
		lidar.setup();
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		bool xbox4Pressed = false;
		while (IsOperatorControl() && IsEnabled())
		{
			bool r1_button = xbox.GetRawButton(6);
			bool A_button = xbox.GetRawButton(1);
			if(!compressor.GetPressureSwitchValue()){
				compressor.Start();
				dash->PutString("Compressor Status:", "Running");
			}
			else {
				compressor.Stop();
				dash->PutString("Compressor Status:", "Stopped");
			}
			if(A_button==true || r1_button==true){
				shifter.Set(DoubleSolenoid::Value::kForward);
				dash->PutString("Solenoid Status:", "Shifted");
				dash->PutNumber("Ultrasonic Readings", ultSonic.getDistance());
				dash->PutString("Example", "Example");
			}
			else {
				shifter.Set(DoubleSolenoid::Value::kReverse);
				dash->PutString("Solenoid Status:", "Not Shifted");
				dash->PutNumber("Ultrasonic Readings", ultSonic.getDistance());
				dash->PutString("Example", "Example");
			}
			if (xbox.GetRawButton(2)==true){
				wheel1.Set(1);
				wheel2.Set(-1);
			}
			else if (xbox.GetRawButton(3)==true){
				wheel1.Set(-1);
				wheel2.Set(1);
			}
			else {
				wheel1.Set(0);
				wheel2.Set(0);
			}
			if (xbox.GetRawButton(4)==true && !xbox4Pressed){
				if (arm.Get()==DoubleSolenoid::Value::kForward){
					arm.Set(DoubleSolenoid::Value::kReverse);
					xbox4Pressed=true;
				}
				else {
					arm.Set(DoubleSolenoid::Value::kForward);
					xbox4Pressed=true;
				}
			}
			else if (!xbox.GetRawButton(4)){
				xbox4Pressed=false;
			}
			dash->PutNumber("Ultrasonic Readings", ultSonic.getDistance());
			dash->PutString("Example", "Change");
			drive.TeleDrive(xbox.GetRawAxis(1),xbox.GetRawAxis(4));

			unsigned char *readTest01= new unsigned char;
			unsigned char *readTest04= new unsigned char;
			dash ->PutNumber ("LIDAR Reading (Plz Work)", lidar.read());
//			dash ->PutBoolean("LIDAR Reading 01 Failed?", lidar.Read(0x01, 1, readTest01));
//			dash ->PutNumber ("LIDAR Reading 01", (int)*readTest01);
//			dash ->PutBoolean("LIDAR Reading 04 Failed?", lidar.Read(0x04, 1, readTest04));
//			dash ->PutNumber ("LIDAR Reading 04", (int)*readTest04);
			dash ->PutNumber("LIDAR High", (double)lidar.getHigh());
			dash ->PutNumber("LIDAR Low", (double)lidar.getLow());
			counter++;
			dash ->PutNumber("Counter", counter);
			Wait(0.020);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
