#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include "Commands/Command.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/Drive.h"
#include "myUltrasonic.h"
#include "Subsystems/myCompressor.h"
#include "Subsystems/Elevator.h"
#include "LIDAR.h"
#include "IMUProcess.h"
#include "OI.h"
#include "WPILib.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static ExampleSubsystem *examplesubsystem;
	static OI *oi;
	static Drive *drive;
	static myUltrasonic *sonic;
	static SmartDashboard *dash;
	static myCompressor *compress;
	static IMUProcess *nav6;
	static SerialPort *nav6Port;
	static Encoder *driveEncoder;
	static Encoder *elevatorEncoder;
	static LIDAR *lidar;
	static Elevator *elevator;
	static Preferences *prefs;
	static DigitalInput *elevatorLimit;
};

#endif
