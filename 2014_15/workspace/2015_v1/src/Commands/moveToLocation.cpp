#include "moveToLocation.h"

moveToLocation::moveToLocation(float x, float y)
{
	this->x=x;
	this->y=y;
	Requires(drive);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void moveToLocation::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void moveToLocation::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool moveToLocation::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void moveToLocation::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void moveToLocation::Interrupted()
{

}
