
#include "BlankPIDOutput.h"

BlankPIDOutput::BlankPIDOutput(): lol(0.0){

}

void BlankPIDOutput::PIDWrite(float output){
	lol=output;
}
