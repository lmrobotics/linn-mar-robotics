#ifndef auton1T_H
#define auton1T_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "commandWithAutomation.h"

class auton1T: public commandWithAutomation
{
public:
	auton1T();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void normalOperation();
	void normalOperationLoop();
	void setTurnRight(bool turnRight);
private:
	int phase;
	bool turnRight;
};

#endif
