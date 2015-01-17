#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
ExampleSubsystem* CommandBase::examplesubsystem = NULL;
OI* CommandBase::oi = NULL;
Drive* CommandBase::drive = NULL;
myUltrasonic* CommandBase::sonic = NULL;
wheelArms* CommandBase::wArms = NULL;
myCompressor* CommandBase::compress = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	examplesubsystem = new ExampleSubsystem();

	oi = new OI();
	drive = new Drive(0,1,0,0,1,0,1);
	sonic = new myUltrasonic(0);
	wArms = new wheelArms(2,3,0,2,3);
	compress = new myCompressor(0);
	SmartDashboard::init();
}
