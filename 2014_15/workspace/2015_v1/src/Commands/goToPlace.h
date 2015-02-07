#ifndef goToPlace_H
#define goToPlace_H

#include "../CommandBase.h"
#include "WPILib.h"

class goToPlace: public CommandBase
{
public:
	enum phase{
		turning,
		moving
	};
	goToPlace(double angle, double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double destinationAngle;
	double destinationDistance;
	double initialAngle;
	double finalAngle;
	bool done;
	phase currentPhase;
};

#endif
