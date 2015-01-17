#ifndef telMessages_H
#define telMessages_H

#include "../CommandBase.h"
#include "WPILib.h"

class telMessages: public CommandBase
{
public:
	telMessages();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
