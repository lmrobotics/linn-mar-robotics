#ifndef teleopCommand_H
#define teleopCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "telArm.h"
#include "telCompress.h"
#include "telDrive.h"
#include "telMessages.h"

class teleopCommand: public CommandGroup
{
public:
	teleopCommand();
};

#endif
