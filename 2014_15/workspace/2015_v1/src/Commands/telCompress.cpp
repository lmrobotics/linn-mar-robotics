#include "telCompress.h"

telCompress::telCompress()
{
	Requires(compress);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telCompress::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void telCompress::Execute()
{
	dash->PutBoolean("Compressor running", compress->autoCompress());
}

// Make this return true when this Command no longer needs to run execute()
bool telCompress::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void telCompress::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void telCompress::Interrupted()
{

}
