#include <Commands/telControl.h>


telControl::telControl()
{
	Requires(drive);
	Requires(elevator);

	currentElevatorState=ELEVATOR_NORMAL;
	currentDriveState=DRIVE_NORMAL;
	limitClicked=false;
	targetElevatorHeight=0;
	elevatorStep=1;
	driveStep=1;
	elevatorTimer=std::clock();
	driveTimer=std::clock();
	targetAngle=0.0;
	targetDistance=0.0;
	initialAngle=0.0;
	initialDistance=0.0;
	elevatorOverride=false;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telControl::Initialize() {
	elevator->openMag();
	elevator->openArms();
	drivePID.enable();
	drivePID.setTarget(0);
}

// Called repeatedly when this Command is scheduled to run
void telControl::Execute() {
	runCurrentLoop();
	if (oi->xbox1_startTapped() || oi->board_5Tapped()){
		normalDriveOperation();
		normalElevatorOperation();
	}
	if (oi->xbox1_start() || oi->board_5()){
		elevatorOverride=true;
	}
	else {
		elevatorOverride=false;
	}
	if (currentElevatorState==AUTO_LOAD_TOTE || currentElevatorState==AUTO_LV2_LOAD_TOTE){
		if (oi->xbox2_bTapped()){
			elevator->shiftArms();
		}
		if (oi->xbox2_xTapped()){
			elevator->shiftMag();
		}
		if (oi->board_bigRedTapped()){
			elevator->shiftArms();
		}
		if (oi->board_lilGreenTapped()){
			elevator->shiftArms();
			elevator->shiftMag();
		}
		if (oi->xbox1_lT()){
			elevator->setRollers(-1);
		}
		else if (oi->xbox1_rT()){
			elevator->setRollers(1);
		}
		if (oi->board_in()){
			elevator->setRollers(-1);
		}
		else if (oi->board_out()){
			elevator->setRollers(1);
		}
		else {
			if (oi->xbox2_y2() > deadband || oi->xbox2_y2() < -deadband) {
				elevator->setRRollers(-oi->xbox2_y2());
			}
			else {
				elevator->setRRollers(0);
			}
			if (oi->xbox2_y1() > deadband || oi->xbox2_y1() < -deadband) {
				elevator->setLRollers(-oi->xbox2_y1());
			}
			else {
				elevator->setLRollers(0);
			}
		}
	}
	dash->PutNumber("PID", drivePID.get());
	dash->PutNumber("PID IsEnabled", drivePID.isEnabled());
	dash->PutNumber("PID target", drivePID.getTarget());


	//||   or
	//&&   and
	//!    not
	//==   equals
	//!=   Not Equals

	// :)  Happy

}

// Make this return true when this Command no longer needs to run execute()
bool telControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void telControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void telControl::Interrupted() {

}

void telControl::normalElevatorOperation(){
	currentElevatorState=ELEVATOR_NORMAL;
}

void telControl::normalDriveOperation(){
	currentDriveState=DRIVE_NORMAL;
}

void telControl::normalDriveOperationLoop(){
	drive->TeleDrive(oi->xbox1_y1(), oi->xbox1_x2());
	if (oi->xbox1_rBTapped()) {
		drive->shift();
	}
	if (oi->xbox1_lB()){
		drive->stopdrive();
	}
	if (oi->xbox1_yTapped()){
		goToLocation(45,48);
	}
	//a button flips between normal drive and controlled acceleration
	//MoveNormal = normal drive and MoveCurve = limited acceleration
	if (oi->xbox1_aTapped()){
		if (drive->getAccel()>=.5){
			drive->setAccel(.02);
		}
		else {
			drive->setAccel(2);
		}
	}
}

void telControl::normalElevatorOperationLoop(){
	if (oi->xbox2_bTapped()){
		elevator->shiftArms();
	}
	if (oi->xbox2_xTapped()){
		elevator->shiftMag();
	}
	if (oi->board_bigRedTapped()){
		elevator->shiftArms();
	}
	if (oi->board_lilGreenTapped()){
		elevator->shiftMag();
	}
	if (oi->xbox1_lT()){
		elevator->setRollers(-1);
	}
	else if (oi->xbox1_rT()){
		elevator->setRollers(1);
	}
	if (oi->board_in()){
		elevator->setRollers(-1);
	}
	else if (oi->board_out()){
		elevator->setRollers(1);
	}
	else {
		if (oi->xbox2_y2() > deadband || oi->xbox2_y2() < -deadband) {
			elevator->setRRollers(-oi->xbox2_y2());
		}
		else {
			elevator->setRRollers(0);
		}
		if (oi->xbox2_y1() > deadband || oi->xbox2_y1() < -deadband) {
			elevator->setLRollers(-oi->xbox2_y1());
		}
		else {
			elevator->setLRollers(0);
		}
	}
	if (oi->board_up() && (elevatorEncoder->GetDistance()<46.5 || elevatorOverride)) {
		elevator->setElevator(1);
	}
	else if (oi->board_down() && (elevatorEncoder->GetDistance()>0 || elevatorOverride) && elevatorLimit->Get()==1) {
		elevator->setElevator(-.8);
	}
	else if (oi->xbox2_lB() && (elevatorEncoder->GetDistance()<46.5 || elevatorOverride)) {
		elevator->setElevator(1);
	}
	else if (oi->xbox2_rB() && (elevatorEncoder->GetDistance()>0 || elevatorOverride) && elevatorLimit->Get()==1) {
		elevator->setElevator(-.8);
	}
	else {
		elevator->setElevator(0);
	}
	if (oi->board_hiLoSwitchTapped()){
		elevator->highGearElevator();
	}
	if (oi->board_hiLoSwitchUnTapped()){
		elevator->lowGearElevator();
	}
	if (oi->xbox2_aTapped()) {
		elevator->shiftElevatorGear();
	}
	if (oi->xbox2_xTapped()){
		elevator->shiftMag();
	}
	if (oi->xbox2_selectTapped()){
		autoGrabTote();
	}
	else if (oi->xbox2_startTapped()){
		autoLoadTote();
	}
	if (oi->xbox1_selectTapped()){
		elevatorEncoder->Reset();
	}
	if (oi->board_1Tapped()){
		autoGetTote();
	}
	if (oi->board_2Tapped()){
		autoLv2LoadTote();
	}
	if (oi->board_3Tapped()){
		moveElevatorToHeight(toteLv3Height);
	}
	if (oi->board_4Tapped()){
		moveElevatorToHeight(toteMaxHeight);
	}
}
