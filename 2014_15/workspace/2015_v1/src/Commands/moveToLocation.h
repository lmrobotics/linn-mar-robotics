#ifndef moveToLocation_H
#define moveToLocation_H

#include "../CommandBase.h"
#include "WPILib.h"

class moveToLocation: public CommandBase
{
public:
	moveToLocation(float x, float y);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float x;
	float y;

};

#endif
