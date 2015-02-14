
#ifndef SRC_BLANKPIDOUTPUT_H_
#define SRC_BLANKPIDOUTPUT_H_

#include "WPILib.h"

class BlankPIDOutput: public PIDOutput {
public:
	BlankPIDOutput();
	virtual void PIDWrite(float output);
	float lol;
};

#endif /* SRC_BLANKPIDOUTPUT_H_ */

