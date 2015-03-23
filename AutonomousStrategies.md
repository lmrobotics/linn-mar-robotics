#Discussions on Autonomous Strategies for FTC Ring It Up!

# Introduction #

Please follow the link to view diagrams and photos that I shared with you through google doc. Wish this page support photos!


# Details #

**Option 1 Starting Position from Left of Dispenser (LofD) and Right of Dispenser (RofD)**

_Strategy_: Note that drivers do not need to differentiate these two starting positions; the program does it automatically.

> _Move forward till close to the line at maximum speed;_

> _Stop, move with slow speed till one of the light sensors reaches the line;_

> _Stop, reset encoder values, then move slowly till both light sensors read the line;_

> _Calcuate the angle between robot and line, then use turn robot to close to staight along the line, using the angle as reference;_

> _Follow the line and move to read IR position;_

> _Scan IR, decide which column is the IR beacon on;_

> _If IR beacon is on the middle, continue moving, then place ring;_

> _If IR beacon is on the sides, back and turn till reaches the line, then follows the line and place the ring;_


_Link:_

https://docs.google.com/file/d/0B7YFwc6_lsxTZjVhMkg1c3FSb0E/edit