#include "pollLIDAR.h"

pollLIDAR::pollLIDAR(): pollTimer(0)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void pollLIDAR::Initialize()
{
	lastPoll = std::clock();
	lidar->setup();
}

// Called repeatedly when this Command is scheduled to run
void pollLIDAR::Execute()
{
	pollTimer = 3.0*(double)(std::clock() - lastPoll) / (double) CLOCKS_PER_SEC;
	dash ->PutString ("Test", "10");
	if (pollTimer>.20){
		dash->PutNumber("Poll Status:", lidar->poll());
		resetPollTimer();
	}
	dash->PutNumber("Poll Timer", pollTimer);
}

// Make this return true when this Command no longer needs to run execute()
bool pollLIDAR::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void pollLIDAR::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void pollLIDAR::Interrupted()
{

}

void pollLIDAR::resetPollTimer(){
	lastPoll = std::clock();
}
