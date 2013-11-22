Zach's Auto Changelog:
Revision 185 made Nov 21
* changed all park() and wait1Msec lines to fullStop(), that kills the momentum
* changed jerk() to toBasket()
* toBasket() now slightly curves towards the bridge
* toBasket() now waits 400 milliseconds for movement instead of 500
* toBasket() now uses fullStop() instead of park()
- commented out all code except waitForStart() and toBasket() for testing