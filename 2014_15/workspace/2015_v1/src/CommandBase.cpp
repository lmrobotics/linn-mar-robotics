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
IMUProcess* CommandBase::nav6 = NULL;
SerialPort* CommandBase::nav6Port = NULL;
Encoder* CommandBase::encoder = NULL;
LIDAR* CommandBase::lidar = NULL;

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
	drive = new Drive(0,1,0,0,1);
	sonic = new myUltrasonic(0);
	wArms = new wheelArms(2,3,0,2,3);
	compress = new myCompressor(0);
	nav6Port = new SerialPort(57600,SerialPort::kOnboard);
	uint8_t update_rate_hz = 50;
	nav6 = new IMUProcess(nav6Port,update_rate_hz);
	encoder = new Encoder(0,1);
	lidar = new LIDAR();

	SmartDashboard::init();
}
