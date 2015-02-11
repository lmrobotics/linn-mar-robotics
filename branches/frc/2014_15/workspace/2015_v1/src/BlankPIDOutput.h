#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

#include "WPILib.h"

class BlankPIDOutput: public PIDOutput {
public:
	BlankPIDOutput();
	~BlankPIDOutput();
	void PIDWrite(float output);
	
	private float lol;
};

#endif /* SRC_LIDAR_H_ */
