What we have struggled, what we have learned this year 2012/2013 FTC
# Introduction #
We programmers spend more time troubleshooting and testing than writing software codes. Sometimes it is a broken sensor or burnt motor, sometimes programming environment has bugs, or sometimes we make silly mistakes. This page keeps track of the struggles we went through and lessons we learned.

# Details #

**Multiplexer**
> _Compatibility issue with RobotC version 3.54:_
> > We spent quite a few hours trying to figure out why none the sensors read correct values when connected through a multiplexer. For example, EOPD reads 1000 instead of 200 when connected directly to NXT port.
_Solution_: it turned out to be a bug in RobotC version 3.54. After downloading 3.55 beta 2, sensors worked properly.


> _Sensor values non-reliable through Multiplexer._
> > We found that some of the sensor readings are not reliable when Multiplexer battery level drops, which unfortunately is hard to tell.
> > _Solution_: We decided to connect the complex sensor like EOPD and IRSeeker directly to NXT and connect the simple ones like light and touch sensors to mux and deal with the uncertainties through the code.

**Motor Testing**


> _Having some debug code to test individual motors is very helpful_
> One motor wire or fuse has issues, causing wheel lags in braking. We  swapped motor controllers, ports, motors, and finally found out the wire issues.

> _Solution_: George wrote a function that will allow drivers to use the joystick buttons to test individual motors. This debug function should be on each tele-op program.

**Limitations of IRSeeker**
_Reading accuracy of IR Seeker changes dramatically with tilting angles._
> Previously we have been reading IR beacon in front of the long white line before climbing the board. The result turned out to be very in-consistent. A slight up/down or left/right tilt in angle causes faulse readings. I am not sure this is the nature of the sensors/beacons or that their performance changes over time.

_Solution_: To get reliable readings, we will either have to read the IR beacon on the board, or install the IR beacon on a servo and use scanning and some algorithm to figure out which column the IR beacon is on.

**Challenges of Line-Following When Climbing the Board**

_Light Sensors raises and tilts forward when robot climbs the board, causing robot to move away from the line_
> The motor power(spped) is tweaked together with the spacing between the light sensors, sensor distance from floor, and sensor calibration. When robot's weight center is in transition, the front of the robot tilt upward, increasing the distance of the light sensors from the floor. This causes the inaccurate line-following. In worst cases, the robot moves away from the line compeletly.

_Solution_: We don't have a solid solution yet. Temporary solution is make the ligh sensors very low and almost touching the floor. One potential solution is to use a touch sensor as a feedback to keep the light sensors at a consistent distance above the floor. I do want to give this a try if there is enough time.

