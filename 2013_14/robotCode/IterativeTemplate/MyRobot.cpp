#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"
#include "floorPickUp.h"
#include <pthread.h>
#include <unistd.h>

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */

//Defined Potentiometer values
#define HOLD_POS		250
#define SHOOT_POS		550
#define PICKUP_POS		843

//Toggleable constants
/*
const float potTopVal1=700;		//Value of Potentiometer 1 when arm is at top
const float potTopVal2=200;		//Value of Potentiometer 2 when arm is at top
const float potBotVal1=200;		//Value of Potentiometer 1 when arm is at bot
const float potBotVal2=700;		//Value of Potentiometer 2 when arm is at bot
*/

class IronLions : public IterativeRobot
{
private:
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
	//NetworkTable *Camtable;
	AnalogChannel *Pot;
	DigitalInput WinchLimit,AutoSwitch;
	Relay *LED;
	int autoThreadID;
	bool autoThreadRunning;
	
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
	bool DoubleAuto;		// True if we're running double autonomous, false if we're running single
	
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
		Intake(1,7,1,8,1,9,1,10),
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
		WinchLimit(6),
		AutoSwitch(10),
		autoThreadID(0),
        autoThreadRunning(false)
	{
		ds = DriverStation::GetInstance();
		SmartDashboard::init();
		//Camtable = NetworkTable::GetTable("SmartDashboard");
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
		DoubleAuto=false;
		
		winchRunning=false;
		
		waitTime = 100;
		
		counter = 0;
		RightInt=0;
		LeftInt=0;
	}
	
