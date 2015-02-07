#include "Commands/commandWithAutomation.h"

commandWithAutomation::commandWithAutomation()
{
	Requires(drive);
	Requires(elevator);
	currentState=NORMAL;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

void commandWithAutomation::runCurrentLoop(){
	if (currentState == NORMAL) {
		normalOperationLoop();
	}
	else if (currentState == MOVE_ELEVATOR_TO_HEIGHT) {
		if (moveElevatorToHeightLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == RESET_ELEVATOR_AND_MAGAZINE) {
		if (resetElevatorAndMagazineLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_LOAD_CRATE) {
		if (autoLoadCrateLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_EJECT_CRATE) {
		if (autoEjectCrateLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_GET_CRATE) {
		if (autoGetCrateLoop()) {
			currentState = NORMAL;
		}
	}
}

//Move elevator to specified height in inches from the ground
void commandWithAutomation::moveElevatorToHeight(float heightIN){

}

//Set Elevator to the lowest position, open magazine once it gets to the bottom
void commandWithAutomation::resetElevatorAndMagazine(){

}

//Load a crate once it is in the arms/rollers
void commandWithAutomation::autoLoadCrate(){

}

//Eject the stack
void commandWithAutomation::autoEjectCrate(){

}

//Grab a crate and load it
void commandWithAutomation::autoGetCrate(){

}

bool commandWithAutomation::moveElevatorToHeightLoop(){
	return false;
}
bool commandWithAutomation::resetElevatorAndMagazineLoop(){
	return false;
}
bool commandWithAutomation::autoLoadCrateLoop(){
	return false;
}
bool commandWithAutomation::autoEjectCrateLoop(){
	return false;
}
bool commandWithAutomation::autoGetCrateLoop(){
	return false;
}
