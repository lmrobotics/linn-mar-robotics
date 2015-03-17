#include "OI.h"

OI::OI() :
		xbox1(0), board(1), xbox2(2), hiLoSwitchUnTapped(false) {
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
		tappedArrayXbox1[0] = false;
	}
	return xbox1.GetRawButton(1);
}
bool OI::xbox1_b() {
	if (!xbox1.GetRawButton(2)) {
		tappedArrayXbox1[1] = false;
	}
	return xbox1.GetRawButton(2);
}
bool OI::xbox1_x() {
	if (!xbox1.GetRawButton(3)) {
		tappedArrayXbox1[2] = false;
	}
	return xbox1.GetRawButton(3);
}
bool OI::xbox1_y() {
	if (!xbox1.GetRawButton(4)) {
		tappedArrayXbox1[3] = false;
	}
	return xbox1.GetRawButton(4);
}
bool OI::xbox1_lB() {
	if (!xbox1.GetRawButton(5)) {
		tappedArrayXbox1[4] = false;
	}
	return xbox1.GetRawButton(5);
}
bool OI::xbox1_rB() {
	if (!xbox1.GetRawButton(6)) {
		tappedArrayXbox1[5] = false;
	}
	return xbox1.GetRawButton(6);
}
bool OI::xbox1_select() {
	if (!xbox1.GetRawButton(7)) {
		tappedArrayXbox1[6] = false;
	}
	return xbox1.GetRawButton(7);
}
bool OI::xbox1_start() {
	if (!xbox1.GetRawButton(8)) {
		tappedArrayXbox1[7] = false;
	}
	return xbox1.GetRawButton(8);
}
bool OI::xbox1_lClick() {
	if (!xbox1.GetRawButton(9)) {
		tappedArrayXbox1[8] = false;
	}
	return xbox1.GetRawButton(9);
}
bool OI::xbox1_rClick() {
	if (!xbox1.GetRawButton(10)) {
		tappedArrayXbox1[9] = false;
	}
	return xbox1.GetRawButton(10);
}
bool OI::xbox1_lT() {
	if ((xbox1.GetRawAxis(2) <= .50)) {
		tappedArrayXbox1[10] = false;
	}
	return (xbox1.GetRawAxis(2) > .50);
}
bool OI::xbox1_rT() {
	if ((xbox1.GetRawAxis(3) <= .50)) {
		tappedArrayXbox1[11] = false;
	}
	return (xbox1.GetRawAxis(3) > .50);
}

