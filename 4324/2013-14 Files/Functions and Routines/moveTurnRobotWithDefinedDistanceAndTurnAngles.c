/** ***************************************************************************
 * This routine includes basic movements; names are self-explanatory
 * Defined distance and turn angles
 */

/** ***************************************************************************
 * Constants define encoder revolutions and wheel dimensions
 * change the two values when wheel or encoder changes
 */
const int wheelDiameter=4.0; //diameter of the wheels with encorder
const int	revolutionPerTurn=1440; //encoder revolutions per wheel 360 degree turn
const int degreeToRevolutionConvertionFactor=250; //parameter based on experiment

/** ***************************************************************************
 * chnage the motor names when drive changes
 */

 void Forward(int motorPower, float distanceInches){

/** ***************************************************************************
 * calculate encoder count target based on distance requirements
 */
		int encoderCountTarget=revolutionPerTurn*floor(3.14159*wheelDiameter/distanceInches);
		int timeTakesToMove=1;
/** ***************************************************************************
 * change motor name accordingly
 */
 		motor[motorLF]=motorPower;
		motor[motorRF]=motorPower;
		motor[motorLB]=motorPower;
		motor[motorRB]=motorPower;

 while((nMotorEncoder[motorLB]<encoderCountTarget)||(nMotorEncoder[motorRB]<encoderCountTarget)){
			wait10Msec(timeTakesToMove);
	}
}

void Backward(int motorPower, float distanceInches){

	/** ***************************************************************************
 * calculate encoder count target based on distance requirements
 */
		int encoderCountTarget=revolutionPerTurn*floor(3.14159*4.0/distanceInches);
		int timeTakesToMove=1;
/** ***************************************************************************
 * change motor name accordingly
 */
	motor[motorLF]=-motorPower;
	motor[motorRF]=-motorPower;
	motor[motorLB]=-motorPower;
	motor[motorRB]=-motorPower;

 while((nMotorEncoder[motorLB]<encoderCountTarget)||(nMotorEncoder[motorRB]<encoderCountTarget)){
			wait10Msec(timeTakesToMove);
	}
}

void Left(int motorPower, int turnDegrees){

/** ***************************************************************************
 * calculate encoder count target based on distance requirements
 */
		int encoderCountTarget=degreeToRevolutionConvertionFactor*turnDegrees;
		int timeTakesToMove=1;
/** ***************************************************************************
 * change motor name accordingly
 */

	motor[motorLF]=-motorPower;
	motor[motorRF]=motorPower;
	motor[motorLB]=-motorPower;
	motor[motorRB]=motorPower;

 while((nMotorEncoder[motorLB]<encoderCountTarget)||(nMotorEncoder[motorRB]<encoderCountTarget)){
			wait10Msec(timeTakesToMove);
	}
}

void Right(int motorPower, int turnDegrees){
				/** ***************************************************************************
 * calculate encoder count target based on distance requirements
 */
		int encoderCountTarget=degreeToRevolutionConvertionFactor*turnDegrees;
		int timeTakesToMove=1;
/** ***************************************************************************
 * change motor name accordingly
 */

	motor[motorLF]=motorPower;
	motor[motorRF]=-motorPower;
	motor[motorLB]=motorPower;
	motor[motorRB]=-motorPower;

 while((nMotorEncoder[motorLB]<encoderCountTarget)||(nMotorEncoder[motorRB]<encoderCountTarget)){
			wait10Msec(timeTakesToMove);
	}
}

void Stopbot(){
	motor[motorLF]=0;
	motor[motorRF]=0;
	motor[motorLB]=0;
	motor[motorRB]=0;
}
