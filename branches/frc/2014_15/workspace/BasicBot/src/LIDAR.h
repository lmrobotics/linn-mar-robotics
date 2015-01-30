/*
 * LIDAR.h
 *
 *  Created on: Jan 29, 2015
 *      Author: FRC_2013
 */

#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

#include "WPILib.h"

class LIDAR: public I2C {
public:
	LIDAR();
	virtual ~LIDAR();
	bool setup();
	int read();

	//Debug Stuff
	unsigned char getHigh();
	unsigned char getLow();

private:

	unsigned char *distanceHigh;
	unsigned char *distanceLow;
	int counter;
};

#endif /* SRC_LIDAR_H_ */
