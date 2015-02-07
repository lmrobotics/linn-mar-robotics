#ifndef telDrive_H
#define telDrive_H

#include "../CommandBase.h"
#include "goToPlace.h"
#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "Commands/commandWithAutomation.h"

class telControl: public commandWithAutomation
{
public:
	telControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void normalOperation();
protected:

	void normalOperationLoop();
};

#endif
