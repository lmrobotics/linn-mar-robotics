/*
 * LIDAR.h
 *
 *  Created on: Jan 23, 2015
 *      Author: FRC_2013
 */

#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

#include "WPILib.h"

class LIDAR: public I2C {
public:
	LIDAR();
	virtual ~LIDAR();
	int getCM();
	int poll();
	void setup();
	unsigned char getHigh();
	unsigned char getLow();
	unsigned char getLidarStatus();
	int test();

private:

	unsigned char distanceArray[2];
	unsigned char testArray[3];
//	unsigned char *distanceHigh;
//	unsigned char *distanceLow;
	unsigned char *lidarStatus;
	int cmReading;
	int counter;
};

#endif /* SRC_LIDAR_H_ */
