#include "BlankPIDOutput.h"

BlankPIDOutput::BlankPIDOutput(){
	lol=0;
}

BlankPIDOutput::~BlankPIDOutput(){
}

BlankPIDOutput::PIDWrite(float output){
	lol=output;
}