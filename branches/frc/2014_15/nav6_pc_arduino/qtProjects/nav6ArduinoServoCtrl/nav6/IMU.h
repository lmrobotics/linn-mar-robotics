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
#include <QTime>
#include <qsemaphore.h>

typedef signed char int8_t;         /* 8 bit signed */
typedef unsigned char uint8_t;      /* 8 bit unsigned */
typedef short int16_t;              /* 16 bit signed */
typedef unsigned short uint16_t;    /* 16 bit unsigned */
typedef int int32_t;                /* 32 bit signed */
typedef unsigned int uint32_t;      /* 32 bit unsigned */

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
    IMU( uint8_t update_rate_hz, char stream_type );
    void InternalInit( uint8_t update_rate_hz, char stream_type );
public:

    IMU( uint8_t update_rate_hz = 100 );
	virtual ~IMU();
	virtual float GetPitch();	// Pitch, in units of degrees (-180 to 180)
	virtual float GetRoll();	// Roll, in units of degrees (-180 to 180)
	virtual float GetYaw();		// Yaw, in units of degrees (-180 to 180)
	virtual float GetCompassHeading(); // CompassHeading, in units of degrees (0 to 360)
	
	bool IsConnected();
	void ZeroYaw();
	
	void SetYawPitchRoll(float yaw, float pitch, float roll, float compass_heading);
    void SetStreamResponse(uint16_t gyro_fsr_dps, uint16_t accel_fsr, uint16_t update_rate_hz, float yaw_offset_degrees, uint16_t flags );
    double GetYawOffset() { return yaw_offset; }
	double GetUpdateCount();
	void Restart();
	bool  IsCalibrating();

    uint8_t update_rate_hz;
	char current_stream_type;
	virtual int DecodePacketHandler( char *received_data, int bytes_remaining );

    QSerialPort *serialPort;
    void processRxData();

private:
	void InitializeYawHistory();
	double GetAverageFromYawHistory();
	void InitIMU();
    void initSerial();
    float qtime();
    bool stream_response_received;
    bool stop;
    QTime *timer;
    QSemaphore *cIMUStateSemaphore;

    char protocol_buffer[1024];
    char temp_buffer[1024];
    int serialBufferIndex;
    float lastStreamResponseTime;

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
    uint16_t accel_fsr_g;
    uint16_t gyro_fsr_dps;
    uint16_t flags;
};
#endif
