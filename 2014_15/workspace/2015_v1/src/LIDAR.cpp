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

LIDAR::LIDAR() : I2C(I2C::Port::kMXP, address), counter(0)
{
//	distanceHigh = new unsigned char();
//	distanceLow = new unsigned char();
	distanceArray[0]='0';
	distanceArray[1]='0';
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
	I2C::Write(controlAddress, 0x00);
	Wait(0.003);
}

int LIDAR::poll(){
	int status=0;
	if (I2C::Write(0x04, 0x00)){
		status+=1;
	}
	Wait(.030);
	if (I2C::Write(controlAddress, measureValue)){
		status+=2;
	}
	Wait(.030);
	/*
	if (I2C::Read(registerHigh, 1, distanceHigh)){
		status+=2;
	}
	Wait(.030);
	if (I2C::Read(registerLow, 1, distanceLow)){
		status+=4;
	}
	*/
	if (I2C::Read(registerHL, 2, distanceArray)){
		status+=4;
	}
	Wait(.030);
	if (I2C::Read(statusAddress, 1, lidarStatus)){
		status+=8;
	}
	Wait(.030);
	if (I2C::Write(0x04, 0x00)){
		status+=16;
	}
	Wait(.030);
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
