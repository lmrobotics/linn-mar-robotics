#include "telMessages.h"

telMessages::telMessages()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telMessages::Initialize()
{
	dash ->PutBoolean("LIDAR Write Test", "false");
//	while (lidar->setup()){
//		Wait(.001);
//	}
	dash ->PutBoolean("LIDAR Write Test", "true");
	counter=0;
}

// Called repeatedly when this Command is scheduled to run
void telMessages::Execute()
{
	counter++;
	//unsigned char *readTest01= new unsigned char;
	//unsigned char *readTest04= new unsigned char;
//	dash ->PutBoolean("LIDAR set", lidar->setup());
	//dash ->PutNumber ("Ultrasonic Readings", sonic->getDistance());
	dash ->PutNumber ("nav6 Yaw", nav6->GetYaw());
	dash ->PutNumber ("nav6 Pitch", nav6->GetPitch());
	dash ->PutNumber ("nav6 Roll", nav6->GetRoll());
//	dash ->PutNumber ("nav6 Update Count", nav6->GetUpdateCount());
//	dash ->PutNumber ("nav6 Byte Count", nav6->GetByteCount());
	dash ->PutNumber ("nav6 X Acceleration", nav6->GetWorldLinearAccelX());
	dash ->PutNumber ("nav6 Y Acceleration", nav6->GetWorldLinearAccelY());
	dash ->PutNumber ("nav6 Z Acceleration", nav6->GetWorldLinearAccelZ());
//	dash ->PutNumber ("nav6 Temperature (C)", nav6->GetTempC());
//	dash ->PutNumber ("nav6 Is Connected", nav6->IsConnected());
//	dash ->PutNumber ("nav6 Is Moving", nav6->IsMoving());
//	dash ->PutNumber ("nav6 Is Calibrating", nav6->IsCalibrating());
//	dash ->PutNumber ("nav6 Byte Count", nav6->GetByteCount());
	dash ->PutNumber ("nav6 Fatal Status", nav6Port -> StatusIsFatal());
	dash ->PutNumber ("counter", counter);

/*
	dash ->PutNumber ("LIDAR Reading (Plz Work)", lidar->getCM());
	dash ->PutNumber ("LIDAR High", (double)lidar->getHigh());
	dash ->PutNumber ("LIDAR Low", (double)lidar->getLow());
	dash ->PutNumber ("LIDAR Status", (double)lidar->getLidarStatus());
	dash ->PutBoolean ("Joystick A Tapped", oi->xbox1_aTapped());
*/


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
