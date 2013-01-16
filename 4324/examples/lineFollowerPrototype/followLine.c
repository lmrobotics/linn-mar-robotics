
/** ***************************************************************************
 * \brief Reflective Light sensor threshold for detecting white line on black
 * background.
 */
const int sensorOnLineThreshold = 50;

/** ***************************************************************************
 * \brief Forward power value applied to both wheels before light sensor
 * correction value is applied. Note that if this value set above 33, the
 * calculation made to make a sharp turn when both light sensors are on the line
 * should be reviewed.
 */
const int baseMotorPower = 33;

/** ***************************************************************************
 * \brief The turn rate calculation is multiplied by this constant.  In general,
 * the faster the robot is going, the faster you will want to turn the bot to
 * make corrections.
 */
const float turnRateMulitplier = 1.5;


/** ***************************************************************************
 * \brief This constant compensates for the differences in the sensitivity 
 * of the two light sensors.
 */
const int sensorCal = 11;

/** ***************************************************************************
 * \brief Determines if sensor value is above white line and not on black
 * background.
 *
 * \param[in] value - Light sensor value
 *
 * \return True if sensor is on the white line, false on back background.
 */
bool sensorOnLine(int value)
{
   return value > sensorOnLineThreshold;
} // sensorOnLine

/** ***************************************************************************
 * \brief Determines if both light sensors are above the white line.
 *
 * Requires two reflective light sensors named leftLightSensor and
 * rightLightSensor.
 *
 * \return True if both left and right light sensors are on the line,
 * false otherwise
 */
bool bothLightSensorsOnLine()
{
   int leftLineSensorValue   = SensorValue[leftLightSensor];
   int rightLineSensorValue = SensorValue[rightLightSensor];

   return (sensorOnLine(leftLineSensorValue) && sensorOnLine(rightLineSensorValue));
} // bothLightSensorsOnLine

bool stopLineFollower()
{
  //getJoystickSettings(joystick);
  //return (joystick.joy1_Buttons & 32) != 0;
  return SensorValue(touchSensor) == 1;
}

/** ***************************************************************************
 * \brief main task that will follow a 1 inch white line on a black background.
 * This program was tested with two active light sensors approximately 1 1/8
 * inches apart.
 *
 */
void follow()
{
  initializeIndividualMotor(rightMotor, 50);
  initializeIndividualMotor(leftMotor, 50);
  initialializeMotorControl(1);
  // disable joystick diagnostic
  disableDiagnosticsDisplay();

   // delay to wait for light sensors to initialize.
   wait1Msec(50);
   eraseDisplay();
   while (!stopLineFollower())
   {
      int leftLineSensorValue  = SensorValue[leftLightSensor];
      int rightLineSensorValue = SensorValue[rightLightSensor];

      float turnFactor = ((float)(leftLineSensorValue - rightLineSensorValue + sensorCal))*turnRateMulitplier;
      nxtDisplayCenteredTextLine(3, "right (1) %d", leftLineSensorValue );
      nxtDisplayCenteredTextLine(4, " left (3) %d", rightLineSensorValue );
      nxtDisplayCenteredTextLine(5, "turn factor %d", turnFactor );
      if (bothLightSensorsOnLine())
      {
      	// tell robot take a sharp left turn
        // suggested improvement: use encoders to make turn more precise
        // suggested improvement: use a constant to adjust turn rate based
        // on distance between drive wheels.
        setMotorPower(rightMotor, baseMotorPower*3);
        setMotorPower(leftMotor,  -baseMotorPower);
        wait1Msec(400);
      }
      else
      {
      	// else assume bot is betweeen the lines
        // make gentle corrections to make bot follow the line
        setMotorPower(rightMotor,(baseMotorPower + turnFactor));
        setMotorPower(leftMotor, (baseMotorPower - turnFactor));
        wait1Msec(10);
      } // else both sensors not on line
   } // while

  motorChangeTimeInterval = 10;
  stopMotorControl();
  wait1Msec(500);

} // task main
