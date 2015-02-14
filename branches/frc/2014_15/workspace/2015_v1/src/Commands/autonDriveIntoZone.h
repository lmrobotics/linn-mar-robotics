#ifndef autonDriveIntoZone_H
#define autonDriveIntoZone_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "commandWithAutomation.h"

class autonDriveIntoZone: public commandWithAutomation
{
public:
	autonDriveIntoZone();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void normalOperation();
	void normalOperationLoop();
private:
	int phase;
};

#endif
