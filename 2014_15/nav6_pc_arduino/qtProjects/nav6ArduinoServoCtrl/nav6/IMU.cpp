/*----------------------------------------------------------------------------*/
/* Copyright (c) Kauai Labs. All Rights Reserved.							  */
/*                                                                            */
/* Created in support of Team 2465 (Kauaibots).  Go Thunderchicken!           */
/*                                                                            */
/* Based upon the Open Source WPI Library released by FIRST robotics.         */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include <time.h>
#include <qdebug.h>
#include <qthread.h>
#include "IMU.h"
#include "IMUProtocol.h"

void IMU::initSerial()
{
    serialPort = new QSerialPort();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       if(info.description().contains("Prolific"))
       {
          serialPort->setPort(info);
          qDebug() << "Attempting to open Nav 6 serial Port";
          qDebug() << "Name        : " << info.portName();
          qDebug() << "Description : " << info.description();
          qDebug() << "Manufacturer: " << info.manufacturer();

          if (!serialPort->setBaudRate(QSerialPort::Baud57600) ||
              !serialPort->setDataBits(QSerialPort::Data8) ||
              !serialPort->setParity(QSerialPort::NoParity) ||
              !serialPort->setStopBits(QSerialPort::OneStop) ||
              !serialPort->setFlowControl(QSerialPort::NoFlowControl))
          {
              qDebug() << "Failed to configure serial port";
          }
          else
          {
              qDebug() << "serial configure worked!";
          }
          //serialPort->close();
          serialPort->open(QIODevice::ReadWrite);
       }
    }

    if (!serialPort->isOpen())
    {
        qDebug() << "Serial port not opened :(";
    }
    else
    {
        qDebug() << "Serial port is opened :)";
        serialPort->setDataTerminalReady(true);
        serialPort->setReadBufferSize(1024);
    }

}

float IMU::qtime()
{
    QTime temp = timer->currentTime();
    return (float)temp.msec()/1000.0 + (float)(temp.second() + temp.minute()*60 + temp.hour()*60*60);
}

void IMU::processRxData()
{    
    uint32_t bytes_read = 0;
    uint16_t bytes_processed = 0;
    uint16_t readIndex = 0;

    bytes_read = serialPort->read(temp_buffer, 1024);

    while  (bytes_processed < bytes_read)
    {
        if(temp_buffer[readIndex] == '!')
        {
            serialBufferIndex = 0;
            memset(protocol_buffer, 0, 1024);
        }
        protocol_buffer[serialBufferIndex++] = temp_buffer[readIndex++];
        bytes_processed++;
        if(temp_buffer[readIndex-1] == '\n')
        {
            int packet_length = DecodePacketHandler(protocol_buffer, serialBufferIndex);
            if ( packet_length > 0 )
            {
                lastStreamResponseTime = qtime();
            }
            else
            {
                char stream_type_r;
                uint16_t gyro_fsr_dps_r, accel_fsr_r, update_rate_hz_r;
                uint16_t q1_offset_r, q2_offset_r, q3_offset_r, q4_offset_r;
                float yaw_offset_degrees_r;
                uint16_t flags_r;
                packet_length = IMUProtocol::decodeStreamResponse( protocol_buffer, serialBufferIndex, stream_type_r,
                          gyro_fsr_dps_r, accel_fsr_r, update_rate_hz_r,
                          yaw_offset_degrees_r,
                          q1_offset_r, q2_offset_r, q3_offset_r, q4_offset_r,
                          flags_r );
                if ( packet_length > 0 )
                {
                    SetStreamResponse(gyro_fsr_dps_r, accel_fsr_r, update_rate_hz_r,
                              yaw_offset_degrees_r,
                              flags_r );
                    lastStreamResponseTime = qtime();
                }
            }
            serialBufferIndex = 0;
        }
    }

    // reconnect if communication was lost
    if (( qtime() - lastStreamResponseTime ) > 3.0) {
        int cmd_packet_length = IMUProtocol::encodeStreamCommand( protocol_buffer, current_stream_type, update_rate_hz );
        lastStreamResponseTime = qtime();
        serialPort->write(protocol_buffer, cmd_packet_length);
        serialPort->waitForBytesWritten(-1);
    }
}

int IMU::DecodePacketHandler( char *received_data, int bytes_remaining ) {
	
	float yaw = 0.0;
	float pitch = 0.0;
	float roll = 0.0;
	float compass_heading = 0.0;		

	int packet_length = IMUProtocol::decodeYPRUpdate( received_data, bytes_remaining, yaw, pitch, roll, compass_heading ); 
	if ( packet_length > 0 )
	{
		SetYawPitchRoll(yaw,pitch,roll,compass_heading);
	}
	return packet_length;
}

