#include "OI.h"

OI::OI() : xbox1(0), xbox2(1)
{
}

float OI::xbox1_x1(){
	return xbox1.GetRawAxis(0);
}
float OI::xbox1_y1(){
	return xbox1.GetRawAxis(1);
}
float OI::xbox1_lTVal(){
	return xbox1.GetRawAxis(2);
}
float OI::xbox1_rTVal(){
	return xbox1.GetRawAxis(3);
}
float OI::xbox1_x2(){
	return xbox1.GetRawAxis(4);
}
float OI::xbox1_y2(){
	return xbox1.GetRawAxis(5);
}
bool OI::xbox1_a(){
	return xbox1.GetRawButton(1);
}
bool OI::xbox1_b(){
	return xbox1.GetRawButton(2);
}
bool OI::xbox1_x(){
	return xbox1.GetRawButton(3);
}
bool OI::xbox1_y(){
	return xbox1.GetRawButton(4);
}
bool OI::xbox1_lB(){
	return xbox1.GetRawButton(5);
}
bool OI::xbox1_rB(){
	return xbox1.GetRawButton(6);
}
bool OI::xbox1_select(){
	return xbox1.GetRawButton(7);
}
bool OI::xbox1_start(){
	return xbox1.GetRawButton(8);
}
bool OI::xbox1_lClick(){
	return xbox1.GetRawButton(9);
}
bool OI::xbox1_rClick(){
	return xbox1.GetRawButton(10);
}
bool OI::xbox1_lT(){
	return (xbox1.GetRawAxis(2)>.10);
}
bool OI::xbox1_rT(){
	return (xbox1.GetRawAxis(3)>.10);
}

//Controller 2-----------------------------------------------------------------------------------------------
float OI::xbox2_x1(){
	return xbox2.GetRawAxis(0);
}
float OI::xbox2_y1(){
	return xbox2.GetRawAxis(1);
}
float OI::xbox2_lTVal(){
	return xbox2.GetRawAxis(2);
}
float OI::xbox2_rTVal(){
	return xbox2.GetRawAxis(3);
}
float OI::xbox2_x2(){
	return xbox2.GetRawAxis(4);
}
float OI::xbox2_y2(){
	return xbox2.GetRawAxis(5);
}
bool OI::xbox2_a(){
	return xbox2.GetRawButton(1);
}
bool OI::xbox2_b(){
	return xbox2.GetRawButton(2);
}
bool OI::xbox2_x(){
	return xbox2.GetRawButton(3);
}
bool OI::xbox2_y(){
	return xbox2.GetRawButton(4);
}
bool OI::xbox2_lB(){
	return xbox2.GetRawButton(5);
}
bool OI::xbox2_rB(){
	return xbox2.GetRawButton(6);
}
bool OI::xbox2_select(){
	return xbox2.GetRawButton(7);
}
bool OI::xbox2_start(){
	return xbox2.GetRawButton(8);
}
bool OI::xbox2_lClick(){
	return xbox2.GetRawButton(9);
}
bool OI::xbox2_rClick(){
	return xbox2.GetRawButton(10);
}
bool OI::xbox2_lT(){
	return (xbox2.GetRawAxis(2)>.15);
}
bool OI::xbox2_rT(){
	return (xbox2.GetRawAxis(3)>.15);
}
