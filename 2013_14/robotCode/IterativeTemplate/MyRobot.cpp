#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */ 

//int counter=0;			// To limit the number of messages sent to the console

class IronLions : public IterativeRobot
{
	Drive drive;
	
	DriverStation *ds;
	Joystick xbox1,xbox2;
	Compressor compressor;
	Gyro gyro;
	Solenoid shifter1,shifter2;
	Encoder driveEncoder;
	NetworkTable *Camtable;
	AnalogChannel *Pot;
	
	// Local variables to count the number of periodic loops performed
	int auto_periodic_loops;
	int disabled_periodic_loops;
	int tele_periodic_loops;
	
	int auto_time;			// autonomous mode clock (ms)
	int auto_state;			// autonomous mode state
	int auto_program_number;// autonomous mode program number
	int auto_count;
	float auto_dist;
	
	int counter;
	int RightInt;			// To record network table values
	int LeftInt;			// To record network table values
	
	//Controller definitions
	/* Controller.GetRawButton(#)
	 * #  |   xbox Button
	 * -------------------
	 * 1  |   A
	 * 2  |   B
	 * 3  |   X
	 * 4  |   Y
	 * 5  |   L1
	 * 6  |   R1
	 * 7  |   Select
	 * 8  |   Start
	 * 9  |   Left Joystick Click
	 * 10 |   Right Joystick Click
	 */
	bool l1_button;
	bool A_button;
	
public:
	IronLions(void):
		drive(1,1,1,2,1,3,1,4),
		xbox1(1),
		xbox2(2),
		compressor(3,1),
		gyro(2),
		shifter1(3),
		shifter2(4),
		driveEncoder(4,5)
	{
		ds = DriverStation::GetInstance();
		Camtable = NetworkTable::GetTable("SmartDashboard");
		Pot= new AnalogChannel(1);
		Pot->SetAverageBits(7);
		
		driveEncoder.SetMaxPeriod(.1);
		driveEncoder.SetDistancePerPulse(.0222);
		driveEncoder.Start();
		
		auto_periodic_loops = 0;
		disabled_periodic_loops = 0;
		tele_periodic_loops = 0;
		
		auto_time = 0;
		auto_state = 0;
		auto_program_number = 0;
		auto_count = 0;
		auto_dist = 0;
		
		counter = 0;
		RightInt=0;
		LeftInt=0;
	}
	
	void DriveAngle(float targetAngle, float motorSpeed) {
		const float gyroAngleRatio=1.0/50.0;
		const float gyroDeadband=0;
		float angle;
		angle = gyro.GetAngle();
		
		if (angle<=(targetAngle-15)){
			angle=targetAngle-15;
		}
		else if (angle>=(targetAngle+15)){
			angle=targetAngle+15;
		}
		else if (angle>(targetAngle-gyroDeadband) & angle < (targetAngle+gyroDeadband)){
			angle=targetAngle;
		}
		
		drive.Move(motorSpeed-((angle-targetAngle)*gyroAngleRatio),-motorSpeed-((angle-targetAngle)*gyroAngleRatio));
	}
	
	/**
	 * Robot-wide initialization code should go here.
	 * 
	 * Use this method for default Robot-wide initialization which will
	 * be called when the robot is first powered on.  It will be called exactly 1 time.
	 */
	void IronLions::RobotInit() {
		printf("Entering RobotInit");
	}
	
	/**
	 * Initialization code for disabled mode should go here.
	 * 
	 * Use this method for initialization code which will be called each time
	 * the robot enters disabled mode. 
	 */
	void IronLions::DisabledInit() {
		printf("Entering DisabledInit\n");
				
		disabled_periodic_loops = 0;	// Reset the loop counter for disabled mode
	}
	
	/**
	 * Periodic code for disabled mode should go here.
	 * 
	 * Use this method for code which will be called periodically at a regular
	 * rate while the robot is in disabled mode.
	 */
	void IronLions::DisabledPeriodic() {
		// feed the user watchdog at every period when disabled
		GetWatchdog().Feed();
		
		drive.stopdrive();
		// increment the number of disabled periodic loops completed
		disabled_periodic_loops++;
	}
	
	/**
	 * Initialization code for autonomous mode should go here.
	 * 
	 * Use this method for initialization code which will be called each time
	 * the robot enters autonomous mode.
	 */
	void IronLions::AutonomousInit() {
		printf("Entering AutonomousInit\n");
		driveEncoder.Start();
		driveEncoder.Reset();
		gyro.Reset();
		auto_dist = driveEncoder.GetDistance();
		auto_count = 0;
	}
	
	/**
	 * Periodic code for autonomous mode should go here.
	 *
	 * Use this method for code which will be called periodically at a regular
	 * rate while the robot is in autonomous mode.
	 */
	void IronLions::AutonomousPeriodic() {
		// feed the user watchdog at every period when in autonomous
		GetWatchdog().Feed();

		if((driveEncoder.GetDistance()>-36) && (auto_count==0)) {
			DriveAngle(0,-.35);
		}
		else if(auto_count==0) {
			drive.stopdrive();
			Wait(3);
			auto_dist = driveEncoder.GetDistance();
			auto_count++;
		}
		if((driveEncoder.GetDistance()<(36)) && (auto_count==1)) {
			DriveAngle(0,.35);
		}
		else if (auto_count == 1) {
			drive.stopdrive();
			auto_dist = driveEncoder.GetDistance();
			auto_count++;
		}
		
		/*
		if (Camtable->ContainsKey("LeftBool")){
			Camtable->GetNumber("LeftBool",LeftInt);
		}
		if (Camtable->ContainsKey("RightBool")){
			Camtable->GetNumber("RightBool",RightInt);
		}
		if (counter>=5){
			//printf("LeftBool: %d   ",LeftInt);
			//printf("RightBool: %d \n",RightInt);
			counter=0;
		}
		counter++;
		*/
		
		printf("driveEncoder Dist: %f\n", (driveEncoder.GetDistance()));
		auto_periodic_loops++;
	}
	
	/**
	 * Initialization code for teleop mode should go here.
	 * 
	 * Use this method for initialization code which will be called each time
	 * the robot enters teleop mode.
	 */
	void IronLions::TeleopInit() {
		printf("Entering TeleopInit\n");
		driveEncoder.Start();
		driveEncoder.Reset();
	}
	
	/**
	 * Periodic code for teleop mode should go here.
	 *
	 * Use this method for code which will be called periodically at a regular
	 * rate while the robot is in teleop mode.
	 */
	void IronLions::TeleopPeriodic() {
		//Joystick Button Definitions
		l1_button = xbox1.GetRawButton(5);
		A_button = xbox1.GetRawButton(1);
		
		
		if(A_button) {
			driveEncoder.Reset();
		}
		
		
		if(l1_button==true){
			shifter1.Set(true);
			shifter2.Set(false);
		}
		else {
			shifter1.Set(false);
			shifter2.Set(true);
		}
		
		//printf("Entering TeleopPeriodic\n");
		if(!compressor.GetPressureSwitchValue()){
			compressor.Start();
		}
		else {
			compressor.Stop();
		}
		
		
		printf("driveEncoderCount: %f \n", (float)(driveEncoder.Get()));
		//printf("Potentiometer reading: %f \n", (float)(Pot -> GetValue()));
		drive.TeleDrive(xbox1.GetRawAxis(4),xbox1.GetY(GenericHID::kLeftHand));
	}
};

START_ROBOT_CLASS(IronLions);

