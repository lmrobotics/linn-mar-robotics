/*
 * MyPID.h
 *
 *  Created on: Mar 16, 2015
 *      Author: FRC_2013
 */

#include "WPILib.h"
#include <iostream>
#include <cstdio>
#include <ctime>

#ifndef SRC_MYPID_H_
#define SRC_MYPID_H_

class MyPID {
public:
	MyPID(double p, double i, double d, PIDSource *source);
	virtual ~MyPID();
	void calculate();
	double get();
	void enable();
	void disable();
	void reset();
	void setP(double p);
	void setI(double i);
	void setD(double d);
	void setTarget(double target);
	double getP();
	double getI();
	double getD();
	double getTarget();
	bool isEnabled();
private:
	double p;
	double i;
	double d;
	double correction;
	double lastError;
	double history;
	double target;
	PIDSource *input;
	std::clock_t lastCalc;
	bool enabled;
};

#endif /* SRC_MYPID_H_ */
