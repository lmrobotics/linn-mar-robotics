#include "Commands/commandWithAutomation.h"

commandWithAutomation::commandWithAutomation() : drivePID(1, .05, .05, driveEncoder, PIDPlacebo)
{
	Requires(drive);
	Requires(elevator);
	currentElevatorState=ELEVATOR_NORMAL;
	currentDriveState=DRIVE_NORMAL;
	targetElevatorHeight=0;
	elevatorStep=1;
	driveStep=1;
	elevatorTimer=std::clock();
	driveTimer=std::clock();
	targetAngle=0.0;
	targetDistance=0.0;
	initialAngle=0.0;
	initialDistance=0.0;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

void commandWithAutomation::runCurrentLoop(){
	if (currentElevatorState == ELEVATOR_NORMAL) {
		normalElevatorOperationLoop();
	}
	else if (currentElevatorState == MOVE_ELEVATOR_TO_HEIGHT) {
		if (moveElevatorToHeightLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}
	else if (currentElevatorState == RESET_ELEVATOR) {
		if (resetElevatorLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}
	else if (currentElevatorState == AUTO_LOAD_TOTE) {
		if (autoLoadToteLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}
	else if (currentElevatorState == AUTO_EJECT_TOTE) {
		if (autoEjectToteLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}
	else if (currentElevatorState == AUTO_GET_TOTE) {
		if (autoGetToteLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}
	else if (currentElevatorState == AUTO_GRAB_TOTE) {
		if (autoGrabToteLoop()) {
			normalElevatorOperation();
			currentElevatorState = ELEVATOR_NORMAL;
		}
	}

	if (currentDriveState == DRIVE_NORMAL){
		normalDriveOperationLoop();
	}
	else if (currentDriveState == GO_TO_LOCATION){
		if (goToLocationLoop()){
			normalDriveOperation();
			currentDriveState=DRIVE_NORMAL;
		}
	}
}

//Move elevator to specified height in inches from the ground
void commandWithAutomation::moveElevatorToHeight(float heightIN){
	targetElevatorHeight=heightIN;
	if(elevatorEncoder->GetDistance() > heightIN+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < heightIN-.25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}
	currentElevatorState=MOVE_ELEVATOR_TO_HEIGHT;
}

//Set Elevator to the lowest position, open magazine once it gets to the bottom
void commandWithAutomation::resetElevator(){
	targetElevatorHeight=toteLowestHeight;
	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight - .25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}
	currentElevatorState=RESET_ELEVATOR;
	elevatorStep=1;
}
//Load a Tote once it is in the arms/rollers
void commandWithAutomation::autoLoadTote(){
	targetElevatorHeight=toteLowestHeight;
	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight - .25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}

	currentElevatorState=AUTO_LOAD_TOTE;
	elevatorStep=1;

}
//Eject the stack
void commandWithAutomation::autoEjectTote(){
	targetElevatorHeight = toteLowestHeight;
	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight - .25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}
	currentElevatorState=AUTO_EJECT_TOTE;
	elevatorStep=1;
}

//Grab a Tote and load it
void commandWithAutomation::autoGetTote(){
	targetElevatorHeight=toteLowestHeight;
	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight - .25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}

	currentElevatorState=AUTO_GET_TOTE;
	elevatorStep=1;
}

void commandWithAutomation::autoGrabTote(){
	targetElevatorHeight=toteLowestHeight;
	currentElevatorState=AUTO_GRAB_TOTE;
	elevatorStep=1;
}

//Go to a location specified by the angle and distance. Positive angle means right.
void commandWithAutomation::goToLocation(double angle, double distance){
	targetAngle=angle;
	targetDistance=distance;
	initialAngle=nav6->GetYaw();
	drivePID.Reset();
	if (angle>0){
		if (angle>45){
			drive->Move(-1,1);
		}
		else {
			drive->Move(-.3,.3);
		}
	}
	else if (angle<0){
		if (angle<-45){
			drive->Move(1,-1);
		}
		else {
			drive->Move(.3,-.3);
		}
	}
	else {
		drive->Move(0,0);
	}
	currentDriveState=GO_TO_LOCATION;
	driveStep=1;
}

bool commandWithAutomation::moveElevatorToHeightLoop(){

	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.15 ){
		if (abs(elevatorEncoder->GetDistance() - targetElevatorHeight)>1){
			elevator->setElevator(-1);
		}
		else{
			elevator->setElevator(-.6);
		}
		return false;
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight-.15 ){
		if (abs(elevatorEncoder->GetDistance() - targetElevatorHeight)>1){
			elevator->setElevator(1);
		}
		else{
			elevator->setElevator(.6);
		}
		return false;
	}
	else{
		elevator-> setElevator(0);
		return true;
	}
	return false;
}

bool commandWithAutomation::resetElevatorLoop(){
	targetElevatorHeight=toteLowestHeight;
	if(!elevator -> isArmsOpen()){
		elevator -> openArms();
	}
	if (moveElevatorToHeightLoop()){
		if (!elevator -> isMagOpen()){
			elevator -> openMag();
		}
		return true;
	}
	return false;
}

bool commandWithAutomation::autoLoadToteLoop(){
	switch (elevatorStep){
	case 1:
		targetElevatorHeight=toteLowestHeight;
		if(!elevator -> isArmsOpen()){
			elevator -> openArms();
		}
		if(moveElevatorToHeightLoop()){
			elevatorStep=2;
		}
		break;
	case 2:
		if (elevator->isArmsOpen()){
			elevator->openArms();
		}
		elevatorStep=3;
		break;
	case 3:
		targetElevatorHeight=toteHoldHeight;
		if(moveElevatorToHeightLoop()){
			return true;
		}
		break;
	}
	return false;

}
bool commandWithAutomation::autoEjectToteLoop(){
	switch (elevatorStep){
	case 1:
		if(!elevator -> isArmsOpen()){
			elevator -> openArms();
		}
		elevatorStep=2;
		break;
	case 2:
		targetElevatorHeight=toteLowestHeight;
		if(moveElevatorToHeightLoop()){
			elevatorStep=3;
		}
		break;
	case 3:
		if(!elevator -> isMagOpen()){
			elevator -> openMag();
		}
		return true;
		break;
	}
	return false;

}

bool commandWithAutomation::autoGetToteLoop(){
	switch (elevatorStep){
	case 1:
		targetElevatorHeight=toteHoldHeight;
		if (moveElevatorToHeightLoop()){
			elevatorStep=2;
		}
		break;
	case 2:
		if(elevator -> isArmsOpen()==true){
			elevator -> closeArms();
		}
		elevatorTimer=std::clock();
		elevatorStep = 3;
		break;
	case 3:
		elevator -> setRollers(-.5);
		if((3.0*(double)(std::clock() - elevatorTimer) / (double) CLOCKS_PER_SEC)>.3){
			elevator -> setRollers(0);
			elevatorStep = 4;
		}
		break;
	case 4:
		if (elevator->isMagOpen()){
			elevator->closeMag();
		}
		targetElevatorHeight=toteLowestHeight;
		if(moveElevatorToHeightLoop()){
			elevatorStep=5;
		}
		break;
	case 5:
		if (elevator->isArmsOpen()){
			elevator->openArms();
		}
		elevatorStep=6;
		break;
	case 6:
		targetElevatorHeight=toteHoldHeight;
		if(moveElevatorToHeightLoop()){
			return true;
		}
		break;
	}
	return false;
}
bool commandWithAutomation::autoGrabToteLoop(){
	switch (elevatorStep){
	case 1:
		if(elevator -> isArmsOpen()==true){
			elevator -> closeArms();
		}
		elevatorTimer=std::clock();
		elevatorStep = 2;
		break;
	case 2:
		elevator -> setRollers(-.5);
		if((3.0*(double)(std::clock() - elevatorTimer) / (double) CLOCKS_PER_SEC)>1){
			elevator -> setRollers(0);
			return true;
		}
		break;
	}
	return false;
}

bool commandWithAutomation::goToLocationLoop(){
	switch (driveStep){
	case 1:
		if (targetAngle>0){
			if (targetAngle-nav6->GetYaw()<45){
				drive->Move(-1,1);
			}
			else {
				drive->Move(-.3,.3);
			}
		}
		else if (targetAngle<0){
			if (targetAngle-nav6->GetYaw()>-45){
				drive->Move(1,-1);
			}
			else {
				drive->Move(.3,-.3);
			}
		}
		if (abs(targetAngle-nav6->GetYaw())<8){
			drive->Move(0,0);
			driveStep=2;
		}
		break;
	case 2:
		initialDistance=driveEncoder->GetDistance();
		drive->Move(0,0);
		drivePID.Enable();
		drivePID.Reset();
		drivePID.SetSetpoint(initialAngle+targetAngle);
		driveStep=3;
		break;
	case 3:
		drive->MoveNoAccel(.75-drivePID.Get(),.75+drivePID.Get());
		if (targetDistance-driveEncoder->GetDistance()<30){
			drive->Move(0,0);
		}
		if (targetDistance-driveEncoder->GetDistance()<5){
			drive->stopdrive();
			return true;
		}
	}
	return false;
}
