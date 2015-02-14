#include <Commands/telControl.h>


telControl::telControl()
{
	Requires(drive);
	Requires(elevator);
	currentState=NORMAL;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void telControl::Initialize() {
	dash->PutString("Does It Work?", "YES");
}

// Called repeatedly when this Command is scheduled to run
void telControl::Execute() {
	drive->TeleDrive(oi->xbox1_y1(), oi->xbox1_x2());
	if (oi->xbox1_rBTapped()) {
		drive->shift();
	}

	runCurrentLoop();

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

void telControl::normalOperation(){

}

void telControl::normalOperationLoop(){
	if (oi->xbox2_lT()) {
		elevator->setRollers(-.5);
		elevator->setConveyor(-conveyorSpeed);
	}
	else if (oi->xbox2_rT()) {
		elevator->setRollers(.5);
		elevator->setConveyor(conveyorSpeed);
	}
	else if (oi->xbox1_lT()) {
		elevator->setRollers(-.5);
		elevator->setConveyor(-conveyorSpeed);
	}
	else if (oi->xbox1_rT()) {
		elevator->setRollers(.5);
		elevator->setConveyor(conveyorSpeed);
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
		elevator->setConveyor(0);
	}
	if (oi->xbox2_lB()) {
		elevator->setElevator(.6);
	}
	else if (oi->xbox2_rB()) {
		elevator->setElevator(-1);
	}
	else {
		elevator->setElevator(0);
	}
	if (oi->xbox2_aTapped()) {
		elevator->shiftElevatorGear();
	}
	if (oi->xbox2_bTapped()) {
		elevator->shiftArms();
	}
	if (oi->xbox2_xTapped()) {
		elevator->shiftMagazine();
	}
	if (oi->xbox1_lB()){
		drive->stopdrive();
	}

	//a button flips between normal drive and controlled acceleration---request from Grayson
	//MoveNormal = normal drive and MoveCurve = limited acceleration
	if (oi->xbox1_aTapped()){
		if (drive->getAccel()>=.5){
			drive->setAccel(.02);
		}
		else {
			drive->setAccel(2);
		}
	}
	//
}
