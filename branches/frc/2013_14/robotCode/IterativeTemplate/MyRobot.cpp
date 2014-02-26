#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"
#include "floorPickUp.h"

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
	FloorPickUp Intake;
	
	DriverStation *ds;
	SmartDashboard *dash;
	Joystick xbox1,xbox2;
	Compressor compressor;
	Gyro gyro;
	Victor winchMotor1, winchMotor2;
	Solenoid shifter1, shifter2, winchRelease1, winchRelease2;
	Encoder driveEncoder, winchEncoder;
	NetworkTable *Camtable;
	AnalogChannel *Pot;
	DigitalInput WinchLimit;
	Relay *LED;
	
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
	int autoState;			// The current phase of autonomous
	int autoStateLoops;		// Records the number of loops spent in each state
	bool autoLeft;			// True if doing double autonomous on left side, false if doing double autonomous on right
	
	bool winchRunning;
	int winchStart;
	
	float currentPos;
	
	int waitTime;
	
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
	bool X_button2;
	bool r1_button2;
	bool l1_button2;
	bool rightjoy2;
	
public:
	IronLions(void):
		drive(1,1,1,2,1,3,1,4),
		Intake(1,7,1,8,1,9),
		xbox1(1),
		xbox2(2),
		compressor(1,1),
		gyro(2),
		winchMotor1(5),
		winchMotor2(6),
		shifter1(3),
		shifter2(4),
		winchRelease1(1),
		winchRelease2(2),
		driveEncoder(2,3),
		winchEncoder(4,5),
		WinchLimit(6)
	{
		ds = DriverStation::GetInstance();
		SmartDashboard::init();
		Camtable = NetworkTable::GetTable("SmartDashboard");
		Pot= new AnalogChannel(1);
		
		LED = new Relay(8);
		
		driveEncoder.SetMaxPeriod(.1);
		driveEncoder.SetDistancePerPulse(.0222);
		driveEncoder.Start();
		
		auto_periodic_loops = 0;
		disabled_periodic_loops = 0;
		tele_periodic_loops = 0;
		
		auto_count = 0;
		auto_dist = 0;
		
		TeleTimer = 0;
		autoState=1;
		autoStateLoops=0;
		autoLeft=true;
		
		winchRunning=false;
		
		waitTime = 100;
		
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
		autoState = 2;
		auto_periodic_loops = 0;
		LED ->Set(Relay::kForward);
		currentPos = Pot -> GetAverageValue();
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
		LED ->Set(Relay::kForward);
		currentPos = Pot -> GetAverageValue();
		
		dash ->PutNumber("Drive Encoder", driveEncoder.Get());
		dash ->PutNumber("Drive Encoder Distance", driveEncoder.GetDistance());
		
		switch (autoState)
		{
			
			//Cases 1-500: Single autonomous code.
			
			//Phase 1: Prepare to Shoot the first ball and the shoot it. Also, process vision stuff if that code needs to be here		
			case 1:		//First chunk of movement. Any vision related code that doesn't fit in Autonomous Init will go here too
				if (driveEncoder.GetDistance() < 35){
					drive.Move(.5,-.5);
					/*if (Camtable->ContainsKey("LeftBool")){
						Camtable->GetNumber("LeftBool",LeftInt);
					}
					if (Camtable->ContainsKey("RightBool")){
						Camtable->GetNumber("RightBool",RightInt);
					}*/
				}
				else {
					drive.stopdrive();
				}
				if (currentPos < 410) {
					Intake.goToPos(420.0,currentPos);
					Intake.moveWheels(-1);
				}
				else {
					Intake.holdPos(420,currentPos);
					Intake.moveWheels(0);
				}
				if ((driveEncoder.GetDistance()>35) && (currentPos >= 410)){					
					if ((LeftInt == 1) || (RightInt==1)){
						waitTime=50;
					}
					else {
						waitTime=300;
					}
					if (auto_periodic_loops > waitTime) {
						drive.Move(0.0,0.0);
						winchRelease1.Set(true);
						winchRelease2.Set(false);
					}
				}
				break;
				
			case 2:
				if (currentPos < 410) {
					Intake.goToPos(420.0,currentPos);
					Intake.moveWheels(-1);
				}
				else {					
					if ((LeftInt == 1) || (RightInt==1)){
						waitTime=50;
					}
					else {
						waitTime=300;
					}
					Intake.holdPos(420,currentPos);
					Intake.moveWheels(0);
					auto_periodic_loops = 0;
					autoState = 3;
				}
				break;
			case 3:
				if (auto_periodic_loops > waitTime) {
					winchRelease1.Set(true);
					winchRelease2.Set(false);
				}
				if (winchRelease1.Get()==true) {
					if (driveEncoder.GetDistance() < 35){
						drive.Move(.5,-.5);
					}
					else {
						drive.stopdrive();
					}
				}
				break;
//-----------------------------------------------------------------------------------------------------------------------------
			
			//Cases 500-1500: Double Autonomous code
			
			//Phase 1: Pick up other ball and process vision
			case 499:
				if ((currentPos < 460) || (currentPos > 600)) {
					Intake.goToPos(480.0,currentPos);
					Intake.moveWheels(-1);
					auto_periodic_loops = 0;
				}
				else {
					Intake.holdPos(480,currentPos);
					Intake.moveWheels(0);
					if (auto_periodic_loops > 60) {
						autoState=500;
					}
				}
				break;
			case 500:
				if (currentPos < 760) {
					winchRelease1.Set(true);
					winchRelease2.Set(false);
					Intake.goToPos(770,currentPos);
				}
				else {
					Intake.holdPos(770,currentPos);
					Wait(1);
					winchRelease1.Set(false);
					winchRelease2.Set(true);
					autoState=501;
				}
				break;
			case 501:
				if (WinchLimit.Get() == 1) {
					winchMotor1.Set(1);
					winchMotor2.Set(1);
				}
				else {
					winchMotor1.Set(0);
					winchMotor2.Set(0);
					auto_periodic_loops = 0;
					autoState=502;
				}
				break;
			case 502:
				if (auto_periodic_loops < 50){
					//drive.Move(-.4,.4);
					Intake.moveWheels(-1);
				}
				else {
					auto_periodic_loops = 0;
					autoState = 504;
				}
				break;
				/*case 503:
				if (driveEncoder.GetDistance() < 5){
					auto_periodic_loops = 0;
					drive.Move(.4,-.4);
				}
				else if (driveEncoder.GetDistance()>=5){
					drive.stopdrive();
					if (auto_periodic_loops > 30) {
						autoState = 504;
						auto_periodic_loops = 0;
					}
				}
				break;*/
			case 504:
				if (currentPos > 600) {
					Intake.goToPos(580,currentPos);
				}
				else {
					Intake.holdPos(580,currentPos);
					if (auto_periodic_loops > 80) {
						Intake.moveWheels(0);
						auto_periodic_loops = 0;
						winchRelease1.Set(true);
						winchRelease2.Set(false);
						autoState = 505;
					}
				}
				break;
			case 505:
				if (auto_periodic_loops > 50) {
					if (driveEncoder.GetDistance() < 35){
						drive.Move(.5,-.5);
					}
					else {
						drive.stopdrive();
					}
				}
				else {
					drive.stopdrive();
				}
				break;
				
			//Default case. Simply stops the robot
			default:
				drive.Move(0.0,0.0);
				break;
		}
		
		printf("driveEncoder Dist: %f\n", (driveEncoder.GetDistance()));
		printf("auto_periodic: %d",auto_periodic_loops);
		dash ->PutNumber("Intake Angle",Pot -> GetAverageValue());
		auto_periodic_loops++;
		autoStateLoops++;
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
		winchEncoder.Start();
		winchEncoder.Reset();
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
		A_button2 = xbox2.GetRawButton(1); //Intake Angle Setpoint pickup
		B_button2 = xbox2.GetRawButton(2); //Intake Angle Setpoint shoot
		X_button2 = xbox2.GetRawButton(3); //Intake Angle Setpoint drive
		Y_axis = xbox2.GetY(GenericHID::kLeftHand);      //Intake Angle Up-Down Control
		l1_button2 = xbox2.GetRawButton(5);//Intake Wheels Out
		r1_button2 = xbox2.GetRawButton(6);//Intake Wheels In
		rightjoy2 = xbox2.GetRawButton(10);//Winch Cancel
		//-------------------------------------------------------------------------
		
		currentPos = Pot -> GetAverageValue();
		LED ->Set(Relay::kForward);
		
		//Run Winch
		if ((Y_button2 == true) && (WinchLimit.Get() == 1) && (winchRunning == false)) {
			winchEncoder.Reset();
			winchStart = winchEncoder.Get();
			winchRunning = true;
		}
		//Cancel winch movement
		else if (((rightjoy2 == true) && (winchRunning == true)) || ((winchEncoder.Get()-winchStart)>3200)) {
			winchMotor1.Set(0);
			winchMotor2.Set(0);
			winchRunning = false;
		}
		//Slow down when close to switch
		if ((winchRunning == true) && (WinchLimit.Get() == 1)) {
			if (((winchEncoder.Get()-winchStart) < 2000)) {
				winchMotor1.Set(1);
				winchMotor2.Set(1);
			}
			else {
				winchMotor1.Set(.95);
				winchMotor2.Set(.95);
			}
		}
		else {
			winchMotor1.Set(0);
			winchMotor2.Set(0);
			winchRunning = false;
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
		//Timer For WinchRelease
		if (TeleTimer < 90){
			TeleTimer += 1;
		}
		else {
			TeleTimer = TeleTimer;
		}
		
		//Intake Angle
		if (((Y_axis < -.2) && (Y_axis > -.8)) || ((Y_axis > .2) && (Y_axis < .8))){
			if (Y_axis < -.2) { //Run Intake Down
				Intake.moveAngle(.4,0);
			}
			else {              //Run Intake Up
				Intake.moveAngle(.4,1);
			}
		}
		else if ((Y_axis >= .8) || (Y_axis <= -.8)) {
			if (Y_axis >= .8) {
				Intake.moveAngle(.6,1);				
			}
			else {
				Intake.moveAngle(.6,0);				
			}
		}
		else if (A_button2) { //Move pickup to pickup position
			Intake.goToPos(800.0, currentPos);
		}
		else if (B_button2) { //Move pickup to shoot position
			Intake.goToPos(535.0, currentPos);
		}
		else if (X_button2) { //Move to carry postion
			Intake.goToPos(190.0, currentPos);
		}
		else {
			Intake.stop();
		}
		
		
		//Intake Wheels
		if (l1_button2) { //Run wheels to push ball out
			Intake.moveWheels(1);
		}
		else if (r1_button2) { //Run wheels to pickup ball
			Intake.moveWheels(-1);
		}
		else {
			Intake.moveWheels(0);
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
		}
		else {
			compressor.Stop();
		}
		
		//Print Statements		
		//printf("driveEncoderCount: %f \n", (float)(driveEncoder.Get()));
		
		//Smart Dashboard Values
		dash ->PutNumber("Intake Angle",Pot -> GetAverageValue());
		dash ->PutNumber("Winch Encoder", winchEncoder.Get());
		dash ->PutNumber("Winch Limit", WinchLimit.Get());
		dash ->PutNumber("Tele Timer", TeleTimer);
		dash ->PutNumber("DriveEncoder", driveEncoder.Get());
		
		//Drive Arcade
		drive.TeleDrive(xbox1.GetRawAxis(4),xbox1.GetY(GenericHID::kLeftHand));
	}
};

START_ROBOT_CLASS(IronLions);

