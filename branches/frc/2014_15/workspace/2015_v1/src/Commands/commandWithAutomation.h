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
	enum runState{
		NORMAL,
		MOVE_ELEVATOR_TO_HEIGHT,
		RESET_ELEVATOR_AND_MAGAZINE,
		AUTO_LOAD_TOTE,
		AUTO_EJECT_TOTE,
		AUTO_GET_TOTE
	};

	commandWithAutomation();
	virtual void Initialize()=0;
	virtual void Execute()=0;
	virtual bool IsFinished()=0;
	virtual void End()=0;
	virtual void Interrupted()=0;

	virtual void normalOperation()=0;
	void moveElevatorToHeight(float heightIN);
	void resetElevatorAndMagazine();
	void autoLoadTote();
	void autoEjectTote();
	void autoGetTote();
	void goToLocation(double angle, double distance);

	void runCurrentLoop();

protected:

	const float deadband =.1;
	runState currentState;
	double targetElevatorHeight;
	const double lowestElevatorHeight=0;
	const double toteLoadHeight=0;
	const double averageRollerSpeed=.5;
	const double averageConveyorSpeed=.5;
	const double elevatorEncoderCountToInches=1000;
	int step;

	std::clock_t timer;

	//These should be run continuously in the execute loop
	//Returns false until the task is finished
	virtual void normalOperationLoop()=0;
	bool moveElevatorToHeightLoop();
	bool resetElevatorAndMagazineLoop();
	bool autoLoadToteLoop();
	bool autoEjectToteLoop();
	bool autoGetToteLoop();
	bool goToLocationLoop();
};

#endif
