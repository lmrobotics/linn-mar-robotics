/*
 * LIDAR.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: FRC_2013
 */

#include <LIDAR.h>

#define address 0x62
#define controlAddress 0x00
#define statusAddress 0x01
#define measureValue 0x04
#define registerHigh 0x0f
#define registerLow 0x10
#define registerHL 0x8f

LIDAR::LIDAR() : I2C(I2C::Port::kMXP, address), counter(0), cmReading(0)
{
//	distanceHigh = new unsigned char();
//	distanceLow = new unsigned char();
	distanceArray[0]='0';
	distanceArray[1]='0';
	testArray[0]=address;
	testArray[1]=controlAddress;
	testArray[2]=0x04;
	lidarStatus = new unsigned char();
	// TODO Auto-generated constructor stub
}

LIDAR::~LIDAR() {
	// TODO Auto-generated destructor stub
}

int LIDAR::getCM(){
	return cmReading;
}

void LIDAR::setup(){
	I2C::Write(address, 0x00);
	Wait(0.005);
}

int LIDAR::poll(){
	int status=0;
//	if (I2C::Write(0x04, 0x00)){
//		status+=8;
//	}

//	for (int i=0;i<50;i++){
//		if (!Write(controlAddress, measureValue)){
//			break;
//		}
//		else {
//			if (i>=49){
//				status+=1;
//			}
//		}
//		Wait(.01);
//	}
    Wait(.025);
	uint8_t myControlAddress=0x01;
	uint8_t myMeasureValue=0x04;
	if (Write(myControlAddress, myMeasureValue)){
		status+=1;
	}
    Wait(.005);
	for (int i=0;i<50;i++){
		if (!Read(registerHL, 2, distanceArray)){
			break;
		}
		else {
			if (i>=49){
				status+=2;
			}
		}
		Wait(.01);
	}
	for (int i=0;i<50;i++){
		if (!Read(statusAddress, 1, lidarStatus)){
			break;
		}
		else {
			if (i>=49){
				status+=4;
			}
		}
		Wait(.01);
	}

	cmReading=(int)((distanceArray[0] <<8) + distanceArray[1]);
//	cmReading=(int)((*distanceHigh <<8)+*distanceLow);
	return status;
}

unsigned char LIDAR::getHigh(){
	return distanceArray[0];
}

unsigned char LIDAR::getLow(){
	return distanceArray[1];
}

unsigned char LIDAR::getLidarStatus(){
	return *lidarStatus;
}

int LIDAR::test(){
	unsigned char* recieve=0x00;
	if (Transaction(testArray, 3, recieve, 1)){
		return 1;
	}
	return 0;
}
