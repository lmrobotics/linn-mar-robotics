const int MP=15;                                //Motor power of Drive wheels
const int EWT=20;                               //Wobble Timer. Time given for the Elevator motors to stop wobbling
const int WWT=20;                               //Wobble Timer. Time given for the drive motors to stop wobbling

** ***************************************************************************
 * \brief 
 */
void Forward(){
        motor[motorLF]=MP;
        motor[motorRF]=MP;
        motor[motorLB]=MP;
        motor[motorRB]=MP;
}

** ***************************************************************************
 * \brief 
 */
void Backward(){
        motor[motorLF]=-MP;
        motor[motorRF]=-MP;
        motor[motorLB]=-MP;
        motor[motorRB]=-MP;
}

** ***************************************************************************
 * \brief 
 */
void Left(){
        motor[motorLF]=-MP;
        motor[motorRF]=MP;
        motor[motorLB]=-MP;
        motor[motorRB]=MP;
}

** ***************************************************************************
 * \brief 
 */
void Right(){
        motor[motorLF]=MP;
        motor[motorRF]=-MP;
        motor[motorLB]=MP;
        motor[motorRB]=-MP;
}

** ***************************************************************************
 * \brief 
 */
void Stopbot(){
        motor[motorLF]=0;
        motor[motorRF]=0;
        motor[motorLB]=0;
        motor[motorRB]=0;
        wait10Msec(WWT);
}

** ***************************************************************************
 * \brief 
 */
void LineFollow(bool Direction){                                        //true=Turn Right when found line, false=Turn Left when found line
        HTEOPDsetLongRange(EOPD);
        bool Foundpeg=false;
        bool FoundLine=false;
        bool FirstSign=false;                                                                           //false=- , True=+
        int Delta=0;
        int LStart=16;
        int RStart=15;
        //Section 1a: Find the line
        motor[motorLF]=MP;
        motor[motorRF]=MP;
        motor[motorLB]=MP;
        motor[motorRB]=MP;
        nxtDisplayTextLine(0,"Finding Line");
        while (FoundLine==false){
                Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
                if (SensorValue[LightL]>22 || SensorValue[LightR]>22){
                        FoundLine=true;
                        if (Delta>0){
                                FirstSign=true;
                        }
                }
                wait10Msec(1);
        }
        Stopbot();
        wait10Msec(100);
        FoundLine=false;
        Foundpeg=false;
        nxtDisplayTextLine(0,"Small Turns");
        while (Foundpeg==false){
                Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
                motor[motorRF]=MP+((Delta*1)/3);
                motor[motorLF]=MP-((Delta*1)/3);
                motor[motorRB]=MP+((Delta*1)/3);
                motor[motorLB]=MP-((Delta*1)/3);
                if (HTEOPDreadRaw(EOPD)>=18){
                        Foundpeg=true;
                        Stopbot();
                }
                wait10Msec(1);
        }
}
