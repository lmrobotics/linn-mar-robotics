#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
ExampleSubsystem* CommandBase::examplesubsystem = NULL;
OI* CommandBase::oi = NULL;
Drive* CommandBase::drive = NULL;
myUltrasonic* CommandBase::sonic = NULL;
myCompressor* CommandBase::compress = NULL;
IMUProcess* CommandBase::nav6 = NULL;
SerialPort* CommandBase::nav6Port = NULL;
Encoder* CommandBase::driveEncoder = NULL;
Encoder* CommandBase::elevatorEncoder = NULL;
LIDAR* CommandBase::lidar = NULL;
Elevator* CommandBase::elevator = NULL;
BlankPIDOutput* CommandBase::PIDPlacebo = NULL;
Preferences* CommandBase::prefs = NULL;

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
	drive = new Drive(0,1,0,0,7);
	sonic = new myUltrasonic(0);
	compress = new myCompressor(0);
	nav6Port = new SerialPort(57600,SerialPort::kOnboard);
	uint8_t update_rate_hz = 50;
	nav6 = new IMUProcess(nav6Port,update_rate_hz);
	driveEncoder = new Encoder(0,1,false,Encoder::EncodingType::k4X);
	elevatorEncoder = new Encoder(2,3,false,Encoder::EncodingType::k4X);

	//TODO: Test these and find what the values should actually be
	driveEncoder->SetDistancePerPulse(.02371);
	elevatorEncoder->SetDistancePerPulse(.01537);

	driveEncoder->Reset();
	elevatorEncoder->Reset();
	lidar = new LIDAR();
	elevator = new Elevator(5, 3, 4, 0, 1, 6, 3, 4, 0, 2, 5);
	SmartDashboard::init();
	PIDPlacebo = new BlankPIDOutput();
	prefs = Preferences::GetInstance();
}
