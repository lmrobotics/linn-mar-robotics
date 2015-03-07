#ifndef commandWithAutomatedFunctions_H
#define commandWithAutomatedFunctions_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <iostream>
#include <cstdio>
#include <ctime>

class commandWithAutomation: public CommandBase
{
public:
	enum elevatorState{
		ELEVATOR_NORMAL,
		MOVE_ELEVATOR_TO_HEIGHT,
		RESET_ELEVATOR,
		AUTO_LOAD_TOTE,
		AUTO_EJECT_TOTE,
		AUTO_GET_TOTE,
		AUTO_GRAB_TOTE,
	};

	enum driveState{
		DRIVE_NORMAL,
		GO_TO_LOCATION
	};

	commandWithAutomation();
	virtual void Initialize()=0;
	virtual void Execute()=0;
	virtual bool IsFinished()=0;
	virtual void End()=0;
	virtual void Interrupted()=0;

	virtual void normalElevatorOperation()=0;
	virtual void normalDriveOperation()=0;
	void moveElevatorToHeight(float heightIN);
	void resetElevator();
	void autoLoadTote();
	void autoEjectTote();
	void autoGetTote();
	void autoGrabTote();
	void goToLocation(double angle, double distance);

	void runCurrentLoop();

	const double toteLowestHeight=.15;
	const double toteHoldHeight=18;
	const double averageRollerSpeed=.5;
	const double averageConveyorSpeed=.5;

protected:

	PIDController drivePID;
	const float deadband =.1;
	elevatorState currentElevatorState;
	driveState currentDriveState;

	//Target Angle/Distance in "goToLocation"
	double targetAngle;
	double targetDistance;
	//Initial conditions when running "goToLocation"
	double initialAngle;
	double initialDistance;

	double targetElevatorHeight;
	int elevatorStep;
	int driveStep;

	std::clock_t elevatorTimer;
	std::clock_t driveTimer;

	//These should be run continuously in the execute loop
	//Returns false until the task is finished
	virtual void normalElevatorOperationLoop()=0;
	virtual void normalDriveOperationLoop()=0;
	bool moveElevatorToHeightLoop();
	bool resetElevatorLoop();
	bool autoLoadToteLoop();
	bool autoEjectToteLoop();
	bool autoGetToteLoop();
	bool autoGrabToteLoop();
	bool goToLocationLoop();
};

#endif
