#include "auton1T.h"
auton1T::auton1T(): phase(1), turnRight(true)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void auton1T::Initialize()
{
	drive->highGear();
	phase=1;
	currentElevatorState=ELEVATOR_NORMAL;
	currentDriveState=DRIVE_NORMAL;
	turnRight=true;
}

// Called repeatedly when this Command is scheduled to run
void auton1T::Execute()
{
	runCurrentLoop();
}

// Make this return true when this Command no longer needs to run execute()
bool auton1T::IsFinished()
{
	return phase==6;
}

// Called once after isFinished returns true
void auton1T::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void auton1T::Interrupted()
{

}

//Changes the direction that the robot will turn after it picks up the tote/bin
void auton1T::setTurnRight(bool turnRight){
	this->turnRight=turnRight;
}

// Normal operation schedules the actions to be carried out. The integer "phase" is used to track what the program is doing now and
// what it will do next
void auton1T::normalElevatorOperation(){
	elevatorStep=1;
	phase++;
	currentElevatorState=ELEVATOR_NORMAL;
}
void auton1T::normalElevatorOperationLoop(){
	switch (phase){
	case 1:
		autoLoadTote();
		break;
	case 4:
		autoEjectTote();
		break;
	}
}

void auton1T::normalDriveOperation(){
	driveStep=1;
	phase++;
	currentDriveState=DRIVE_NORMAL;
}
void auton1T::normalDriveOperationLoop(){
	switch (phase){
	case 1:
		drive->stopdrive();
		break;
	case 2:
		if (turnRight){
			goToLocation(90,100);
		}
		else {
			goToLocation(-90,100);
		}
		break;
	case 3:
		goToLocation(70,0);
		break;
	case 4:
		drive->stopdrive();
		break;
	case 5:
		goToLocation(0,-12);
		break;
	}
}
