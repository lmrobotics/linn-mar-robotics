/** ***************************************************************************
 * This routine includes basic movements; names are self-explanatory
 * Indifinite distance
 * Robot moving speed controlled by motorPower
 */
void Forward(int motorPower){
        motor[motorLF]=motorPower;
        motor[motorRF]=motorPower;
        motor[motorLB]=motorPower;
        motor[motorRB]=motorPower;
}

void Backward(int motorPower){
        motor[motorLF]=-motorPower;
        motor[motorRF]=-motorPower;
        motor[motorLB]=-motorPower;
        motor[motorRB]=-motorPower;
}

void Left(int motorPower){
        motor[motorLF]=-motorPower;
        motor[motorRF]=motorPower;
        motor[motorLB]=-motorPower;
        motor[motorRB]=motorPower;
}

void Right(int motorPower){
        motor[motorLF]=motorPower;
        motor[motorRF]=-motorPower;
        motor[motorLB]=motorPower;
        motor[motorRB]=-motorPower;
}

void Stopbot(){
        motor[motorLF]=0;
        motor[motorRF]=0;
        motor[motorLB]=0;
        motor[motorRB]=0;
}