void IMU::InternalInit( uint8_t update_rate_hz, char stream_type ) {
	current_stream_type = stream_type;
	yaw_offset_degrees = 0;
	accel_fsr_g = 2;
	gyro_fsr_dps = 2000;
	flags = 0;
	this->update_rate_hz = update_rate_hz;
	yaw = 0.0;
    pitch = 0.0;
	roll = 0.0;
    cIMUStateSemaphore = new QSemaphore (1);
    timer = new QTime();
    timer->start();

    stream_response_received = false;
    stop = false;
    serialBufferIndex = 0;
    initSerial();

    InitIMU();

    lastStreamResponseTime = qtime();
}

IMU::IMU(uint8_t update_rate_hz, char stream_type ) {
   InternalInit(update_rate_hz,stream_type);
}

IMU::IMU(uint8_t update_rate_hz )
{
   InternalInit(update_rate_hz,STREAM_CMD_STREAM_TYPE_YPR);
}

/**
 * Initialize the IMU.
 */
void IMU::InitIMU()
{
 
 InitializeYawHistory();
    yaw_offset = 0;

    int packet_length = IMUProtocol::encodeStreamCommand( protocol_buffer, current_stream_type, update_rate_hz );
    serialPort->write(protocol_buffer, packet_length );
    serialPort->waitForBytesWritten(-1);
}

/**
 * Delete the IMU.
 */
IMU::~IMU()
{

}

bool IMU::IsConnected()
{
    double time_since_last_update = qtime() - last_update_time;
    return time_since_last_update <= 1.0;
}

bool IMU::IsCalibrating()
{
    cIMUStateSemaphore->acquire();
    uint16_t calibration_state = this->flags & NAV6_FLAG_MASK_CALIBRATION_STATE;
    cIMUStateSemaphore->release();
    return (calibration_state != NAV6_CALIBRATION_STATE_COMPLETE);
}

void IMU::ZeroYaw()
{
	yaw_offset = GetAverageFromYawHistory();
}


/**
 * Return the yaw angle in degrees.
 * 
 * This angle increases as the robot spins to the right.
 * 
 * This angle ranges from -180 to 180 degrees.
 */
float IMU::GetYaw( void )
{
    cIMUStateSemaphore->acquire();
    double yaw = this->yaw;
	yaw -= yaw_offset;
	if ( yaw < -180 ) yaw += 360;
	if ( yaw > 180 ) yaw -= 360;
    cIMUStateSemaphore->release();
    return yaw;
}

float IMU::GetPitch( void )
{
	return this->pitch;
}

float IMU::GetRoll( void )
{
	return this->roll;
}

float IMU::GetCompassHeading( void )
{
	return this->compass_heading;
}

void IMU::SetYawPitchRoll(float yaw, float pitch, float roll, float compass_heading)
{
	{
        cIMUStateSemaphore->acquire();

		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
		this->compass_heading = compass_heading;
        cIMUStateSemaphore->release();
    }
	UpdateYawHistory(this->yaw);
}

void IMU::InitializeYawHistory()
{
	memset(yaw_history,0,sizeof(yaw_history));
	next_yaw_history_index = 0;
	last_update_time = 0.0;
}

void IMU::UpdateYawHistory(float curr_yaw )
{
	if ( next_yaw_history_index >= YAW_HISTORY_LENGTH )
	{
		next_yaw_history_index = 0;
	}
	yaw_history[next_yaw_history_index] = curr_yaw;
    last_update_time = qtime();
	next_yaw_history_index++;
}

double IMU::GetAverageFromYawHistory()
{
    cIMUStateSemaphore->acquire();
    double yaw_history_sum = 0.0;
	for ( int i = 0; i < YAW_HISTORY_LENGTH; i++ )
	{
		yaw_history_sum += yaw_history[i];
	}	
	double yaw_history_avg = yaw_history_sum / YAW_HISTORY_LENGTH;
    cIMUStateSemaphore->release();
    return yaw_history_avg;
}

void IMU::SetStreamResponse(uint16_t gyro_fsr_dps, uint16_t accel_fsr, uint16_t update_rate_hz, float yaw_offset_degrees, uint16_t flags)
{
	{
        cIMUStateSemaphore->acquire();
        this->yaw_offset_degrees = yaw_offset_degrees;
		this->flags = flags;
		this->accel_fsr_g = accel_fsr;
		this->gyro_fsr_dps = gyro_fsr_dps;
		this->update_rate_hz = update_rate_hz;
        cIMUStateSemaphore->release();
    }
}