	/* Double autonomous */
	static void *DoubleAutoSequence(IronLions *IL)
	{
		IL -> autoThreadRunning = true;
		float autoSpeed = .85;
				
		//Drive and move arm to shooting position
		while (IL -> driveEncoder.GetDistance() < 100){
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(autoSpeed+(angle*(1.0/50.0)),-autoSpeed+(angle*(1.0/50.0)));
			if ((IL -> Pot -> GetAverageValue()) < (SHOOT_POS - 20)){
				IL -> Intake.goToPos(SHOOT_POS,(IL -> Pot -> GetAverageValue()));
				IL -> Intake.moveWheels(-1);
			}
			else {
				IL -> Intake.stop();
				IL -> Intake.moveWheels(0);
			}
			Wait(.01);
		}
		IL -> drive.stopdrive();
		
		//Finish moving arm
		while ((IL -> Pot -> GetAverageValue()) < (SHOOT_POS - 20)){
			IL -> Intake.goToPos(SHOOT_POS,(IL -> Pot -> GetAverageValue()));
			IL -> Intake.moveWheels(-1);
		}
		IL -> Intake.stop();
		IL -> Intake.moveWheels(0);
		Wait(1);
		
		//Shoot
		IL -> winchRelease1.Set(true);
		IL -> winchRelease2.Set(false);
		Wait(.4);
		
		//Reset winch release
		IL -> winchRelease1.Set(false);
		IL -> winchRelease2.Set(true);
		Wait(.1);
		
		//Move arm down while moving catapult down
		IL -> winchEncoder.Reset();
		IL -> winchStart = IL -> winchEncoder.Get();
		while ((IL -> Pot -> GetAverageValue()) < (PICKUP_POS - 20)){
			IL -> Intake.goToPos(PICKUP_POS,(IL -> Pot -> GetAverageValue()));
			IL -> Intake.moveWheels(-1);
			if (IL -> WinchLimit.Get() == 1){
				if (((IL -> winchEncoder.Get())-(IL -> winchStart)) < 2000) {
					IL -> winchMotor1.Set(.85);
					IL -> winchMotor2.Set(.85);
				}
				else {
					IL -> winchMotor1.Set(.8);
					IL -> winchMotor2.Set(.8);
				}
			}
			else{
				IL -> winchMotor1.Set(0);
				IL -> winchMotor2.Set(0);
			}
			Wait(.01);
		}
		IL -> Intake.stop();
		
		//Move back while lowering catapult
		while (IL -> driveEncoder.GetDistance() > 20){
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(-autoSpeed+(angle*(1.0/50.0)),autoSpeed+(angle*(1.0/50.0)));
			IL -> Intake.moveWheels(-1);
			if (IL -> WinchLimit.Get() == 1){
				if (((IL -> winchEncoder.Get())-(IL -> winchStart)) < 2000) {
					IL -> winchMotor1.Set(.85);
					IL -> winchMotor2.Set(.85);
				}
				else {
					IL -> winchMotor1.Set(.8);
					IL -> winchMotor2.Set(.8);
				}
			}
			else{
				IL -> winchMotor1.Set(0);
				IL -> winchMotor2.Set(0);
			}
			Wait(.01);
		}
		IL -> drive.stopdrive();
		
		//Keep lowering catapult if it isn't done yet
		while (IL -> WinchLimit.Get() == 1){
			if (((IL -> winchEncoder.Get())-(IL -> winchStart)) < 2000) {
				IL -> winchMotor1.Set(.85);
				IL -> winchMotor2.Set(.85);
			}
			else {
				IL -> winchMotor1.Set(.8);
				IL -> winchMotor2.Set(.8);
			}
			Wait(.01);
		}
		IL -> winchMotor1.Set(0);
		IL -> winchMotor2.Set(0);
		
		//Move back while turning intake wheels
		while (IL -> driveEncoder.GetDistance() > 15){
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(-autoSpeed+(angle*(1.0/50.0)),autoSpeed+(angle*(1.0/50.0)));
			IL -> Intake.moveWheels(-1);
			Wait(.01);
		}
		IL -> drive.stopdrive();
		
		//Keep running intake
		for (int i=0; i<30; i++){
			IL -> Intake.moveWheels(-1);
			Wait(.02);
		}
		
		//Move arm up to shooting position
		while ((IL -> Pot -> GetAverageValue()) > (SHOOT_POS + 20)){
			IL -> Intake.goToPos(SHOOT_POS,(IL -> Pot -> GetAverageValue()));
			IL -> Intake.moveWheels(-1);
			Wait(.01);
		}
		IL -> Intake.stop();
		Wait(.1);
		
		//Drive to shooting position
		while (IL -> driveEncoder.GetDistance() < 120){
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(autoSpeed+(angle*(1.0/50.0)),-autoSpeed+(angle*(1.0/50.0)));
			IL -> Intake.moveWheels(-1);
			Wait(.01);
		}
		IL -> Intake.moveWheels(0);
		IL -> drive.stopdrive();
		Wait(.8);
		
		//Shoot again
		IL -> winchRelease1.Set(true);
		IL -> winchRelease2.Set(false);
		Wait(.1);

		IL -> autoThreadRunning = false;
		return 0;
	}

	/* Single autonomous */
	static void *SingleAutoSequence(IronLions *IL)
	{
		IL->autoThreadRunning = true;
		
		//Drive and move arm to shooting position
		while (IL -> driveEncoder.GetDistance() < 100){
			//IL -> drive.Move(.54,-.5);
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(.5+(angle*(1.0/50.0)),-.5+(angle*(1.0/50.0)));
			if ((IL -> Pot -> GetAverageValue()) < (SHOOT_POS - 20)){
				IL -> Intake.goToPos(SHOOT_POS,(IL -> Pot -> GetAverageValue()));
				IL -> Intake.moveWheels(-1);
			}
			else {
				IL -> Intake.stop();
				IL -> Intake.moveWheels(0);
			}
			Wait(.01);
		}
		IL -> drive.stopdrive();
		
		//Finish moving arm
		while ((IL -> Pot -> GetAverageValue()) < (SHOOT_POS - 20)){
			IL -> Intake.goToPos(SHOOT_POS,(IL -> Pot -> GetAverageValue()));
			IL -> Intake.moveWheels(-1);
		}
		IL -> Intake.stop();
		IL -> Intake.moveWheels(0);
		Wait(1);
		
		//Shoot
		IL -> winchRelease1.Set(true);
		IL -> winchRelease2.Set(false);

		IL->autoThreadRunning = false;
		return 0;
	}

