#include "Commands/autonomousCommand.h"

autonomousCommand::autonomousCommand()
{
	switch (CommandBase::prefs->GetInt("Autonomous",1)){
	case 1:
		CommandBase::dash->PutNumber ("Autonomous Value", 1);
		AddSequential(new auton1T());
		break;
	case 2:
		CommandBase::dash->PutNumber ("Autonomous Value", 2);
		AddSequential(new auton2T());
		break;
	case 3:
		CommandBase::dash->PutNumber ("Autonomous Value", 3);
		AddSequential(new auton3T());
		break;
	default:
		CommandBase::dash->PutNumber ("Autonomous Value", 4);
		AddSequential(new autonDriveIntoZone());
		break;
	}
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}
