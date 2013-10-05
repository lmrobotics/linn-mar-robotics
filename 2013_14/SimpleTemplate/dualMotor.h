
#ifndef DUALMOTOR_H
#define DUALMOTOR_H

#include "SafePWM.h"
#include "SpeedController.h"
#include "PIDOutput.h"
#include "Victor.h"

/**
 * IFI Victor Speed Controller
 */
template <class motorType> class dualMotor : public SpeedController
{
public:
	explicit dualMotor(UINT32 channel1, UINT32 channel2);
	dualMotor(UINT8 moduleNumber, UINT32 channel1, UINT32 channel2);
	virtual ~dualMotor();
	virtual void Set(float value, UINT8 syncGroup=0);
	virtual float Get();
	virtual void Disable();

	virtual void PIDWrite(float output);

private:
	motorType motor1;
	motorType motor2;
};

#endif
