#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     LightR,         sensorLightActive)
#pragma config(Sensor, S3,     LightL,         sensorLightActive)
#pragma config(Sensor, S4,     HTSMUX,            sensorI2CCustom)
#pragma config(Motor,  motorA,          motorWall,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorR,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorL,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorA,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorB,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servoClaw,            tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("joystickSimple")
#include "drivers/hitechnic-sensormux.h"
#include "JoystickDriver.c"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-eopd.h"
#include "drivers/hitechnic-colour-v2.h"
#include "drivers/lego-touch.h"

const int MP=50;				//Motor power of Drive wheels
const int AWT=20;				//Wobble Timer. Time given for the arm motors to stop wobbling
const int WWT=20;				//Wobble Timer. Time given for the drive motors to stop wobbling

void Forward();
void Backward();
void Left();
void Right();
void Stopbot();
void LineFollow(bool Direction);
int Scan();

const tMUXSensor EOPD = msensor_S4_1;
const tMUXSensor IRFind = msensor_S4_2;
const tMUXSensor Touch = msensor_S4_3;

task main(){
	HTEOPDsetLongRange(EOPD);
	/*
	motor[motorL]=100;
	motor[motorR]=100;
	wait10Msec(320);
	int ScanValue=Scan();						//Perform Scan
	HTEOPDsetLongRange(EOPD);
	Forward();
	while (HTEOPDreadProcessed(EOPD)<1){
		wait10Msec(1);
	}
	nxtDisplayTextLine(0,"Finished");
	wait10Msec(5000);
	//Left();
	wait10Msec(500);
	//Stopbot();
	*/
	LineFollow(-1);
}

void Forward(){
	motor[motorL]=MP;
	motor[motorR]=MP;
}

void Backward(){
	motor[motorL]=-MP;
	motor[motorR]=-MP;
}

void Left(){
	motor[motorL]=-MP;
	motor[motorR]=MP;
}

void Right(){
	motor[motorL]=MP;
	motor[motorR]=-MP;
}

void Stopbot(){
	motor[motorL]=0;
	motor[motorR]=0;
	wait10Msec(WWT);
}

void LineFollow(bool Direction){					//1=Turn Right when found line, -1=Turn Left when found line
	HTEOPDsetLongRange(EOPD);
	bool Foundpeg=false;
	bool FoundLine=false;
	bool FirstSign=false; //false=- , True=+
	int Delta=0;
	int LStart=SensorValue[LightL];
	int RStart=SensorValue[LightR];
	int T=0;
//	while (true){
//	nxtDisplayTextLine(0, "L: %d, R: %d, Delta: %d", SensorValue[LightL], SensorValue[LightR], Delta);
//	wait10Msec(200);
//}
//	wait10Msec(2000);
	//Section 1a: Find the line
	motor[motorL]=20;
	motor[motorR]=20;
	nxtDisplayTextLine(0,"Finding Line");
	while (FoundLine==false){
		Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
		if (SensorValue[LightL]>22 || SensorValue[LightR]>22){
			FoundLine=true;
			if (Delta>0){
				FirstSign=true;
			}
		}
	}
	Stopbot();
	wait10Msec(100);
	FoundLine=false;
	if (Direction==true){
		motor[motorL]=20;
		motor[motorR]=20;
		nxtDisplayTextLine(0,"Moving Forward");
		wait10Msec(100);
		motor[motorR]=-20;
	}
	else {
		motor[motorL]=20;
		motor[motorR]=20;
		nxtDisplayTextLine(0,"Moving Forward");
		wait10Msec(100);
		motor[motorL]=-20;
	}
	nxtDisplayTextLine(0,"Turning onto line");
	while (FoundLine==false){
		Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
		if (SensorValue[LightL]>22 || SensorValue[LightR]>22){
			FoundLine=true;
		}
	}
	wait10Msec(40);
	Stopbot();
	//Section 3: Big turns
	nxtDisplayTextLine(0,"Big Turns");
	while (Foundpeg==false){
		Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
		motor[motorR]=50+Delta*3;
		motor[motorL]=50-Delta*3;
		if (HTEOPDreadRaw(EOPD)>1){
			Foundpeg=true;
		}
	}
	Foundpeg=false;
	nxtDisplayTextLine(0,"Small Turns");
	while (Foundpeg==false){
		Delta=(SensorValue[LightL]-LStart)-(SensorValue[LightR]-RStart);
		motor[motorR]=40+Delta*2;
		motor[motorL]=40-Delta*2;
		if (HTEOPDreadRaw(EOPD)>50){
			Foundpeg=true;
		}
	}
}

int Scan()
{
	int IR1=0;
	int IR2=0;
	int IR3=0;
	int IR4=0;
	int IR5=0;
	int IR11=0;
	int IR12=0;
	int IR13=0;
	int IR14=0;
	int IR15=0;
	int TurnDirection=0;									//Direction the robot is currently moving. 1=Right, -1=Left, 0=Forward
	int TurnAmount=0;											//How much the robot has turned, and in which direction. Right is positive
	while (HTIRS2readDCDir(IRFind)>5){
		Right();
		TurnAmount++;
		wait10Msec(1);
		nxtDisplayTextLine(0,"%d",HTIRS2readDCDir(IRFind));
	}
	while (HTIRS2readDCDir(IRFind)<5){
		Left();
		TurnAmount--;
		wait10Msec(1);
		nxtDisplayTextLine(0,"%d",HTIRS2readDCDir(IRFind));
	}
	Stopbot();
	HTIRS2readAllDCStrength(IRFind, IR1, IR2, IR3, IR4, IR5);
	if (IR4>0){
		motor[motorL]=20;
		motor[motorR]=-20;
		TurnDirection=1;
	}
	else if (IR2>0){
		motor[motorL]=-20;
		motor[motorR]=20;
		TurnDirection=-1;
	}
	else if (IR3<100){
		Stopbot();
		TurnDirection=0;
	}
	else {
		motor[motorL]=20;
		motor[motorR]=-20;
		TurnDirection=1;
		wait10Msec(10);
		TurnAmount+=10;
		HTIRS2readAllDCStrength(IRFind, IR11, IR12, IR13, IR14, IR15);
		if (IR13<IR3){
			motor[motorL]=-20;
			motor[motorR]=20;
			TurnDirection=-1;
		}
	}
	HTIRS2readAllDCStrength(IRFind, IR1, IR2, IR3, IR4, IR5);
	if (TurnDirection !=0){
		while (IR3<100){
			HTIRS2readAllDCStrength(IRFind, IR1, IR2, IR3, IR4, IR5);
			TurnAmount+=TurnDirection;
			wait10Msec(1);
			nxtDisplayTextLine(0,"%d",IR3);
		}
	}
	nxtDisplayTextLine(0, "%d", TurnAmount);
	return TurnAmount;
}
