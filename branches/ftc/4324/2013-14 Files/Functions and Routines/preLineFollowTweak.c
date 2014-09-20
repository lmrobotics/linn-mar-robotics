/** ***************************************************************************
 * This function will be used together with line-follower.
 * First decide the angle and direction the robot is approaching the line
 * Then turn according to the angle and direction to make the robot more or less straight
 * and ready for line-following program
 *
 * angle=acos(linewidth/encoderReading)
 */

/** ***************************************************************************
 * move at a fairly low speed to increase measurement accuracy
 */
 const int slowSpeed=15;	//slow moving speed to determine angles
 const int maxEncoderCount=2880; // max encoder count for straight movement, no
 																	//tweak required if motor moves this far.


 void preLineFollowTweak(){

/** ***************************************************************************
 * Encoder count to decide the angle the robot is approaching the line,
 * used to decide how much the robot to should turn to be ready for line-following
 */
 	int angleEncoderCount=0;
 	int leftLightReading=0;
 	int rightLightReading=0;

/** ***************************************************************************
 * move till one of the two light sensors find the line
 */
	motor[motorLF]=slowSpeed;
	motor[motorRF]=slowSpeed;
	motor[motorLB]=slowSpeed;
	motor[motorRB]=slowSpeed;
	while ((SensorValue[LightL]<40) && (SensorValue[LightR]<40)){
		wait1Msec(2);
	}
	Stopbot();
	leftLightReading=SensorValue[LightL];
	rightLightReading=SensorValue[LightR];
	wait10Msec(2);

	/** ***************************************************************************
 * Reset encoder values
 */
 	nMotorEncoder[motorLF]=0;
	nMotorEncoder[motorRF]=0;
	nMotorEncoder[motorLB]=0;
	nMotorEncoder[motorRB]=0;

/** ***************************************************************************
 * 	Continue move the robot slowly until both light sensors are on the line,
 *  or encoder reaches two revolution counts, indicating that the robot has been
 *  moving very starightly on the line
 */
 	motor[motorLF]=slowSpeed;
	motor[motorRF]=slowSpeed;
	motor[motorLB]=slowSpeed;
	motor[motorRB]=slowSpeed;
	while ((SensorValue[LightL]<40) || (SensorValue[LightR]<40)||(nMotorEncoder[motorLB]>maxEncoderCount)){
		wait1Msec(2);
	}
	Stopbot();
	angleEncoderCount=nMotorEncoder[motorLB];
	wait1Msec(2);

/** ***************************************************************************
 * Now that either both light sensors are on the line,
 * or wheels have moved 2 revolutions
 *
 */

/** ***************************************************************************
 * Turn on-spot based on encoder counts,
 *  or ready for line-following if maxEncoderCount has reached
 * turn right or left depending on which light sensor reaches line first.
 * Left light reaches first indicating robot approaching from ight; Right Light
 * reaches first indicating robot appraching line from left.
 */

 	if ((angleEncoderCount<maxEncoderCount) && (leftLightReading<rightLightReading)){
 		motor[motorRF]=30;
		motor[motorRB]=30;
 		while ((nMotorEncoder[motorRF]<angleEncoderCount) || (nMotorEncoder[motorRB]<angleEncoderCount)){
			wait1Msec(2);
		}
		Stopbot();
		wait1Msec(2);
	}

	if ((angleEncoderCount<maxEncoderCount) && (leftLightReading>rightLightReading)){
 		motor[motorLF]=30;
		motor[motorLB]=30;
 		while ((nMotorEncoder[motorRF]<angleEncoderCount) || (nMotorEncoder[motorRB]<angleEncoderCount)){
			wait1Msec(2);
		}
		Stopbot();
		wait1Msec(2);
	}

}
