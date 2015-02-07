#include "OI.h"

OI::OI() :
		xbox1(0), xbox2(1) {
}

float OI::xbox1_x1() {
	return xbox1.GetRawAxis(0);
}
float OI::xbox1_y1() {
	return xbox1.GetRawAxis(1);
}
float OI::xbox1_lTVal() {
	return xbox1.GetRawAxis(2);
}
float OI::xbox1_rTVal() {
	return xbox1.GetRawAxis(3);
}
float OI::xbox1_x2() {
	return xbox1.GetRawAxis(4);
}
float OI::xbox1_y2() {
	return xbox1.GetRawAxis(5);
}

bool OI::xbox1_a() {
	if (!xbox1.GetRawButton(1)) {
		tappedArray1[0] = false;
	}
	return xbox1.GetRawButton(1);
}
bool OI::xbox1_b() {
	if (!xbox1.GetRawButton(2)) {
		tappedArray1[1] = false;
	}
	return xbox1.GetRawButton(2);
}
bool OI::xbox1_x() {
	if (!xbox1.GetRawButton(3)) {
		tappedArray1[2] = false;
	}
	return xbox1.GetRawButton(3);
}
bool OI::xbox1_y() {
	if (!xbox1.GetRawButton(4)) {
		tappedArray1[3] = false;
	}
	return xbox1.GetRawButton(4);
}
bool OI::xbox1_lB() {
	if (!xbox1.GetRawButton(5)) {
		tappedArray1[4] = false;
	}
	return xbox1.GetRawButton(5);
}
bool OI::xbox1_rB() {
	if (!xbox1.GetRawButton(6)) {
		tappedArray1[5] = false;
	}
	return xbox1.GetRawButton(6);
}
bool OI::xbox1_select() {
	if (!xbox1.GetRawButton(7)) {
		tappedArray1[6] = false;
	}
	return xbox1.GetRawButton(7);
}
bool OI::xbox1_start() {
	if (!xbox1.GetRawButton(8)) {
		tappedArray1[7] = false;
	}
	return xbox1.GetRawButton(8);
}
bool OI::xbox1_lClick() {
	if (!xbox1.GetRawButton(9)) {
		tappedArray1[8] = false;
	}
	return xbox1.GetRawButton(9);
}
bool OI::xbox1_rClick() {
	if (!xbox1.GetRawButton(10)) {
		tappedArray1[9] = false;
	}
	return xbox1.GetRawButton(10);
}
bool OI::xbox1_lT() {
	if ((xbox1.GetRawAxis(2) <= .50)) {
		tappedArray1[10] = false;
	}
	return (xbox1.GetRawAxis(2) > .50);
}
bool OI::xbox1_rT() {
	if ((xbox1.GetRawAxis(3) <= .50)) {
		tappedArray1[11] = false;
	}
	return (xbox1.GetRawAxis(3) > .50);
}

