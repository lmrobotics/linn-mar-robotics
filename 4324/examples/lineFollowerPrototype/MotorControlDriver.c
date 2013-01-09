// \cond - tell Doxigen to not include prototypes, typedefs and globals in the generated documentation.
/*
 * Internal data Structure used to save motor information
 */
typedef struct
{
  int currentMotorPower; // current motor power setting
  int targetMotorPower;  // desired motor power setting
  int motorID;           // ID of motor to control
  int stepSize;          // amount of change to apply to motor each time interval
} motorObjectType;

const int maxNumberOfMotors = 10;      // max mumber of motors driver can  control
static int numberOfMotors = 0;          // Number of motors the driver that have been initialized so far
static int motorChangeTimeInterval = 5; // number of milliseconds to wait before making next power step change.
                                        // can be changed when in call to initialializeMotorControl

static motorObjectType motors[maxNumberOfMotors];

task serviceMotorPowerChange();

// \endcond

/** ***************************************************************************
 * \brief Initialize motor control driver.
 *
 * \param serviceTime - The amount delay between applying each
 * stepSize change to the current motor power level. The larger this value is
 * the longer it will take to apply a new target power level to the motor.
 * This delay is specified in milliseconds. The default value is 5 milliseconds.
 */
void initialializeMotorControl(int serviceTime = 5)
{
  StartTask(serviceMotorPowerChange);
  motorChangeTimeInterval = serviceTime;
}

/** ***************************************************************************
 * \brief Gradually brings all motors to a halt and stops the motor control
 * task.  If logging is enabled, the log is written.
 */
void stopMotorControl()
{
  bool motorsStopped = false;
  for (int motorIndex = 0; motorIndex < numberOfMotors; motorIndex++)
  {
  motors[motorIndex].targetMotorPower = 0;
  }

  while (!motorsStopped)
  {
    wait1Msec(motorChangeTimeInterval);
    motorsStopped = true;
    for (int motorIndex = 0; motorIndex < numberOfMotors; motorIndex++)
    {
    if (motors[motorIndex].currentMotorPower != 0)
      motorsStopped = false;
    }
  }
  StopTask(serviceMotorPowerChange);
}

/** ***************************************************************************
 * \brief Initialize specific motor to be controlled by the driver.
 *
 * When called for the first time for a specific motorID, the current and
 * target power levels are set to zero.  On subsequent calls to
 * initialize a specific motor, the current and target power levels are not modified.
 * Calling this function multiple times for a specific motorID is allowed so that the
 * stepSize value for the motor can be modified.
 *
 * \param motorID - ID of motor to be controlled.
 *
 * \param stepSize - Amount of change to apply to motor power every serviceTime time interval.
 */
void initializeIndividualMotor(int motorID, int stepSize = 1)
{
  bool found = false;
  // search to see of motor is already stored in control array
  for (int motorIndex = 0; motorIndex < numberOfMotors; motorIndex++)
  {
    if(motors[motorIndex].motorID == motorID)
    {
      // if found, set the new step size.i
      motors[motorIndex].stepSize = stepSize;
      found = true;
    }
  } // for each existing motor in control array

  if (!found && (numberOfMotors < maxNumberOfMotors))
  {
    motors[numberOfMotors].motorID = motorID;
    motors[numberOfMotors].currentMotorPower = 0;
    motors[numberOfMotors].targetMotorPower = 0;
    motors[numberOfMotors].stepSize = stepSize;
    numberOfMotors++;
  } // if motor needs to be added to array

}

/** ***************************************************************************
 * \brief Set the target power level for the specified motor.
 *
 * Important Note: initializeIndividualMotor must be called prior to
 * calling this function with the specific motorID.
 *
 * \param motorID - motor to apply newTargetPowerLevel to.
 *
 * \param newTargetPower - power level to apply to motor.
 */
void setMotorPower(int motorID, int newTargetPower)
{
  for (int motorIndex = 0; motorIndex < numberOfMotors; motorIndex++)
  {
    if(motors[motorIndex].motorID == motorID)
    {
      motors[motorIndex].targetMotorPower = newTargetPower;
    }
  }
} // setMotorPower

/** ***************************************************************************
 * \brief Warning: Should not be called directly!
 *
 * This task will service changes in the motor power level. The target power
 * level is achieved by increasing or decreasing the current power level by
 * the stepSize and then delaying by the motorChangeTimeInterval.  This is
 * repeated until the target motor speed is achieved.
 */
task serviceMotorPowerChange()
{
  while(true)
  {
    for (int motorIndex = 0; motorIndex < numberOfMotors; motorIndex++)
    {
      int stepSize = motors[motorIndex].stepSize;
      // initialize newValue to current power so the power doesn't change if
      // the target power has been set already
      short newValue = motors[motorIndex].currentMotorPower;
      // check to see if current motor power is greater that target
      if (motors[motorIndex].currentMotorPower > motors[motorIndex].targetMotorPower)
      {
        if ((motors[motorIndex].currentMotorPower -
             motors[motorIndex].targetMotorPower) > stepSize)
        {
          newValue = motors[motorIndex].currentMotorPower - stepSize;
        }
        else
        {
          newValue = motors[motorIndex].targetMotorPower;
        }
      }
      // check to see if current power is less than target power
      else if (motors[motorIndex].currentMotorPower < motors[motorIndex].targetMotorPower)
      {
        if ((motors[motorIndex].targetMotorPower -
             motors[motorIndex].currentMotorPower) > stepSize)
          {
            newValue = motors[motorIndex].currentMotorPower + stepSize;
          }
          else
          {
            newValue = motors[motorIndex].targetMotorPower;
          }
      }
      else
      {
         newValue = motors[motorIndex].targetMotorPower;
      }

      //if (newValue != motors[motorIndex].currentMotorPower)
      {
        motors[motorIndex].currentMotorPower = newValue;
        motor[motors[motorIndex].motorID] = newValue;
        nxtDisplayTextLine(motorIndex, "motor%d = %d", motors[motorIndex].motorID, motor[motors[motorIndex].motorID]);
      }
    } // for each motor

    wait1Msec(motorChangeTimeInterval);

  } // while true
} // serviceMotorPowerChange
