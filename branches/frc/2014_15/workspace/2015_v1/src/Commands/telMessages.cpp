#include "telMessages.h"

telMessages::telMessages()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telMessages::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void telMessages::Execute()
{
	dash->PutNumber("Ultrasonic Readings", sonic->getDistance());
	dash->PutBoolean("A", oi->xbox1_a());
	dash->PutBoolean("B", oi->xbox1_b());
	dash->PutBoolean("X", oi->xbox1_x());
	dash->PutBoolean("Y", oi->xbox1_y());
	dash->PutBoolean("Select", oi->xbox1_select());
	dash->PutBoolean("Start", oi->xbox1_start());
	dash->PutBoolean("lB", oi->xbox1_lB());
	dash->PutBoolean("rB", oi->xbox1_rB());
	dash->PutBoolean("lClick", oi->xbox1_lClick());
	dash->PutBoolean("rClick", oi->xbox1_rClick());
}

// Make this return true when this Command no longer needs to run execute()
bool telMessages::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void telMessages::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void telMessages::Interrupted()
{

}
