#ifndef commandWithAutomatedFunctions_H
#define commandWithAutomatedFunctions_H

#include "../CommandBase.h"
#include "WPILib.h"

class commandWithAutomation: public CommandBase
{
public:
	enum runState{
		NORMAL,
		MOVE_ELEVATOR_TO_HEIGHT,
		RESET_ELEVATOR_AND_MAGAZINE,
		AUTO_LOAD_CRATE,
		AUTO_EJECT_CRATE,
		AUTO_GET_CRATE
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
	void autoLoadCrate();
	void autoEjectCrate();
	void autoGetCrate();

	void runCurrentLoop();

protected:

	const float deadband =.1;
	runState currentState;

	//These should be run continuously in the execute loop
	//Returns false until the task is finished
	virtual void normalOperationLoop()=0;
	bool moveElevatorToHeightLoop();
	bool resetElevatorAndMagazineLoop();
	bool autoLoadCrateLoop();
	bool autoEjectCrateLoop();
	bool autoGetCrateLoop();
};

#endif
