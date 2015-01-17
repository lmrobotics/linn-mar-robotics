#include "telDrive.h"

telDrive::telDrive()
{
	Requires(drive);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telDrive::Initialize()
{
	dash->PutString("Does It Work?", "YES");
}

// Called repeatedly when this Command is scheduled to run
void telDrive::Execute()
{
	drive->TeleDrive(oi->xbox1_y1(),oi->xbox1_x2());
	if (oi->xbox1_rB() || oi->xbox1_a()){
		drive->lowGear();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool telDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void telDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void telDrive::Interrupted()
{

}
