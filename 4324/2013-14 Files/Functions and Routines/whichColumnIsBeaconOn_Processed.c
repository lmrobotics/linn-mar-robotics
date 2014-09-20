/** ***************************************************************************
* The most simple way to detect IR beacon, using processed IR zone readings
* Name of the IR seeker must be HTIRS2
 */

int whichColumnIsBeaconOn()
{
/** ***************************************************************************
* acS1 to acS5 are non processed zones
 */
	int acS1, acS2, acS3, acS4, acS5 = 0;
	// the default DSP mode is 1200 Hz.
	//	tHTIRS2DSPMode _mode = DSP_1200;

	HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );

/** ***************************************************************************
* -1: beacon on left column; 0: beacon on middle column; 1: beacon on right column
 * Based on the assumption that IR (robot) faces the middle column
 */

 if ((acS2>30)&&(acS4<10)){
     return -1;
   }
   else if ((acS2<10)&&(acS4>30)){
     return 1;
   }
   else {
     return 0;
   }
}
