#include "Commands/autonDriveIntoZone.h"
#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/teleopCommand.h"
#include "CommandBase.h"
#include "Commands/pollLIDAR.h"
#include "Commands/testCommand.h"
#include "Commands/autonomousCommand.h"
//#include "Commands/ExampleCommand.h"

class Robot: public IterativeRobot
{
private:
//	Command *autoCommand;
	Command *telCommand;
	Command *tCommand;
//	Command *lidarPoll;
	LiveWindow *lw;
	int test1;
	int *test2;

	void RobotInit()
	{
		CommandBase::init();
//		autoCommand = new autonomousCommand();
		telCommand = new teleopCommand();
		tCommand = new testCommand();
//		lidarPoll = new pollLIDAR();
		lw = LiveWindow::GetInstance();
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
		if (telCommand != NULL)
			telCommand->Cancel();
//		if (autoCommand != NULL)
//			autoCommand->Cancel();
		if (tCommand != NULL)
			tCommand->Cancel();
	}

	void AutonomousInit()
	{

//		if (autoCommand != NULL)
//			autoCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
//		if (autoCommand != NULL)
//			autoCommand->Cancel();
		if (telCommand != NULL)
			telCommand->Start();
//		if (lidarPoll != NULL)
//			lidarPoll->Start();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestInit()
	{
		if (tCommand != NULL)
				tCommand->Start();
		test1=0;
		test2=&test1;
		*test2=1;
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