bool OI::xbox1_aTapped() {
	if (!xbox1.GetRawButton(1)) {
		tappedArrayXbox1[0] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[0]) {
			tappedArrayXbox1[0] = true;
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
		tappedArrayXbox1[1] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[1]) {
			tappedArrayXbox1[1] = true;
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
		tappedArrayXbox1[2] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[2]) {
			tappedArrayXbox1[2] = true;
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
		tappedArrayXbox1[3] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[3]) {
			tappedArrayXbox1[3] = true;
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
		tappedArrayXbox1[4] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[4]) {
			tappedArrayXbox1[4] = true;
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
		tappedArrayXbox1[5] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[5]) {
			tappedArrayXbox1[5] = true;
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
		tappedArrayXbox1[6] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[6]) {
			tappedArrayXbox1[6] = true;
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
		tappedArrayXbox1[7] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[7]) {
			tappedArrayXbox1[7] = true;
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
		tappedArrayXbox1[8] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[8]) {
			tappedArrayXbox1[8] = true;
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
		tappedArrayXbox1[9] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[9]) {
			tappedArrayXbox1[9] = true;
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
		tappedArrayXbox1[10] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[10]) {
			tappedArrayXbox1[10] = true;
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
		tappedArrayXbox1[11] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox1[11]) {
			tappedArrayXbox1[11] = true;
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
		tappedArrayXbox2[0] = false;
	}
	return xbox2.GetRawButton(1);
}
bool OI::xbox2_b() {
	if (!xbox2.GetRawButton(2)) {
		tappedArrayXbox2[1] = false;
	}
	return xbox2.GetRawButton(2);
}
bool OI::xbox2_x() {
	if (!xbox2.GetRawButton(3)) {
		tappedArrayXbox2[2] = false;
	}
	return xbox2.GetRawButton(3);
}
bool OI::xbox2_y() {
	if (!xbox2.GetRawButton(4)) {
		tappedArrayXbox2[3] = false;
	}
	return xbox2.GetRawButton(4);
}
bool OI::xbox2_lB() {
	if (!xbox2.GetRawButton(5)) {
		tappedArrayXbox2[4] = false;
	}
	return xbox2.GetRawButton(5);
}
bool OI::xbox2_rB() {
	if (!xbox2.GetRawButton(6)) {
		tappedArrayXbox2[5] = false;
	}
	return xbox2.GetRawButton(6);
}
bool OI::xbox2_select() {
	if (!xbox2.GetRawButton(7)) {
		tappedArrayXbox2[6] = false;
	}
	return xbox2.GetRawButton(7);
}
bool OI::xbox2_start() {
	if (!xbox2.GetRawButton(8)) {
		tappedArrayXbox2[7] = false;
	}
	return xbox2.GetRawButton(8);
}
bool OI::xbox2_lClick() {
	if (!xbox2.GetRawButton(9)) {
		tappedArrayXbox2[8] = false;
	}
	return xbox2.GetRawButton(9);
}
bool OI::xbox2_rClick() {
	if (!xbox2.GetRawButton(10)) {
		tappedArrayXbox2[9] = false;
	}
	return xbox2.GetRawButton(10);
}
bool OI::xbox2_lT() {
	if ((xbox2.GetRawAxis(2) <= .50)) {
		tappedArrayXbox2[10] = false;
	}
	return (xbox2.GetRawAxis(2) > .50);
}
bool OI::xbox2_rT() {
	if ((xbox2.GetRawAxis(3) <= .50)) {
		tappedArrayXbox2[11] = false;
	}
	return (xbox2.GetRawAxis(3) > .50);
}

