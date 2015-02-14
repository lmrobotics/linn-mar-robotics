#ifndef telMessages_H
#define telMessages_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <iostream>
#include <cstdio>
#include <ctime>

class telMessages: public CommandBase
{
public:
	telMessages();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	int counter;
};

#endif
