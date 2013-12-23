#include "dualMotor.h"

#include "DigitalModule.h"
#include "NetworkCommunication/UsageReporting.h"
#include "LiveWindow/LiveWindow.h"


/**
 * Constructor that assumes the default digital module.
 * 
 * @param channel The PWM channel on the digital module that the motors are attached to.
 */
 dualMotor::dualMotor(UINT32 channel1, UINT32 channel2) : 
   motor1(channel1),
   motor2(channel2)
{
}

/**
 * Constructor that specifies the digital module.
 * 
 * @param moduleNumber The digital module (1 or 2).
 * @param channel The PWM channel on the digital module that the motors are attached to (1..10).
 */
 dualMotor::dualMotor(UINT8 moduleNumber, UINT32 channel1, UINT32 channel2) : 
   motor1(channel1),
   motor2(channel2)
{
}

 dualMotor::~dualMotor()
{
}

/**
 * Set the PWM value.  
 * 
 * The PWM value is set using a range of -1.0 to 1.0, appropriately
 * scaling the value for the FPGA.
 * 
 * @param speed The speed value between -1.0 and 1.0 to set.
 * @param syncGroup Unused interface.
 */
 void dualMotor::Set(float speed, UINT8 syncGroup)
{
	motor1.Set(speed, syncGroup);
	motor2.Set(speed, syncGroup);
}

/**
 * Get the recently set value of the PWM.
 * 
 * @return The most recently set value for the PWM between -1.0 and 1.0.
 */
 float dualMotor::Get()
{
	return motor1.Get();
}

/**
 * Common interface for disabling a motor.
 */
 void dualMotor::Disable()
{
	motor1.Disable();
	motor2.Disable();
}

/**
 * Write out the PID value as seen in the PIDOutput base object.
 * 
 * @param output Write out the PWM value as was found in the PIDController
 */
 void dualMotor::PIDWrite(float output) 
{
	motor1.PIDWrite(output);
	motor2.PIDWrite(output);
}
