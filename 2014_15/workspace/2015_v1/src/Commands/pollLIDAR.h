#ifndef pollLIDAR_H
#define pollLIDAR_H

#include "../CommandBase.h"
#include "WPILib.h"
#include <iostream>
#include <cstdio>
#include <ctime>

class pollLIDAR: public CommandBase
{
public:
	pollLIDAR();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void resetPollTimer();

private:
	double pollTimer;
	std::clock_t lastPoll;
};

#endif
