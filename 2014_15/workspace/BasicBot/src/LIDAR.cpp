/*
 * LIDAR.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: FRC_2013
 */

#include <LIDAR.h>

#define address 0x62
#define registerAddress 0x00
#define measureValue 0x04
#define registerHigh 0x0f
#define registerLow 0x10


LIDAR::LIDAR() : I2C(I2C::Port::kMXP, address), counter(0)
{
	distanceHigh = new unsigned char();
	distanceLow = new unsigned char();
	// TODO Auto-generated constructor stub
}

LIDAR::~LIDAR() {
	// TODO Auto-generated destructor stub
}

bool LIDAR::setup(){
	int counter=0;
	while (I2C::Write(registerAddress, measureValue) && counter<100){
		Wait(0.025);
		counter++;
	}
	return true;
}

int LIDAR::read(){
	setup();
	int counter=0;
	while (I2C::Read(registerHigh, 1, distanceHigh) && counter<100){
		Wait(0.025);
		counter++;
	}
	counter=0;
	while (I2C::Read(registerLow, 1, distanceLow)  && counter<100){
		Wait(0.025);
		counter++;
	}
	int result= (int)((*distanceHigh <<8)+*distanceLow);
	return result;
	//return ((*distanceHigh << 8)+ *distanceLow);
}

unsigned char LIDAR::getHigh(){
	return *distanceHigh;
}

unsigned char LIDAR::getLow(){
	return *distanceLow;
}
