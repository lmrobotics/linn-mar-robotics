#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */

//Toggleable constants
const float potTopVal1=700;		//Value of Potentiometer 1 when arm is at top
const float potTopVal2=200;		//Value of Potentiometer 2 when arm is at top
const float potBotVal1=200;		//Value of Potentiometer 1 when arm is at bot
const float potBotVal2=700;		//Value of Potentiometer 2 when arm is at bot

class IronLions : public IterativeRobot
{
	Drive drive;
	
	DriverStation *ds;
	Joystick xbox1,xbox2;
	Compressor compressor;
	Gyro gyro;
	Talon intakeAngleMotorL, intakeAngleMotorR;
	Victor winchMotor1, winchMotor2, intakeWheelsMotor;
	Solenoid shifter1, shifter2, winchRelease1, winchRelease2;
	Encoder driveEncoder, winchEncoder;
	NetworkTable *Camtable;
	AnalogChannel *Pot1;
//	AnalogChannel *Pot2;
	DigitalInput WinchLimit;
	
	// Local variables to count the number of periodic loops performed
	int auto_periodic_loops;
	int disabled_periodic_loops;
	int tele_periodic_loops;
	
	int auto_count; // autonomous mode program number
	float auto_dist;
	
	int counter;
	int RightInt;			// To record network table values
	int LeftInt;			// To record network table values
	int TeleTimer;          // To use so winch is released for time
	
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
	//Joy1
	bool l1_button;
	bool r1_button;
	bool A_button;
	
	//Joy2
	float Y_axis;
	bool Y_button2;
	bool A_button2;
	bool B_button2;
	bool r1_button2;
	bool l1_button2;
	
public:
	IronLions(void):
		drive(1,1,1,2,1,3,1,4),
		xbox1(1),
		xbox2(2),
		compressor(1,1),
		gyro(2),
		intakeAngleMotorL(7),
		intakeAngleMotorR(8),
		winchMotor1(5),
		winchMotor2(6),
		intakeWheelsMotor(1,9),
		shifter1(3),
		shifter2(4),
		winchRelease1(1),
		winchRelease2(2),
		driveEncoder(2,3),
		winchEncoder(4,5),
		WinchLimit(6)
	{
		ds = DriverStation::GetInstance();
		Camtable = NetworkTable::GetTable("SmartDashboard");
		Pot1= new AnalogChannel(1);
//		Pot2= new AnalogChannel(3);
		Pot1->SetAverageBits(7);
//		Pot2->SetAverageBits(7);
		
		driveEncoder.SetMaxPeriod(.1);
		driveEncoder.SetDistancePerPulse(.0222);
		driveEncoder.Start();
		
		auto_periodic_loops = 0;
		disabled_periodic_loops = 0;
		tele_periodic_loops = 0;
		
		auto_count = 0;
		auto_dist = 0;
		
		TeleTimer = 0;
		
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
		// increment the num-ber of disabled periodic loops completed
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
		
		winchRelease1.Set(true);
		winchRelease2.Set(false);
		
		if (auto_periodic_loops>50 & auto_periodic_loops <150){
			drive.Move(.8,.8);
		}
		else {
			drive.Move(0,0);
		}
		
		//Will be the Autonomous code eventually, but not for now
		/*
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
		*/
		
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
		
		//Joystick Button Definitions ---------------------------------------------
		
		//Joystick 1
		l1_button = xbox1.GetRawButton(5); //Shifter
		r1_button = xbox1.GetRawButton(6); //Release Of Winch
		A_button = xbox1.GetRawButton(1);  //Encoder Reset
		
		//Joystick 2
		Y_button2 = xbox2.GetRawButton(4); //Directional button X-Axis -1 = left | 1 = right Run Winch
		A_button2 = xbox2.GetRawButton(1); //Intake Angle Setpoint Down
		B_button2 = xbox2.GetRawButton(2); //Intake Angle Setpoint Up
		Y_axis = xbox2.GetY(GenericHID::kLeftHand);      //Intake Angle Up-Down Control
		l1_button2 = xbox2.GetRawButton(5);//Intake Wheels Out
		r1_button2 = xbox2.GetRawButton(6);//Intake Wheels In
		//-------------------------------------------------------------------------
		
		//Run Winch
		if ((Y_button2 == true) && (WinchLimit.Get() == 1)) {
			winchMotor1.Set(1);
			winchMotor2.Set(1);
		}
		else {
			winchMotor1.Set(0);
			winchMotor2.Set(0);
		}
		
		//Release Of Winch
		if (r1_button) { //Shoot ball
			winchRelease1.Set(true);
			winchRelease2.Set(false);
			TeleTimer = 0;
		}
		else if (TeleTimer > 80) {
			winchRelease1.Set(false);
			winchRelease2.Set(true);
		}
		
		/*
		//Intake Angle
		if (A_button2) { //Move pickup to down position
			if (!(Pot1 -> IsEnabled())){
				Pot1 -> Enable();
			}
			if (!(Pot2 -> IsEnabled())){
				Pot2 -> Enable();
			}
		}
		else if (B_button2) { //Move pickup to up position
			if (!(Pot1 -> IsEnabled())){
				Pot1 -> Enable();
			}
			if (!(Pot2 -> IsEnabled())){
				Pot2 -> Enable();
			}
		}
		*/
		if (Y_axis < -.2 || Y_axis > .2){
			if (Y_axis <-.2){
				intakeAngleMotorL.Set(.55);
				intakeAngleMotorR.Set(-.55);
			}
			else{
				intakeAngleMotorL.Set(-.55);
				intakeAngleMotorR.Set(.55);
			}
		}
		else {
			intakeAngleMotorL.Set(0.0);
			intakeAngleMotorR.Set(0.0);
		}
		
		
		//Intake Wheels
		if (r1_button2) { //Run wheels to pickup ball
			intakeWheelsMotor.Set(-1);
		}
		else if (l1_button2) { //Run wheels to push ball out
			intakeWheelsMotor.Set(1);
		}
		else {
			intakeWheelsMotor.Set(0);
		}
		
		
		//Shifting
		if(l1_button==true){
			shifter1.Set(false);
			shifter2.Set(true);
		}
		else {
			shifter1.Set(true);
			shifter2.Set(false);
		}
		
		//Turn On Compressor
		if(!compressor.GetPressureSwitchValue()){
			compressor.Start();
			//printf("Running Compressor \n");
		}
		else {
			compressor.Stop();
			//printf("Not Running Compressor \n");
		}
		
		//Timer
		TeleTimer += 1;
		
		//Print Statements
		//printf("Timer Value: %d",TeleTimer);
		
		//printf("driveEncoderCount: %f \n", (float)(driveEncoder.Get()));
		printf("Pot1 reading: %f  \n", (float)(Pot1 -> GetAverageValue()));
		
		//Drive Arcade
		drive.TeleDrive(xbox1.GetRawAxis(4),xbox1.GetY(GenericHID::kLeftHand));
	}
};

START_ROBOT_CLASS(IronLions);

