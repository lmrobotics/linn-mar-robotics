#include "telMessages.h"

telMessages::telMessages(): counter(0)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telMessages::Initialize()
{
	counter=0;
}

// Called repeatedly when this Command is scheduled to run
void telMessages::Execute()
{
	counter++;
	dash ->PutNumber ("nav6 Yaw", nav6->GetYaw());
	dash ->PutNumber ("nav6 Pitch", nav6->GetPitch());
	dash ->PutNumber ("nav6 Roll", nav6->GetRoll());
	dash ->PutNumber ("nav6 X Acceleration", nav6->GetWorldLinearAccelX());
	dash ->PutNumber ("nav6 Y Acceleration", nav6->GetWorldLinearAccelY());
	dash ->PutNumber ("nav6 Z Acceleration", nav6->GetWorldLinearAccelZ());
//	dash ->PutNumber ("nav6 Temperature (C)", nav6->GetTempC());
//	dash ->PutNumber ("nav6 Is Connected", nav6->IsConnected());
//	dash ->PutNumber ("nav6 Is Calibrating", nav6->IsCalibrating());
	dash ->PutNumber ("nav6 Fatal Status", nav6Port -> StatusIsFatal());
	dash ->PutNumber ("counter", counter);
	dash ->PutNumber ("drive encoder raw", driveEncoder->GetRaw());
	dash ->PutNumber ("elevator encoder raw", elevatorEncoder->GetRaw());
	dash ->PutNumber ("drive encoder", driveEncoder->Get());
	dash ->PutNumber ("elevator encoder", elevatorEncoder->Get());
	dash ->PutNumber ("drive encoder distance", driveEncoder->GetDistance());
	dash ->PutNumber ("elevator encoder distance", elevatorEncoder->GetDistance());
	dash ->PutNumber ("Autonomous Value",prefs->GetInt("Autonomous",1));

	//LIDAR Crap
	dash ->PutNumber ("LIDAR Reading (Plz Work)", lidar->getCM());
	dash ->PutNumber ("LIDAR High", (double)lidar->getHigh());
	dash ->PutNumber ("LIDAR Low", (double)lidar->getLow());
	dash ->PutNumber ("LIDAR Status", (double)lidar->getLidarStatus());
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
