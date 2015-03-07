#include <Commands/telControl.h>


telControl::telControl()
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
	elevatorOverride=false;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telControl::Initialize() {
	dash->PutString("Does It Work?", "YES");
}

// Called repeatedly when this Command is scheduled to run
void telControl::Execute() {
	runCurrentLoop();
	if (oi->xbox1_startTapped()){
		elevatorOverride=!elevatorOverride;
		normalDriveOperation();
		normalElevatorOperation();
	}
	if (currentElevatorState==AUTO_LOAD_TOTE){
		if (oi->xbox2_bTapped()){
			elevator->shiftArms();
		}
		if (oi->xbox2_xTapped()){
			elevator->shiftMag();
		}
		if (oi->xbox1_lT()){
			elevator->setRollers(-.5);
		}
		else if (oi->xbox1_rT()){
			elevator->setRollers(.5);
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
	if (oi->xbox2_bTapped()) {
		elevator->shiftArms();
	}
	if (oi->xbox1_lT()){
		elevator->setRollers(-.5);
	}
	else if (oi->xbox1_rT()){
		elevator->setRollers(.5);
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
	if (oi->xbox2_bTapped()) {
		elevator->shiftArms();
	}

	if (oi->xbox2_lB() && (elevatorEncoder->GetDistance()<46.5 || elevatorOverride)) {
		elevator->setElevator(1);
	}
	else if (oi->xbox2_rB() && (elevatorEncoder->GetDistance()>0 || elevatorOverride)) {
		elevator->setElevator(-.8);
	}
	else {
		elevator->setElevator(0);
	}
	if (oi->xbox2_aTapped()) {
		elevator->shiftElevatorGear();
	}

	if (oi->xbox1_lB()){
		drive->stopdrive();
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
	if (oi->xbox1_yTapped()){
		autoGetTote();
	}
	if (oi->xbox2_yTapped()){
		resetElevator();
	}
}
