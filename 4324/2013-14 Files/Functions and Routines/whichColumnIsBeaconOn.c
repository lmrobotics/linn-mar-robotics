/** ***************************************************************************
* The most simple way to detect IR beacon, using processed IR zone readings
* name of the IR Seeker must be HTIRS2
*/

int whichColumnIsBeaconOn()
{
/** ***************************************************************************
* _dirDC reads unmodulated IR signals
* _dirAC reads modulated IR signals, which is what we use
*/
	int _dirDC = 0;
	int _dirAC = 0;
	// the default DSP mode is 1200 Hz.
	//	tHTIRS2DSPMode _mode = DSP_1200;

	_dirDC = HTIRS2readDCDir(HTIRS2);
  _dirAC=HTIRS2readACDir(HTIRS2);
/** ***************************************************************************
* -1: beacon on left column; 0: beacon on middle column; 1: beacon on right column
* Based on the assumption that IR (robot) faces the middle column
*/

 if (_dirAC<5){
     return -1;
   }
   else if (_dirAC>5){
     return 1;
   }
   else {
     return 0;
   }
 }