bool OI::xbox1_aTapped() {
	if (!xbox1.GetRawButton(1)) {
		tappedArray1[0] = false;
		return false;
	}
	else {
		if (!tappedArray1[0]) {
			tappedArray1[0] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_bTapped() {
	if (!xbox1.GetRawButton(2)) {
		tappedArray1[1] = false;
		return false;
	}
	else {
		if (!tappedArray1[1]) {
			tappedArray1[1] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_xTapped() {
	if (!xbox1.GetRawButton(3)) {
		tappedArray1[2] = false;
		return false;
	}
	else {
		if (!tappedArray1[2]) {
			tappedArray1[2] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_yTapped() {
	if (!xbox1.GetRawButton(4)) {
		tappedArray1[3] = false;
		return false;
	}
	else {
		if (!tappedArray1[3]) {
			tappedArray1[3] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_lBTapped() {
	if (!xbox1.GetRawButton(5)) {
		tappedArray1[4] = false;
		return false;
	}
	else {
		if (!tappedArray1[4]) {
			tappedArray1[4] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_rBTapped() {
	if (!xbox1.GetRawButton(6)) {
		tappedArray1[5] = false;
		return false;
	}
	else {
		if (!tappedArray1[5]) {
			tappedArray1[5] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_selectTapped() {
	if (!xbox1.GetRawButton(7)) {
		tappedArray1[6] = false;
		return false;
	}
	else {
		if (!tappedArray1[6]) {
			tappedArray1[6] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_startTapped() {
	if (!xbox1.GetRawButton(8)) {
		tappedArray1[7] = false;
		return false;
	}
	else {
		if (!tappedArray1[7]) {
			tappedArray1[7] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_lClickTapped() {
	if (!xbox1.GetRawButton(9)) {
		tappedArray1[8] = false;
		return false;
	}
	else {
		if (!tappedArray1[8]) {
			tappedArray1[8] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_rClickTapped() {
	if (!xbox1.GetRawButton(10)) {
		tappedArray1[9] = false;
		return false;
	}
	else {
		if (!tappedArray1[9]) {
			tappedArray1[9] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_lTTapped() {
	if ((xbox1.GetRawAxis(2) <= .50)) {
		tappedArray1[10] = false;
		return false;
	}
	else {
		if (!tappedArray1[10]) {
			tappedArray1[10] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox1_rTTapped() {
	if ((xbox1.GetRawAxis(3) <= .50)) {
		tappedArray1[11] = false;
		return false;
	}
	else {
		if (!tappedArray1[11]) {
			tappedArray1[11] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

//Controller 2-----------------------------------------------------------------------------------------------
float OI::xbox2_x1() {
	return xbox2.GetRawAxis(0);
}
float OI::xbox2_y1() {
	return xbox2.GetRawAxis(1);
}
float OI::xbox2_lTVal() {
	return xbox2.GetRawAxis(2);
}
float OI::xbox2_rTVal() {
	return xbox2.GetRawAxis(3);
}
float OI::xbox2_x2() {
	return xbox2.GetRawAxis(4);
}
float OI::xbox2_y2() {
	return xbox2.GetRawAxis(5);
}

bool OI::xbox2_a() {
	if (!xbox2.GetRawButton(1)) {
		tappedArray1[0] = false;
	}
	return xbox2.GetRawButton(1);
}
bool OI::xbox2_b() {
	if (!xbox2.GetRawButton(2)) {
		tappedArray1[1] = false;
	}
	return xbox2.GetRawButton(2);
}
bool OI::xbox2_x() {
	if (!xbox2.GetRawButton(3)) {
		tappedArray1[2] = false;
	}
	return xbox2.GetRawButton(3);
}
bool OI::xbox2_y() {
	if (!xbox2.GetRawButton(4)) {
		tappedArray1[3] = false;
	}
	return xbox2.GetRawButton(4);
}
bool OI::xbox2_lB() {
	if (!xbox2.GetRawButton(5)) {
		tappedArray1[4] = false;
	}
	return xbox2.GetRawButton(5);
}
bool OI::xbox2_rB() {
	if (!xbox2.GetRawButton(6)) {
		tappedArray1[5] = false;
	}
	return xbox2.GetRawButton(6);
}
bool OI::xbox2_select() {
	if (!xbox2.GetRawButton(7)) {
		tappedArray1[6] = false;
	}
	return xbox2.GetRawButton(7);
}
bool OI::xbox2_start() {
	if (!xbox2.GetRawButton(8)) {
		tappedArray1[7] = false;
	}
	return xbox2.GetRawButton(8);
}
bool OI::xbox2_lClick() {
	if (!xbox2.GetRawButton(9)) {
		tappedArray1[8] = false;
	}
	return xbox2.GetRawButton(9);
}
bool OI::xbox2_rClick() {
	if (!xbox2.GetRawButton(10)) {
		tappedArray1[9] = false;
	}
	return xbox2.GetRawButton(10);
}
bool OI::xbox2_lT() {
	if ((xbox2.GetRawAxis(2) <= .50)) {
		tappedArray1[10] = false;
	}
	return (xbox2.GetRawAxis(2) > .50);
}
bool OI::xbox2_rT() {
	if ((xbox2.GetRawAxis(3) <= .50)) {
		tappedArray1[11] = false;
	}
	return (xbox2.GetRawAxis(3) > .50);
}

bool OI::xbox2_aTapped() {
	if (!xbox2.GetRawButton(1)) {
		tappedArray1[0] = false;
		return false;
	}
	else {
		if (!tappedArray1[0]) {
			tappedArray1[0] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_bTapped() {
	if (!xbox2.GetRawButton(2)) {
		tappedArray1[1] = false;
		return false;
	}
	else {
		if (!tappedArray1[1]) {
			tappedArray1[1] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_xTapped() {
	if (!xbox2.GetRawButton(3)) {
		tappedArray1[2] = false;
		return false;
	}
	else {
		if (!tappedArray1[2]) {
			tappedArray1[2] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_yTapped() {
	if (!xbox2.GetRawButton(4)) {
		tappedArray1[3] = false;
		return false;
	}
	else {
		if (!tappedArray1[3]) {
			tappedArray1[3] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_lBTapped() {
	if (!xbox2.GetRawButton(5)) {
		tappedArray1[4] = false;
		return false;
	}
	else {
		if (!tappedArray1[4]) {
			tappedArray1[4] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_rBTapped() {
	if (!xbox2.GetRawButton(6)) {
		tappedArray1[5] = false;
		return false;
	}
	else {
		if (!tappedArray1[5]) {
			tappedArray1[5] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_selectTapped() {
	if (!xbox2.GetRawButton(7)) {
		tappedArray1[6] = false;
		return false;
	}
	else {
		if (!tappedArray1[6]) {
			tappedArray1[6] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_startTapped() {
	if (!xbox2.GetRawButton(8)) {
		tappedArray1[7] = false;
		return false;
	}
	else {
		if (!tappedArray1[7]) {
			tappedArray1[7] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_lClickTapped() {
	if (!xbox2.GetRawButton(9)) {
		tappedArray1[8] = false;
		return false;
	}
	else {
		if (!tappedArray1[8]) {
			tappedArray1[8] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_rClickTapped() {
	if (!xbox2.GetRawButton(10)) {
		tappedArray1[9] = false;
		return false;
	}
	else {
		if (!tappedArray1[9]) {
			tappedArray1[9] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_lTTapped() {
	if ((xbox2.GetRawAxis(2) <= .50)) {
		tappedArray1[10] = false;
		return false;
	}
	else {
		if (!tappedArray1[10]) {
			tappedArray1[10] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::xbox2_rTTapped() {
	if ((xbox2.GetRawAxis(3) <= .50)) {
		tappedArray1[11] = false;
		return false;
	}
	else {
		if (!tappedArray1[11]) {
			tappedArray1[11] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
