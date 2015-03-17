/*
 * MyPID.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: FRC_2013
 */

#include <MyPID.h>

MyPID::MyPID(double p, double i, double d, PIDSource *source) {
	this->p=p;
	this->i=i;
	this->d=d;
	input = source;
	lastCalc=std::clock();
	enabled=false;
	lastError=0;
	target=0;
	history=0;
	correction=0;
}

MyPID::~MyPID() {

}

void MyPID::calculate(){
	double sourceVal=input->PIDGet();
	double error=target-sourceVal;
	if (enabled){
		history+=(error*(3.0*(double)(std::clock() - lastCalc) / (double) CLOCKS_PER_SEC));
		correction= p*(error)+
				i*(history)+
				d*((error-lastError)/3.0*(double)(std::clock() - lastCalc) / (double) CLOCKS_PER_SEC);
	}
	lastCalc=std::clock();
	lastError=error;
}
double MyPID::get(){
	if (enabled){
		calculate();
		return correction;
	}
	else {
		return false;
	}
}
void MyPID::enable(){
	enabled=true;
	reset();
}
void MyPID::disable(){
	enabled=false;
}
void MyPID::reset(){
	lastCalc=std::clock();
	lastError=0;
	history=0;
	correction=0;
}

void MyPID::setP(double p){
	this->p=p;
}
void MyPID::setI(double i){
	this->i=i;
}
void MyPID::setD(double d){
	this->d=d;
}
void MyPID::setTarget(double target){
	this->target=target;
}

double MyPID::getP(){
	return p;
}
double MyPID::getI(){
	return i;
}
double MyPID::getD(){
	return d;
}
double MyPID::getTarget(){
	return target;
}
bool MyPID::isEnabled(){
	return enabled;
}
