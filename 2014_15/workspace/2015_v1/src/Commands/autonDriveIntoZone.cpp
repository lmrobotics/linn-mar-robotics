#include "autonDriveIntoZone.h"

autonDriveIntoZone::autonDriveIntoZone(): phase(1)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void autonDriveIntoZone::Initialize()
{
	phase=1;
	currentDriveState=DRIVE_NORMAL;
	currentElevatorState=ELEVATOR_NORMAL;
}

// Called repeatedly when this Command is scheduled to run
void autonDriveIntoZone::Execute()
{
	runCurrentLoop();
}

// Make this return true when this Command no longer needs to run execute()
bool autonDriveIntoZone::IsFinished()
{
	return phase==2;
}

// Called once after isFinished returns true
void autonDriveIntoZone::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void autonDriveIntoZone::Interrupted()
{

}

// Normal operation schedules the actions to be carried out. The integer "phase" is used to track what the program is doing now and
// what it will do next
void autonDriveIntoZone::normalDriveOperation(){
	driveStep=1;
	phase++;
	currentDriveState=DRIVE_NORMAL;
}
void autonDriveIntoZone::normalDriveOperationLoop(){
	switch (phase){
	case 1:
		goToLocation(0,108);
		break;
	case 2:
		drive->stopdrive();
		break;
	}
}

void autonDriveIntoZone::normalElevatorOperation(){
	elevatorStep=1;
	phase++;
	currentElevatorState=ELEVATOR_NORMAL;
}
void autonDriveIntoZone::normalElevatorOperationLoop(){

}

