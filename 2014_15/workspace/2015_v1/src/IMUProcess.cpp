#include "IMUProcess.h"

//static SEM_ID cIMUStateSemaphore = semBCreate (SEM_Q_PRIORITY, SEM_FULL);  

IMUProcess::IMUProcess( SerialPort *pport, uint8_t update_rate_hz = 100 ) : IMUAdvanced(pport, update_rate_hz){

	memset(roll_history,0,sizeof(roll_history));
	next_roll_history_index = 0;
	
	memset(pitch_history,0,sizeof(pitch_history));
	next_pitch_history_index = 0;
}

float IMUProcess::GetPitch(){

	//Synchronized sync(cIMUStateSemaphore);
	double pitch = this->pitch;
	pitch = pitch - (float)pitch_offset;
	/*if ( pitch < -180 ) pitch += 360;
	if ( pitch > 180 ) pitch -= 360;*/
	return pitch;
}

float IMUProcess::GetRoll(){
	
	//Synchronized sync(cIMUStateSemaphore);
	double roll = this->roll;
	roll = roll - (float)roll_offset;
	/*if ( roll < -180 ) roll += 360;
	if ( roll > 180 ) roll -= 360;*/
	return roll;
}

double IMUProcess::GetFilteredYaw(){
	//TODO: Actually write this. GetYaw is being used as a placeholder
	return GetYaw();
}

double IMUProcess::GetFilteredPitch(){
	//TODO: Actually write this. GetPitch is being used as a placeholder
	return GetPitch();
}

double IMUProcess::GetFilteredRoll(){
	//TODO: Actually write this. GetRoll is being used as a placeholder
	return GetRoll();
}

void IMUProcess::ResetYawRollPitch(){

	ZeroYaw();
	roll_offset = GetAverageFromRollHistory();
	pitch_offset = GetAverageFromPitchHistory();
}

double IMUProcess::GetAverageFromPitchHistory(){
	
	//Synchronized sync(cIMUStateSemaphore);
	double pitch_history_sum = 0.0;
	for ( int i = 0; i < PITCH_HISTORY_LENGTH; i++ )
	{
		pitch_history_sum += pitch_history[i];
	}       
	double pitch_history_avg = pitch_history_sum / PITCH_HISTORY_LENGTH;
	return pitch_history_avg;
}

double IMUProcess::GetAverageFromRollHistory(){

	//Synchronized sync(cIMUStateSemaphore);
	double roll_history_sum = 0.0;
	for ( int i = 0; i < ROLL_HISTORY_LENGTH; i++ )
	{
		roll_history_sum += roll_history[i];
	}       
	double roll_history_avg = roll_history_sum / ROLL_HISTORY_LENGTH;
	return roll_history_avg;
}

int IMUProcess::DecodePacketHandler( char *received_data, int bytes_remaining ){

	int packet_length = IMUAdvanced::DecodePacketHandler(received_data,bytes_remaining);

	UpdatePitchHistory(this->pitch);
	UpdateRollHistory(this->roll);
	UpdateYawHistory(this->yaw);
	
	return packet_length;
}

void IMUProcess::UpdatePitchHistory(float curr_Pitch){

	if ( next_pitch_history_index >= YAW_HISTORY_LENGTH )
	{
		next_pitch_history_index = 0;
	}
	pitch_history[next_pitch_history_index] = curr_Pitch;
	next_pitch_history_index++;
	
	//printf("pitch offset %f", pitch_offset);
}

void IMUProcess::UpdateRollHistory(float curr_Roll){

	if ( next_roll_history_index >= ROLL_HISTORY_LENGTH )
	{
		next_roll_history_index = 0;
	}
	roll_history[next_roll_history_index] = curr_Roll;
	next_roll_history_index++;
	
	//printf("roll offset %f", roll_offset);
}

IMUProcess::~IMUProcess(){
	
}
