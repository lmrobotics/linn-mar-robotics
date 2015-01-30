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
	void poll();
	void setup();
	unsigned char getHigh();
	unsigned char getLow();
	unsigned char getLidarStatus();

private:

	unsigned char *distanceHigh;
	unsigned char *distanceLow;
	unsigned char *lidarStatus;
	int cmReading;
	int counter;
};

#endif /* SRC_LIDAR_H_ */
