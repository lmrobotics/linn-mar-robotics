#pragma config(Motor,  motorA,          motor1,        tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "dataRecord.c"
#include "pidMotorControlDriver.c"

// This program will test the PID motor control driver made from scratch
task main()
{

  initialializePidMotorControl(50);
  initializeIndividualMotor(motorA);
  setMotorPower(motorA, 600);
  long now;
  long past = time1[T1];
  long deltaTime;
  long encoderValue;
  long savedEncoder = nMotorEncoder[motor1];
  long deltaRotation;
  int CTR = 0;
  while(CTR <= 500)
  {
     CTR = CTR + 1;
     wait1Msec(50);
     now = time1[T1];
     deltaTime = now - past;
     past = now;
     nxtDisplayCenteredTextLine(0, "now %d", now);
     nxtDisplayCenteredTextLine(1, "deltaTime %d", deltaTime);

     encoderValue = nMotorEncoder[motor1];
     nxtDisplayCenteredTextLine(2, "encdrVal %d", encoderValue);
     deltaRotation = encoderValue - savedEncoder;
     savedEncoder = encoderValue;
     nxtDisplayCenteredTextLine(3, "deltaRot %d", deltaRotation);

     long speed = (deltaRotation * 1000) / deltaTime;

     nxtDisplayCenteredTextLine(4, "degSec %d", speed);
     nxtDisplayCenteredTextLine(6, "RPM %d", speed/6);

     nxtDisplayCenteredTextLine(7, "power = %d",motor[motorA]);
     logInt(speed);

  }

  stopMotorControl();
  string fileName = "_myPid.dat";
  saveLog(fileName);
} // main
