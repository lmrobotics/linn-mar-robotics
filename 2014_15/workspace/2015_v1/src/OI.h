#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick xbox1, xbox2;
public:
	OI();

	//If a button is pressed down, a "tapped" function will return true only the first time it is called
	//After that, it will return false until the button is no longer pressed down, in which case it will reset
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
	bool xbox1_aTapped();
	bool xbox1_bTapped();
	bool xbox1_xTapped();
	bool xbox1_yTapped();
	bool xbox1_rBTapped();
	bool xbox1_lBTapped();
	bool xbox1_rTTapped();
	bool xbox1_lTTapped();
	bool xbox1_selectTapped();
	bool xbox1_startTapped();
	bool xbox1_lClickTapped();
	bool xbox1_rClickTapped();


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
	bool xbox2_aTapped();
	bool xbox2_bTapped();
	bool xbox2_xTapped();
	bool xbox2_yTapped();
	bool xbox2_rBTapped();
	bool xbox2_lBTapped();
	bool xbox2_rTTapped();
	bool xbox2_lTTapped();
	bool xbox2_selectTapped();
	bool xbox2_startTapped();
	bool xbox2_lClickTapped();
	bool xbox2_rClickTapped();

private:
	bool tappedArray1[12]{false,false,false,false,false,false,false,false,false,false,false,false};
	bool tappedArray2[12]{false,false,false,false,false,false,false,false,false,false,false,false};
};

#endif