	/* Test function for autonomous */
	static void *TestAuto(IronLions *IL)
	{
		IL -> autoThreadRunning = true;
		
		while(IL -> autoThreadRunning) {
			float angle = IL -> gyro.GetAngle();
			IL -> drive.Move(.5+(angle*(1.0/50.0)),-.5+(angle*(1.0/50.0)));
		}
		
		IL -> autoThreadRunning = false;
		return 0;
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
	
	// Suspend the autonomous thread and delete it
	void IronLions::StopAutoThread()
	{
		//Not changing autoThreadRunning to false
		if (autoThreadRunning)
		{
			printf("Suspending and deleting auto thread\n");
			int status = taskSuspend(autoThreadID);
			status = taskDelete(autoThreadID);
			if (status == ERROR )
			{
				printf("Forcibly deleting auto thread\n");
				status = taskDeleteForce(autoThreadID);
			}
			printf("Stopped thread");
			autoThreadRunning = false;
		}
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
		StopAutoThread();
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
		auto_periodic_loops = 0;
		LED ->Set(Relay::kForward);
		currentPos = Pot -> GetAverageValue();
				
		if (AutoSwitch.Get()==1) {
			DoubleAuto=true;
		}
		else {
			DoubleAuto=false;
		}
		
		if (!autoThreadRunning)
		{
			// comment out or remove this line when satisfied with auto thread test
			if (DoubleAuto)
			{
				autoThreadID = taskSpawn("DoubleAuto", 150, VX_FP_TASK, 20000, (FUNCPTR)DoubleAutoSequence, (int)this,0,0,0,0,0,0,0,0,0);
				//autoThreadID = taskSpawn("TestAuto", 150, VX_FP_TASK, 20000, (FUNCPTR)TestAuto, (int)this,0,0,0,0,0,0,0,0,0);
			}
			else
			{
				autoThreadID = taskSpawn("SingleAuto", 150, VX_FP_TASK, 20000, (FUNCPTR)SingleAutoSequence, (int)this,0,0,0,0,0,0,0,0,0);		    	
			}
			if (autoThreadID==ERROR)
			{
				printf("Autonomous Thread failed to start!!!\n");
			}
		}
		else {
			printf("Thread Already Running");
		}
		shifter1.Set(false);
		shifter2.Set(true);
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
		dash ->PutNumber("DriveEncoder", driveEncoder.Get());
		dash ->PutNumber("Intake Angle",Pot -> GetAverageValue());
		dash ->PutNumber("Gyro", gyro.GetAngle());
		shifter1.Set(false);
		shifter2.Set(true);
//		int TaskPrioVal=0;
//		taskPriorityGet(taskIdSelf(),&TaskPrioVal);
//		printf("Thread Priority: %d \n", TaskPrioVal);
		auto_periodic_loops++;
	}
	
	/**
	 * Initialization code for teleop mode should go here.
	 * 
	 * Use this method for initialization code which will be called each time
	 * the robot enters teleop mode.
	 */
	void IronLions::TeleopInit() 
	{
		printf("Entering TeleopInit\n");
		StopAutoThread();
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
				winchMotor1.Set(.85);
				winchMotor2.Set(.85);
			}
			else {
				winchMotor1.Set(.8);
				winchMotor2.Set(.8);
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
				Intake.moveAngle(.5,0);
			}
			else {              //Run Intake Up
				Intake.moveAngle(.5,1);
			}
		}
		else if ((Y_axis >= .8) || (Y_axis <= -.8)) {
			if (Y_axis >= .8) {
				Intake.moveAngle(.7,1);				
			}
			else {
				Intake.moveAngle(.7,0);				
			}
		}
		else if (A_button2) { //Move pickup to pickup position
			Intake.goToPos(PICKUP_POS, currentPos);
		}
		else if (B_button2) { //Move pickup to shoot position
			Intake.goToPos(SHOOT_POS, currentPos);
		}
		else if (X_button2) { //Move to carry postion
			Intake.goToPos(HOLD_POS, currentPos);
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
		dash ->PutNumber("Gyro", gyro.GetAngle());
		
		//Drive Arcade
		drive.TeleDrive(xbox1.GetRawAxis(4),xbox1.GetY(GenericHID::kLeftHand));
	}
};

START_ROBOT_CLASS(IronLions);
