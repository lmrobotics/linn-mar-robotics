#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "WPILib.h"

class myUltrasonic : public AnalogInput{
public:
    explicit myUltrasonic(uint32_t channel);
	virtual ~myUltrasonic();
	double getDistance();
private:
    double calibFactor;
	double calibConstant;
};

#endif
