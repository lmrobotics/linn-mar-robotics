#ifndef telDrive_H
#define telDrive_H

#include "../CommandBase.h"
#include "WPILib.h"

class telDrive: public CommandBase
{
public:
	telDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
