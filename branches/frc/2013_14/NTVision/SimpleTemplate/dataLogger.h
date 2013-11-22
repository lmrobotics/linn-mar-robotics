// dataLogger.h
#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <fstream>
#include <string>
using namespace std;


class dataLogger
{
public:
	dataLogger (const char* fileName);
	~dataLogger ();
	void write_float(float value);
	void close_();
private:
	// file descriptor
	FILE * fd;
	char* buffer;
	int buffer_index;
	static const int buffer_size = 16*1024;
}; // class dataLogger

#endif
