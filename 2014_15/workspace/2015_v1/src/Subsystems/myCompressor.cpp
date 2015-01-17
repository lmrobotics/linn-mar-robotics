#include "myCompressor.h"
#include "../RobotMap.h"

myCompressor::myCompressor(uint8_t pcmID) :
		Subsystem("ExampleSubsystem"),
		Compressor(pcmID)
{

}

void myCompressor::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

bool myCompressor::autoCompress(){
	if(!GetPressureSwitchValue()){
		Start();
		return true;
	}
	else {
		Stop();
		return false;
	}
}
