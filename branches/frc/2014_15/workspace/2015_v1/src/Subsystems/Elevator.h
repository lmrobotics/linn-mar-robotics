#ifndef elevator_H
#define elevator_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Elevator: public Subsystem
{
private:

	Victor armMotorR;
	Victor armMotorL;
	Victor conveyorMotor;

	DoubleSolenoid winchShifter;
	DoubleSolenoid magShifter;
	DoubleSolenoid armShifter;
	DoubleSolenoid winchBrake;

	//Encoder elevatorEncoder;


	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Victor winchMotor;

	Elevator(uint32_t winchChannel, uint32_t armLChannel, uint32_t armRChannel, uint32_t conveyorChannel,
			uint8_t pneumaticsModuleNumber, uint32_t winchShiftForwardChannel, uint32_t winchShiftReverseChannel,
			uint32_t magShiftForwardChannel, uint32_t magShiftReverseChannel,
			uint32_t armShiftForwardChannel, uint32_t armShiftReverseChannel,
			uint8_t pneumaticsModuleNumber2, uint32_t winchBrakeForwardChannel, uint32_t winchBrakeReverseChannel);

	~Elevator();

	void InitDefaultCommand();

	void openMagazine();
	void closeMagazine();
	bool isMagazineOpen();
	void shiftMagazine();

	void setElevator(double power);
	void highGearElevator();
	void lowGearElevator();
	void shiftElevatorGear();
	bool isElevatorHighGear();
	void brakeElevator();
	void unbrakeElevator();

	void openArms();
	void closeArms();
	void shiftArms();
	bool isArmsOpen();
	void setRollers(double power);
	void setLRollers(double power);
	void setRRollers(double power);

	void setConveyor(double power);
};

#endif
