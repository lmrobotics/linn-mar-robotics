#include "goToPlace.h"

goToPlace::goToPlace(double angle, double distance): destinationAngle(angle), destinationDistance(distance),
			initialAngle(nav6->GetFilteredYaw()), finalAngle(initialAngle+destinationAngle), done(false),
			currentPhase(turning)
{
	Requires(drive);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void goToPlace::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void goToPlace::Execute()
{
	if (currentPhase==turning){
		if ((nav6->GetFilteredYaw()>finalAngle && destinationAngle>0) ||
				(nav6->GetFilteredYaw()<finalAngle && destinationAngle<0)){
			currentPhase=moving;
		}
		else{
			if (destinationAngle>0)
				drive->Move(.15,-.15);
			else
				drive->Move(-.15,.15);
		}
	}
	else {
		drive->stopdrive();
		done=true;
		//TODO: This section. This section shall be done once the Quaternion math has been figured out and the encoder works
	}
}

// Make this return true when this Command no longer needs to run execute()
bool goToPlace::IsFinished()
{
	return done;
}

// Called once after isFinished returns true
void goToPlace::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void goToPlace::Interrupted()
{

}
