#ifndef myCompressor_H
#define myCompressor_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class myCompressor: public Subsystem, public Compressor
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	explicit myCompressor(uint8_t pcmID);
	bool autoCompress();
	void InitDefaultCommand();
};

#endif
