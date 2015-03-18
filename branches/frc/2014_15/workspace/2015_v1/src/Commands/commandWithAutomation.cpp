#include "Commands/commandWithAutomation.h"

commandWithAutomation::commandWithAutomation() :
drivePID(.02, .005, 0, nav6),
i(0)
{
	limitClicked=false;
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
	else if (currentElevatorState == AUTO_LV2_LOAD_TOTE) {
		if (autoLv2LoadToteLoop()) {
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
	else if (currentDriveState == FAST_GO_TO_LOCATION){
		if (fastGoToLocationLoop()){
			normalDriveOperation();
			currentDriveState=DRIVE_NORMAL;
		}
	}
	else if (currentDriveState == ADVANCED_TURN){
		if (advancedTurnLoop()){
			normalDriveOperation();
			currentDriveState=DRIVE_NORMAL;
		}
	}
	else if (currentDriveState == ADVANCED_MOVE){
		if (advancedMoveLoop()){
			normalDriveOperation();
			currentDriveState=DRIVE_NORMAL;
		}
	}

	if (elevatorLimit->Get()==0){
		if (!limitClicked){
			elevatorEncoder->Reset();
			limitClicked=true;
		}
	}
	else {
		limitClicked=false;
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
	i=0;
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
//Load a Tote from the second level (chute level)
void commandWithAutomation::autoLv2LoadTote(){
	targetElevatorHeight=toteLowestHeight;
	i=0;
	if(elevatorEncoder->GetDistance() > targetElevatorHeight+.25){
		elevator-> setElevator(-1);
	}
	else if(elevatorEncoder->GetDistance() < targetElevatorHeight - .25){
		elevator-> setElevator(1);
	}
	else{
		elevator-> setElevator(0);
	}

	currentElevatorState=AUTO_LV2_LOAD_TOTE;
	elevatorStep=1;

}

//Eject the stack
void commandWithAutomation::autoEjectTote(){
	elevator->openArms();
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
	nav6->ZeroYaw();
	targetAngle=angle;
	targetDistance=distance;
	initialAngle=nav6->GetYaw();
	drivePID.reset();
	if (angle>0){
		if (angle>45){
			drive->Move(1,-1);
		}
		else {
			drive->Move(.3,-.3);
		}
	}
	else if (angle<0){
		if (angle<-45){
			drive->Move(-1,1);
		}
		else {
			drive->Move(-.3,.3);
		}
	}
	else {
		drive->Move(0,0);
	}
	currentDriveState=GO_TO_LOCATION;
	driveStep=1;
	drive->setAccel(.1);
}
void commandWithAutomation::fastGoToLocation(double angle, double distance){
	nav6->ZeroYaw();
	targetAngle=angle;
	targetDistance=distance;
	initialAngle=nav6->GetYaw();
	drivePID.reset();
	if (angle>0){
		drive->Move(1,-1);
	}
	else if (angle<0){
		drive->Move(-1,1);
	}
	else {
		drive->Move(0,0);
	}
	currentDriveState=FAST_GO_TO_LOCATION;
	driveStep=1;
	drive->setAccel(2);
}

void commandWithAutomation::advancedTurn(double L, double R, double yaw){
	nav6->ZeroYaw();
	targetAngle=yaw;
	initialAngle=nav6->GetYaw();
	drive->Move(L,R);
	currentDriveState=ADVANCED_TURN;
	driveStep=1;
}

void commandWithAutomation::advancedMove(double L, double R, double distance){
	targetDistance=distance;
	initialDistance=driveEncoder->GetDistance();
	drive->Move(L,R);
	currentDriveState=ADVANCED_MOVE;
	driveStep=1;
}

bool commandWithAutomation::moveElevatorToHeightLoop(){

	if((elevatorEncoder->GetDistance() < .30 || elevatorLimit->Get()==0) && targetElevatorHeight<.30){
		elevator->setElevator(0);
		return true;
	}
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
		if (!elevator -> isMagOpen()){
			elevator -> closeMag();
			i++;
		}
		if (!elevator->isArmsOpen()){
			elevator->openArms();
			i++;
		}
		i++;
		if (i<=1 || i>20){
			elevatorStep=2;
		}
		break;
	case 2:
		targetElevatorHeight=toteLowestHeight;
		if(moveElevatorToHeightLoop()){
			elevatorStep=3;
		}
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
bool commandWithAutomation::autoLv2LoadToteLoop(){
	switch (elevatorStep){
	case 1:
		if (elevator -> isMagOpen()){
			elevator -> closeMag();
			i++;
		}
		i++;
		if (i<=1 || i>20){
			elevatorStep=2;
		}
		break;
	case 2:
		if (elevator->isArmsOpen()){
			elevator->closeArms();
		}
		targetElevatorHeight=toteLowestHeight;
		if(moveElevatorToHeightLoop()){
			elevatorStep=3;
		}
		break;
	case 3:
		if (!elevator->isArmsOpen()){
			elevator->openArms();
		}
		targetElevatorHeight=toteLv2HoldHeight;
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
		elevator -> closeArms();
		elevator->closeMag();
		elevatorTimer=std::clock();
		elevatorStep = 2;
		break;
	case 2:
		elevator -> setRollers(-1);
		if((3.0*(double)(std::clock() - elevatorTimer) / (double) CLOCKS_PER_SEC)>.3){
			elevator -> setRollers(0);
			elevatorStep = 3;
		}
		break;
	case 3:
		if (elevator->isMagOpen()){
			elevator->closeMag();
		}
		if(!elevator->isArmsOpen()){
			elevator->openArms();
		}
		targetElevatorHeight=toteLowestHeight;
		if(moveElevatorToHeightLoop()){
			elevatorStep=4;
		}
		break;
	case 4:
		if (elevator->isArmsOpen()){
			elevator->openArms();
		}
		elevatorStep=5;
		break;
	case 5:
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
		elevator -> closeArms();
		elevatorTimer=std::clock();
		elevatorStep = 2;
		break;
	case 2:
		elevator -> setRollers(-1);
		if((3.0*(double)(std::clock() - elevatorTimer) / (double) CLOCKS_PER_SEC)>.3){
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
			if (targetAngle-(nav6->GetYaw()-initialAngle)>30){
				drive->Move(.5,-.5);
			}
			else {
				drive->Move(.25,-.25);
			}
		}
		else if (targetAngle<0){
			if (targetAngle-(nav6->GetYaw()-initialAngle)<-30){
				drive->Move(-.5,.5);
			}
			else {
				drive->Move(-.25,.25);
			}
		}
		if (abs(targetAngle-(nav6->GetYaw()-initialAngle))<5){
			drive->stopdrive();
			driveStep=2;
		}
		break;
	case 2:
		drive->setAccel(2);
		initialDistance=driveEncoder->GetDistance();
		drive->stopdrive();
		drivePID.enable();
		drivePID.reset();
		drivePID.setTarget(initialAngle+targetAngle);
		driveStep=3;
		break;
	case 3:
		if (targetDistance>0){
			drive->MoveNoAccel(.5+drivePID.get(),.5-drivePID.get());
			dash->PutNumber("drivePID", drivePID.get());
			if (targetDistance-(driveEncoder->GetDistance()-initialDistance)<5){
				drive->stopdrive();
				drivePID.disable();
				return true;
			}
		}
		else{
			drive->MoveNoAccel(-.5+drivePID.get(),-.5-drivePID.get());
			dash->PutNumber("drivePID", drivePID.get());
			if (targetDistance-(driveEncoder->GetDistance()-initialDistance)>-5){
				drive->stopdrive();
				drivePID.disable();
				return true;
			}
		}
	}
	return false;
}

bool commandWithAutomation::fastGoToLocationLoop(){
	switch (driveStep){
	case 1:
		if (targetAngle>0){
			if (targetAngle-(nav6->GetYaw()-initialAngle)>30){
				drive->Move(1,-1);
			}
			else {
				drive->Move(.35,-.35);
			}
		}
		else if (targetAngle<0){
			if (targetAngle-(nav6->GetYaw()-initialAngle)<-30){
				drive->Move(-1,1);
			}
			else {
				drive->Move(-.35,.35);
			}
		}
		if (abs(targetAngle-(nav6->GetYaw()-initialAngle))<5){
			drive->stopdrive();
			driveStep=2;
		}
		break;
	case 2:
		drive->setAccel(2);
		initialDistance=driveEncoder->GetDistance();
		drive->stopdrive();
		drivePID.enable();
		drivePID.reset();
		drivePID.setTarget(initialAngle+targetAngle);
		driveStep=3;
		break;
	case 3:
		if (targetDistance>0){
			drive->MoveNoAccel(.8+drivePID.get(),.8-drivePID.get());
			dash->PutNumber("drivePID", drivePID.get());
			if (targetDistance-(driveEncoder->GetDistance()-initialDistance)<5){
				drive->stopdrive();
				drivePID.disable();
				return true;
			}
		}
		else{
			drive->MoveNoAccel(-.8+drivePID.get(),-.8-drivePID.get());
			dash->PutNumber("drivePID", drivePID.get());
			if (targetDistance-(driveEncoder->GetDistance()-initialDistance)>-5){
				drive->stopdrive();
				drivePID.disable();
				return true;
			}
		}
	}
	return false;
}

bool commandWithAutomation::advancedMoveLoop(){
	if (targetDistance>0){
		return ((targetDistance-(driveEncoder->GetDistance()-initialDistance))<5);
	}
	else {
		return ((targetDistance-(driveEncoder->GetDistance()-initialDistance))>-5);
	}
}

bool commandWithAutomation::advancedTurnLoop(){
	if (targetAngle>0){
		return ((targetAngle-(nav6->GetYaw()-initialAngle))<5);
	}
	else {
		return ((targetAngle-(nav6->GetYaw()-initialAngle))>-5);
	}
}
