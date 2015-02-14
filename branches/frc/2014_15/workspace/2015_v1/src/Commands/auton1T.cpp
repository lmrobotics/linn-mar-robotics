#include "auton1T.h"
auton1T::auton1T(): phase(1)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void auton1T::Initialize()
{
	phase=1;
	currentState=NORMAL;
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
	return phase==2;
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
void auton1T::normalOperation(){
	step=1;
	phase++;
	currentState=NORMAL;
}
void auton1T::normalOperationLoop(){
	switch (phase){
	case 1:
		goToLocation(0,24);
		break;
	case 2:
		autoGrabTote();
		break;
	case 3:
		if (turnRight){
			goToLocation(-90,120);
		}
		else {
			goToLocation(90,120);
		}
		break;
	case 4:
		autoEjectTote();
		break;
	}
}
