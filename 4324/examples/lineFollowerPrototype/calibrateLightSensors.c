#pragma config(Sensor, S1,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S3,     leftLightSensor, sensorLightActive)

/** ***************************************************************************
 * \brief
 *
 */
task main()
{

   // delay to wait for light sensors to initialize.
   wait1Msec(50);
   eraseDisplay();
   while (true)
   {
      int leftLineSensorValue  = SensorValue[leftLightSensor];
      int rightLineSensorValue = SensorValue[rightLightSensor];

      nxtDisplayCenteredTextLine(3, "right (1) %d", leftLineSensorValue );
      nxtDisplayCenteredTextLine(4, " left (3) %d", rightLineSensorValue );
      nxtDisplayCenteredTextLine(5, "cal factor %d", rightLineSensorValue - leftLineSensorValue );
      wait1Msec(10);
   } // while

  wait1Msec(500);

} // task main
