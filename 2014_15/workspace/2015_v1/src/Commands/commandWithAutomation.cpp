#include "Commands/commandWithAutomation.h"

commandWithAutomation::commandWithAutomation()
{
	Requires(drive);
	Requires(elevator);
	currentState=NORMAL;
	targetElevatorHeight=0;
	step=0;
	timer=std::clock();
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
	else if (currentState == AUTO_LOAD_TOTE) {
		if (autoLoadToteLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_EJECT_TOTE) {
		if (autoEjectToteLoop()) {
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_GET_TOTE) {
		if (autoGetToteLoop()) {
			currentState = NORMAL;
		}
	}
}

//Move elevator to specified height in inches from the ground
void commandWithAutomation::moveElevatorToHeight(float heightIN){
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > heightIN+.5){
		elevator-> winchMotor.Set(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < heightIN - .5){
		elevator-> winchMotor.Set(.5);
	}
	else{
		elevator-> winchMotor.Set(0);
	}
	targetElevatorHeight=heightIN;
	currentState=MOVE_ELEVATOR_TO_HEIGHT;
}

//Set Elevator to the lowest position, open magazine once it gets to the bottom
void commandWithAutomation::resetElevatorAndMagazine(){
	targetElevatorHeight=lowestElevatorHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> winchMotor.Set(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> winchMotor.Set(.5);
	}
	else{
		elevator-> winchMotor.Set(0);
	}
	currentState=RESET_ELEVATOR_AND_MAGAZINE;
	step=1;
	/*
	step=1;
	if(elevatorEncoder->Get()>lowestElevatorHeight){
		elevator-> winchMotor.Set(-.5);
	}
	if(elevator->isMagazineOpen()==false){
		elevator-> magShifter.Set(DoubleSolenoid::Value::kForward);
	}
	*/
}
//Load a Tote once it is in the arms/rollers
void commandWithAutomation::autoLoadTote(){
	targetElevatorHeight=toteLoadHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> winchMotor.Set(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> winchMotor.Set(.5);
	}
	else{
		elevator-> winchMotor.Set(0);
	}

	currentState=AUTO_LOAD_TOTE;
	step=1;

	/*
	elevator->armMotorR.Set(averageRollerSpeed);
	elevator->armMotorL.Set(-averageRollerSpeed);
	elevator->conveyorMotor.Set(averageConveyorSpeed);
	elevatorEncoder->winchMotor.Set(toteLoadHeight);
	*/
}
//Eject the stack
void commandWithAutomation::autoEjectTote(){
	targetElevatorHeight = toteLoadHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> winchMotor.Set(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> winchMotor.Set(.5);
	}
	else{
		elevator-> winchMotor.Set(0);
	}
	currentState=AUTO_EJECT_TOTE;
	step=1;

	/*
	elevator->conveyorMotor.Set(-averageConveyorSpeed);
	elevator->armShifter.Set(DoubleSolenoid::Value::kReverse);
	elevator->armMotorR.Set(-averageRollerSpeed);
	elevator->armMotorL.Set(averageRollerSpeed);
	*/
}

//Grab a Tote and load it
void commandWithAutomation::autoGetTote(){
	targetElevatorHeight=lowestElevatorHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> winchMotor.Set(-.5);
	}
	else{
		elevator-> winchMotor.Set(0);
	}

	currentState=AUTO_GET_TOTE;
	step=1;
}

//Go to a location specified by the angle and distance. Positive angle means right.
void commandWithAutomation::goToLocation(double angle, double distance){

}

bool commandWithAutomation::moveElevatorToHeightLoop(){

	if(elevatorEncoder->Get() > targetElevatorHeight +.5 ){
		elevator-> winchMotor.Set(-.5);
		return false;
	}
	else if(elevatorEncoder->Get() < targetElevatorHeight -.5 ){
		elevator-> winchMotor.Set(.5);
		return false;
	}
	else{
		elevator-> winchMotor.Set(0);
		return true;
	}
	return false;
}

bool commandWithAutomation::resetElevatorAndMagazineLoop(){
	switch (step){
	case 1:
		targetElevatorHeight=lowestElevatorHeight;
		if (moveElevatorToHeightLoop()){
			step=2;
		}
		break;
	case 2:
		if(elevator -> isMagazineOpen()==false){
			elevator -> openMagazine();
		}
		if(elevator -> isArmsOpen()==false){
			elevator -> openArms();
		}
		return true;
		break;
	}
	return false;
	/*
	if(elevatorEncoder->Get() > lowestElevatorHeight){
		return false;
	}
	if(elevator->isMagazineOpen()==false){
		return false;
	}
	if((elevatorEncoder->Get() == lowestElevatorHeight) && (elevator->isMagazineOpen()==true)){
		return true;
	}
	return false;
	*/
}

bool commandWithAutomation::autoLoadToteLoop(){
	switch (step){
	case 1:
		targetElevatorHeight=toteLoadHeight;
		if(moveElevatorToHeightLoop()){
			step=2;
		}
		break;
	case 2:
		elevator -> setRollers(-.5);
		elevator -> setConveyor(-.5);
		timer=std::clock();
		step=3;
		break;
	case 3:
		elevator -> setRollers(-.5);
		elevator -> setConveyor(-.5);
		if((3.0*(double)(std::clock() - timer) / (double) CLOCKS_PER_SEC)>1){
			elevator -> setRollers(0);
			elevator -> setConveyor(0);
			return true;
		}
		break;
	}
	return false;

	/*
	if((elevator->winchMotor.Get() == (toteLoadHeight)) && (elevator->armMotorR.Get() == (averageRollerSpeed)) && (elevator->armMotorL.Get() == (-averageRollerSpeed))){
	return true;
	}
	else
		return false;
		*/
}
bool commandWithAutomation::autoEjectToteLoop(){
	switch (step){
	case 1:
		targetElevatorHeight=toteLoadHeight;
		if(moveElevatorToHeightLoop()){
			step=2;
		}
		break;
	case 2:
		if(elevator -> isMagazineOpen()==false){
			elevator -> openMagazine();
		}
		step=3;
		break;
	case 3:
		if(elevator -> isArmsOpen()==false){
			elevator -> openArms();
		}
		timer=std::clock();
		step=4;
		break;
	case 4:
		elevator -> setConveyor(.5);
		elevator -> setRollers(.5);
		if ((3.0*(double)(std::clock() - timer) / (double) CLOCKS_PER_SEC) > .3){
			step = 5;
		}
		break;
	case 5:
		if(elevator -> isArmsOpen()==true){
			elevator -> closeArms();
		}
		elevator -> setConveyor(.5);
		elevator -> setRollers(.5);
		if ((3.0*(double)(std::clock() - timer) / (double) CLOCKS_PER_SEC) > 1){
			step = 6;
			elevator -> setConveyor(0);
			elevator -> setRollers(0);
		}
		break;
	case 6:
		targetElevatorHeight=lowestElevatorHeight;
		if(elevatorEncoder->Get()>targetElevatorHeight){
			elevator -> winchMotor.Set(-.5);
		}
		else{
			elevator -> winchMotor.Set(.5);
		}
		step=7;
		break;
	case 7:
		if(elevator->isArmsOpen()==false){
			elevator -> openArms();
		}
		return true;
		break;
	}
	return false;

	/*
	if((elevator->conveyorMotor.Get() == (averageConveyorSpeed)) && (elevator->armShifter.Get() == (DoubleSolenoid::Value::kReverse)) && (elevator->armMotorR.Get()(-averageRollerSpeed)) && (elevator->armMotorL.Get()(averageRollerSpeed))){
	return true;
}
	else
		return false;
		*/

}

bool commandWithAutomation::autoGetToteLoop(){
	switch (step){
	case 1:
		targetElevatorHeight=lowestElevatorHeight;
		if (moveElevatorToHeightLoop()){
			step=2;
		}
		break;
	case 2:
		if(elevator -> isMagazineOpen()==false){
			elevator -> openMagazine();
		}
		if(elevator -> isArmsOpen()==true){
			elevator -> closeArms();
		}
		std::clock();
		step = 3;
		break;

	case 3:
		elevator -> setRollers(-.5);
		if((3.0*(double)(std::clock() - timer) / (double) CLOCKS_PER_SEC)>.3){
			elevator -> setRollers(0);
			step = 4;
		}
		break;
	case 4:
		targetElevatorHeight=toteLoadHeight;
			if (moveElevatorToHeightLoop()){
				step=5;
			}
		break;
	case 5:
		elevator -> setRollers(-.5);
		elevator -> setConveyor(-.5);
		timer=std::clock();
		step=6;
		break;
	case 6:
		elevator -> setRollers(-.5);
		elevator -> setConveyor(-.5);
		if((3.0*(double)(std::clock() - timer) / (double) CLOCKS_PER_SEC)>1){
			elevator -> setRollers(0);
			elevator -> setConveyor(0);
			return true;
		}
		break;
	}
	return false;
}
/*
bool commandWithAutomation::goToLocationLoop(){

}*/
