#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick xbox1, xbox2;
public:
	OI();

	float xbox1_y1();
	float xbox1_y2();
	float xbox1_x1();
	float xbox1_x2();
	float xbox1_rTVal();
	float xbox1_lTVal();
	bool xbox1_a();
	bool xbox1_b();
	bool xbox1_x();
	bool xbox1_y();
	bool xbox1_rB();
	bool xbox1_lB();
	bool xbox1_rT();
	bool xbox1_lT();
	bool xbox1_select();
	bool xbox1_start();
	bool xbox1_lClick();
	bool xbox1_rClick();

	float xbox2_y1();
	float xbox2_y2();
	float xbox2_x1();
	float xbox2_x2();
	float xbox2_rTVal();
	float xbox2_lTVal();
	bool xbox2_a();
	bool xbox2_b();
	bool xbox2_x();
	bool xbox2_y();
	bool xbox2_rB();
	bool xbox2_lB();
	bool xbox2_rT();
	bool xbox2_lT();
	bool xbox2_select();
	bool xbox2_start();
	bool xbox2_lClick();
	bool xbox2_rClick();
};

#endif
