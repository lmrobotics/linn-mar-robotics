#include "WPILib.h"
#include "LIDAR.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	LIDAR lidar;
	int counter;
public:
	Robot() : lidar(), counter(0)
	{
		SmartDashboard::init();
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			SmartDashboard::PutNumber ("Counter", counter++);
			SmartDashboard::PutNumber ("Poll Status", (double)lidar.poll());
			SmartDashboard::PutNumber ("LIDAR Reading (Plz Work)", lidar.getCM());
			SmartDashboard::PutNumber ("LIDAR High", (double)lidar.getHigh());
			SmartDashboard::PutNumber ("LIDAR Low", (double)lidar.getLow());
			SmartDashboard::PutNumber ("LIDAR Status", (double)lidar.getLidarStatus());
			Wait(0.025);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
