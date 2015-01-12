#include "myUltrasonic.h"

/**
 * Constructor
 */
myUltrasonic::myUltrasonic(uint32_t channel) : AnalogInput(channel)
{
	calibFactor=259.1837;
	calibConstant=0.0;
}

myUltrasonic::~myUltrasonic()
{
}

//Gets the distance to the detected object in cm
double myUltrasonic::getDistance(){
	return (AnalogInput::GetVoltage()*calibFactor + calibConstant);
}
