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


LIDAR::LIDAR() : I2C(I2C::Port::kMXP, address), counter(0)
{
	distanceHigh = new unsigned char();
	distanceLow = new unsigned char();
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

void LIDAR::poll(){
	I2C::Write(controlAddress, measureValue);
	Wait(.025);
	I2C::Read(registerHigh, 1, distanceHigh);
	Wait(.003);
	I2C::Read(registerLow, 1, distanceLow);
	Wait(.003);
	I2C::Read(statusAddress, 1, lidarStatus);
	cmReading=(int)((*distanceHigh <<8)+*distanceLow);
}

unsigned char LIDAR::getHigh(){
	return *distanceHigh;
}

unsigned char LIDAR::getLow(){
	return *distanceLow;
}

unsigned char LIDAR::getLidarStatus(){
	return *lidarStatus;
}
