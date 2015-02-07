#ifndef IMUPROCESS_H_
#define IMUPROCESS_H_

#define ROLL_HISTORY_LENGTH 10
#define PITCH_HISTORY_LENGTH 10

#include "IMUAdvanced.h"
#include "WPILib.h"

class IMUProcess : public IMUAdvanced{
	//friend class IMU;
	//friend class IMUAdvanced;
public:
	IMUProcess(SerialPort *pport, uint8_t update_rate_hz);
	~IMUProcess(void);
	
	virtual float GetPitch();       // Pitch, in units of degrees (-180 to 180)
	virtual float GetRoll();        // Roll, in units of degrees (-180 to 180)
	
	virtual double GetFilteredYaw();
	virtual double GetFilteredPitch();
	virtual double GetFilteredRoll();

	void ResetYawRollPitch(void);
	virtual int DecodePacketHandler( char *received_data, int bytes_remaining );
protected:
	void UpdateRollHistory(float curr_Roll);
	void UpdatePitchHistory(float curr_Pitch);
	
	double roll_offset;
	double pitch_offset;
	
	int next_roll_history_index;
	int next_pitch_history_index;
	
	float roll_history[ROLL_HISTORY_LENGTH];
	float pitch_history[PITCH_HISTORY_LENGTH];
private:
	double GetAverageFromPitchHistory();
	double GetAverageFromRollHistory();
};

#endif
