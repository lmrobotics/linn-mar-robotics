#include "telArm.h"

telArm::telArm() : yPressed(false)
{
	Requires(wArms);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void telArm::Execute()
{
	if (oi->xbox1_y()){
		if (!yPressed){
			wArms->shift();
			yPressed=true;
		}
	}
	else {
		yPressed=false;
	}
	if (oi->xbox1_x()){
		wArms->pull();
	}
	else if (oi->xbox1_b()){
		wArms->push();
	}
	else {
		wArms->stopWheels();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool telArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void telArm::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void telArm::Interrupted()
{

}
