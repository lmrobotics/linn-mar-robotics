/*----------------------------------------------------------------------------*/
/* Copyright (c) Kauai Labs. All Rights Reserved.							  */
/*                                                                            */
/* Created in support of Team 2465 (Kauaibots).  Go Thunderchicken!           */
/*                                                                            */
/* Based upon the Open Source WPI Library released by FIRST robotics.         */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef IMU_H_
#define IMU_H_

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// needed for base types
// todo: get a more global base message types w/o having to use namespace Messages
#include "../arduino/BaseMessageClass.h"
using namespace Messages;

/**
 * Use the IMU to retrieve a Yaw/Pitch/Roll measurement.
 * 
 * This utilizes the Kauai Labs Nav6 IMU.
 * 
 * This IMU interfaces to the CRio processor via a Serial port.
 */

#define YAW_HISTORY_LENGTH 10

class IMU
{
protected:
    QSerialPort serial;
    IMU( uint8 update_rate_hz, char stream_type );
    void InternalInit( uint8 update_rate_hz, char stream_type );
public:

    IMU( uint8 update_rate_hz = 100 );
	virtual ~IMU();
	virtual float GetPitch();	// Pitch, in units of degrees (-180 to 180)
	virtual float GetRoll();	// Roll, in units of degrees (-180 to 180)
	virtual float GetYaw();		// Yaw, in units of degrees (-180 to 180)
	virtual float GetCompassHeading(); // CompassHeading, in units of degrees (0 to 360)
	
	bool IsConnected();
	void ZeroYaw();
	
	void SetYawPitchRoll(float yaw, float pitch, float roll, float compass_heading);
	void SetStreamResponse( char stream_type, 
                            uint16 gyro_fsr_dps, uint16 accel_fsr_g, uint16 update_rate_hz,
							float yaw_offset_degrees, 
                            uint16 q1_offset, uint16 q2_offset, uint16 q3_offset, uint16 q4_offset,
                            uint16 flags );
	double GetYawOffset() { return yaw_offset; }
	double GetByteCount();
	double GetUpdateCount();
	void Restart();
	bool  IsCalibrating();

    uint8 update_rate_hz;
	char current_stream_type;
	virtual int DecodePacketHandler( char *received_data, int bytes_remaining );

    QSerialPort *serialPort;
    void processRxData();

private:
	void InitializeYawHistory();
	double GetAverageFromYawHistory();
	void InitIMU();
    void initSerial();
    bool stream_response_received;
    bool stop;

protected:

	void UpdateYawHistory(float curr_yaw );
	
//	Task *	m_task;
	float 	yaw;
	float 	pitch; 
	float 	roll;
	float   compass_heading;
	float 	yaw_history[YAW_HISTORY_LENGTH];
	int 	next_yaw_history_index;
	double 	last_update_time;
	double 	yaw_offset;
	float   yaw_offset_degrees;
    uint16 accel_fsr_g;
    uint16 gyro_fsr_dps;
    uint16 flags;
};
#endif
