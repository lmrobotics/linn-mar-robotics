/** ***************************************************************************
 * This routine use a servo to turn the IRSeeker and find out the direction (in degrees) of the IR beacon
 from the front of robot. It returns the degrees. Positive value representing the beacon is on the right
 side; negative value means the beacon is on the left side
 the servo name must be defined as irSeeker when the routing is called from main
 * 
 */

int irBeaconDirectionInDegrees()
{
/** ***************************************************************************
 *	initial scan to decide where the beacon is
 * 
 */
	char turn_direction='N';		//turn direction: R-right; L-left; N- null
	int ir_mid_position=110;
	int ir_start_position=60;
	int ir_stop_position=180;
	int ir_max_position=110;		//servo position/angle where IR reading reaches maximum
	int ir_reading_maxDC=0;
	int ir_reading_maxAC=0;
	int ir_change_rate=5;
	int _dirDC = 0;
	int _dirAC = 0;
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;
/** ***************************************************************************
 *	// the default DSP mode is 1200 Hz.
	//	tHTIRS2DSPMode _mode = DSP_1200;
 * 
 */

	servoChangeRate[irSeeker]=ir_change_rate;
	servo[irSeeker]=ir_mid_position;
	wait1Msec(1000);
	// Read the current non modulated signal direction
     _dirDC = HTIRS2readDCDir(HTIRS2);
     _dirAC=HTIRS2readACDir(HTIRS2);
     nxtDisplayCenteredTextLine(0,"%d",_dirDC);
     nxtDisplayCenteredTextLine(1,"%d",_dirAC);
     wait1Msec(10);
/** ***************************************************************************
 *	//turn left or right depending on IR reading, until direction reaches 5
		// set "turn_direction" glas
 * 
 */	

/** ***************************************************************************
 *	   	//if irSeeker middle zone points to IR beacon, turn left to it is on zone 4
 * 
 */	 
   	if (_dirAC==5){
   		servo[irSeeker]=servo[irSeeker]-30;
   		turn_direction='R';
   		nxtDisplayCenteredTextLine(3,"%d", ServoValue[irSeeker]);
   		wait1Msec(1000);
   	}

/** ***************************************************************************
 *	   	// now that ir beacon should be on the right or left side of the robot;
 * 
 */	
      while ((_dirAC>5) &&(ServoValue[irSeeker]<ir_stop_position)){
   			turn_direction='R';
   			servo[irSeeker]=servo[irSeeker]+10;
   			nxtDisplayCenteredTextLine(4,"turning Right");
   			wait1Msec(500);
				_dirAC = HTIRS2readACDir(HTIRS2);
			}

			while ((_dirAC<5) &&(ServoValue[irSeeker]>ir_start_position)){
				turn_direction='L';
				servo[irSeeker]=servo[irSeeker]-10;
   			nxtDisplayCenteredTextLine(5,"turning left");
				wait1Msec(500);
				_dirAC = HTIRS2readACDir(HTIRS2);

			}
/** ***************************************************************************
 *	   	//now that _dirDC=5,continue turning on same direction until maxium
			//reading in zone 5.
			// Read the individual signal strengths of the internal sensors
			// Do this for both unmodulated (DC) and modulated signals (AC)
 * 
 */
			HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5);
			HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );
			wait1Msec(1);

			// set temporary ir maximium position
			ir_max_position=ServoValue[irSeeker];
			ir_reading_maxDC=dcS3;
			ir_reading_maxAC=acS3;
/** ***************************************************************************
 *	   				//continue turning left until mid zone reading max
 * 
 */
			
		if (turn_direction=='L'){

				while (dcS3>=ir_reading_maxDC || acS3>=ir_reading_maxAC){

					//assign current ir reading to ir_reading_maxDC and ir_reading_maxAC
					ir_reading_maxDC=dcS3;
					ir_reading_maxAC=acS3;

					//continue turning left if not reading maximum ir reading
   				servo[irSeeker]=servo[irSeeker]-5;
   				ir_max_position=ServoValue[irSeeker];
					wait1Msec(200);
					turn_direction='L';

					//read IRseeker values
					HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5);
					HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );
					wait1Msec(10);
				}
		}
		//continue turning left until mid zone reading max
		else if (turn_direction=='R'){

				while (dcS3>=ir_reading_maxDC || acS3>=ir_reading_maxAC){

					//assign current ir reading to ir_reading_maxDC and ir_reading_maxAC
					ir_reading_maxDC=dcS3;
					ir_reading_maxAC=acS3;

					//continue turning left if not reading maximum ir reading
   				servo[irSeeker]=servo[irSeeker]+5;
   				ir_max_position=ServoValue[irSeeker];
   				turn_direction='R';
					wait1Msec(200);
					//read IRseeker values
					HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5);
					HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );
					wait1Msec(10);
				}
		}
		//default turn direction is null
		else {
		turn_direction='N';
	}
	return ((ir_max_position-ir_mid_position)*180)/255; //return degrees robot need to turn toward IR beacon
}