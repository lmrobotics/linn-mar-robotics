#include "Commands/commandWithAutomation.h"

commandWithAutomation::commandWithAutomation() : drivePID(1, .05, .05, driveEncoder, PIDPlacebo)
{
	Requires(drive);
	Requires(elevator);
	currentState=NORMAL;
	targetElevatorHeight=0;
	step=0;
	timer=std::clock();
	targetAngle=0.0;
	targetDistance=0.0;
	initialAngle=0.0;
	initialDistance=0.0;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

void commandWithAutomation::runCurrentLoop(){
	if (currentState == NORMAL) {
		normalOperationLoop();
	}
	else if (currentState == MOVE_ELEVATOR_TO_HEIGHT) {
		if (moveElevatorToHeightLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == RESET_ELEVATOR_AND_MAGAZINE) {
		if (resetElevatorAndMagazineLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_LOAD_TOTE) {
		if (autoLoadToteLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_EJECT_TOTE) {
		if (autoEjectToteLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_GET_TOTE) {
		if (autoGetToteLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == AUTO_GRAB_TOTE) {
		if (autoGrabToteLoop()) {
			normalOperation();
			currentState = NORMAL;
		}
	}
	else if (currentState == GO_TO_LOCATION){
		if (goToLocationLoop()){
			normalOperation();
			currentState=NORMAL;
		}
	}
}

//Move elevator to specified height in inches from the ground
void commandWithAutomation::moveElevatorToHeight(float heightIN){
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > heightIN+.5){
		elevator-> setElevator(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < heightIN - .5){
		elevator-> setElevator(.5);
	}
	else{
		elevator-> setElevator(0);
	}
	targetElevatorHeight=heightIN;
	currentState=MOVE_ELEVATOR_TO_HEIGHT;
}

//Set Elevator to the lowest position, open magazine once it gets to the bottom
void commandWithAutomation::resetElevatorAndMagazine(){
	targetElevatorHeight=lowestElevatorHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> setElevator(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> setElevator(.5);
	}
	else{
		elevator-> setElevator(0);
	}
	currentState=RESET_ELEVATOR_AND_MAGAZINE;
	step=1;
}
//Load a Tote once it is in the arms/rollers
void commandWithAutomation::autoLoadTote(){
	targetElevatorHeight=toteLoadHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> setElevator(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> setElevator(.5);
	}
	else{
		elevator-> setElevator(0);
	}

	currentState=AUTO_LOAD_TOTE;
	step=1;

}
//Eject the stack
void commandWithAutomation::autoEjectTote(){
	targetElevatorHeight = toteLoadHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> setElevator(-.5);
	}
	else if(elevatorEncoder->Get()*elevatorEncoderCountToInches < targetElevatorHeight - .5){
		elevator-> setElevator(.5);
	}
	else{
		elevator-> setElevator(0);
	}
	currentState=AUTO_EJECT_TOTE;
	step=1;
}

//Grab a Tote and load it
void commandWithAutomation::autoGetTote(){
	targetElevatorHeight=lowestElevatorHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> setElevator(-.5);
	}
	else{
		elevator-> setElevator(0);
	}

	currentState=AUTO_GET_TOTE;
	step=1;
}

void commandWithAutomation::autoGrabTote(){
	targetElevatorHeight=lowestElevatorHeight;
	if(elevatorEncoder->Get()*elevatorEncoderCountToInches > targetElevatorHeight+.5){
		elevator-> setElevator(-.5);
	}
	else{
		elevator-> setElevator(0);
	}
	currentState=AUTO_GRAB_TOTE;
	step=1;
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
	currentState=GO_TO_LOCATION;
	step=1;
}

bool commandWithAutomation::moveElevatorToHeightLoop(){

	if(elevatorEncoder->Get() > targetElevatorHeight +.5 ){
		elevator->setElevator(-.5);
		return false;
	}
	else if(elevatorEncoder->Get() < targetElevatorHeight -.5 ){
		elevator->setElevator(.5);
		return false;
	}
	else{
		elevator-> setElevator(0);
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
			elevator -> setElevator(-.5);
		}
		else{
			elevator -> setElevator(.5);
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

bool commandWithAutomation::autoGrabToteLoop(){
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
			return true;
		}
		break;
	}
	return false;
}

bool commandWithAutomation::goToLocationLoop(){
	switch (step){
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
			step=2;
		}
		break;
	case 2:
		initialDistance=driveEncoder->GetDistance();
		drive->Move(0,0);
		drivePID.Enable();
		drivePID.Reset();
		drivePID.SetSetpoint(initialAngle+targetAngle);
		step=3;
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
