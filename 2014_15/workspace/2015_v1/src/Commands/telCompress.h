#ifndef telCompress_H
#define telCompress_H

#include "../CommandBase.h"
#include "WPILib.h"

class telCompress: public CommandBase
{
public:
	telCompress();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
