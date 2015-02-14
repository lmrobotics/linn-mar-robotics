#ifndef auton2T_H
#define auton2T_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "commandWithAutomation.h"

class auton2T: public commandWithAutomation
{
public:
	auton2T();
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
