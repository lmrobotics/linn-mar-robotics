#ifndef autonomousCommand_H
#define autonomousCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "auton1T.h"
#include "auton2T.h"
#include "auton3T.h"
#include "autonDriveIntoZone.h"
#include "../CommandBase.h"

class autonomousCommand: public CommandGroup
{
public:
	autonomousCommand();
};

#endif