bool OI::xbox2_aTapped() {
	if (!xbox2.GetRawButton(1)) {
		tappedArrayXbox2[0] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[0]) {
			tappedArrayXbox2[0] = true;
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
		tappedArrayXbox2[1] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[1]) {
			tappedArrayXbox2[1] = true;
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
		tappedArrayXbox2[2] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[2]) {
			tappedArrayXbox2[2] = true;
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
		tappedArrayXbox2[3] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[3]) {
			tappedArrayXbox2[3] = true;
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
		tappedArrayXbox2[4] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[4]) {
			tappedArrayXbox2[4] = true;
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
		tappedArrayXbox2[5] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[5]) {
			tappedArrayXbox2[5] = true;
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
		tappedArrayXbox2[6] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[6]) {
			tappedArrayXbox2[6] = true;
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
		tappedArrayXbox2[7] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[7]) {
			tappedArrayXbox2[7] = true;
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
		tappedArrayXbox2[8] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[8]) {
			tappedArrayXbox2[8] = true;
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
		tappedArrayXbox2[9] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[9]) {
			tappedArrayXbox2[9] = true;
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
		tappedArrayXbox2[10] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[10]) {
			tappedArrayXbox2[10] = true;
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
		tappedArrayXbox2[11] = false;
		return false;
	}
	else {
		if (!tappedArrayXbox2[11]) {
			tappedArrayXbox2[11] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}


bool OI::board_1() {
	if (!board.GetRawButton(1)) {
		tappedArrayXbox2[0] = false;
	}
	return xbox2.GetRawButton(1);
}
bool OI::board_2() {
	if (!board.GetRawButton(2)) {
		tappedArrayBoard[1] = false;
	}
	return board.GetRawButton(2);
}
bool OI::board_3() {
	if (!board.GetRawButton(3)) {
		tappedArrayBoard[2] = false;
	}
	return board.GetRawButton(3);
}
bool OI::board_4() {
	if (!board.GetRawButton(4)) {
		tappedArrayBoard[3] = false;
	}
	return board.GetRawButton(4);
}
bool OI::board_5() {
	if (!board.GetRawButton(5)) {
		tappedArrayBoard[4] = false;
	}
	return board.GetRawButton(5);
}
bool OI::board_bigRed() {
	if (!board.GetRawButton(6)) {
		tappedArrayBoard[5] = false;
	}
	return board.GetRawButton(6);
}
bool OI::board_lilGreen() {
	if (!board.GetRawButton(7)) {
		tappedArrayBoard[6] = false;
	}
	return board.GetRawButton(7);
}
bool OI::board_hiLoSwitch() {
	if (!board.GetRawButton(8)) {
		tappedArrayBoard[7] = false;
		return false;
	}
	else {
		hiLoSwitchUnTapped = false;
		return true;
	}
}
bool OI::board_up() {
	if (!board.GetRawButton(9)) {
		tappedArrayBoard[8] = false;
	}
	return board.GetRawButton(9);
}
bool OI::board_down() {
	if (!board.GetRawButton(10)) {
		tappedArrayBoard[9] = false;
	}
	return board.GetRawButton(10);
}
bool OI::board_in() {
	if (!board.GetRawButton(11)) {
		tappedArrayBoard[10] = false;
	}
	return board.GetRawButton(11);
}
bool OI::board_out() {
	if (!board.GetRawButton(12)) {
		tappedArrayBoard[11] = false;
	}
	return board.GetRawButton(12);
}

bool OI::board_1Tapped() {
	if (!board.GetRawButton(1)) {
		tappedArrayBoard[0] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[0]) {
			tappedArrayBoard[0] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_2Tapped() {
	if (!board.GetRawButton(2)) {
		tappedArrayBoard[1] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[1]) {
			tappedArrayBoard[1] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_3Tapped() {
	if (!board.GetRawButton(3)) {
		tappedArrayBoard[2] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[2]) {
			tappedArrayBoard[2] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_4Tapped() {
	if (!board.GetRawButton(4)) {
		tappedArrayBoard[3] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[3]) {
			tappedArrayBoard[3] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_5Tapped() {
	if (!board.GetRawButton(5)) {
		tappedArrayBoard[4] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[4]) {
			tappedArrayBoard[4] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_bigRedTapped() {
	if (!board.GetRawButton(6)) {
		tappedArrayBoard[5] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[5]) {
			tappedArrayBoard[5] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_lilGreenTapped() {
	if (!board.GetRawButton(7)) {
		tappedArrayBoard[6] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[6]) {
			tappedArrayBoard[6] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_hiLoSwitchTapped() {
	if (!board.GetRawButton(8)) {
		tappedArrayBoard[7] = false;
		return false;
	}
	else {
		hiLoSwitchUnTapped=false;
		if (!tappedArrayBoard[7]) {
			tappedArrayBoard[7] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_hiLoSwitchUnTapped() {
	if (!board.GetRawButton(8)) {
		tappedArrayBoard[7] = false;
		if (!hiLoSwitchUnTapped){
			hiLoSwitchUnTapped=true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		hiLoSwitchUnTapped=false;
		return false;
	}
	return false;
}
bool OI::board_upTapped() {
	if (!board.GetRawButton(9)) {
		tappedArrayBoard[8] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[8]) {
			tappedArrayBoard[8] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_downTapped() {
	if (!board.GetRawButton(10)) {
		tappedArrayBoard[9] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[9]) {
			tappedArrayBoard[9] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_inTapped() {
	if (!board.GetRawButton(11)) {
		tappedArrayBoard[10] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[10]) {
			tappedArrayBoard[10] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool OI::board_outTapped() {
	if (!board.GetRawButton(12)) {
		tappedArrayBoard[11] = false;
		return false;
	}
	else {
		if (!tappedArrayBoard[11]) {
			tappedArrayBoard[11] = true;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
