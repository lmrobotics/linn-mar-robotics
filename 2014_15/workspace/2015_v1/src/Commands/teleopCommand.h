#ifndef teleopCommand_H
#define teleopCommand_H

#include <Commands/telControl.h>
#include "Commands/CommandGroup.h"
#include "Commands/pollLIDAR.h"
#include "WPILib.h"
#include "telCompress.h"
#include "telMessages.h"

class teleopCommand: public CommandGroup
{
public:
	teleopCommand();
};

#endif
