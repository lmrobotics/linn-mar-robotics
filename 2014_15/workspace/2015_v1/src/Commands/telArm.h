#ifndef telArm_H
#define telArm_H

#include "../CommandBase.h"
#include "WPILib.h"

class telArm: public CommandBase
{
public:
	telArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool yPressed;
};

#endif
