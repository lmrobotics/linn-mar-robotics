// dataLogger.h

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <fstream>
#include <string>
using namespace std;


class dataLogger
{
public:
	dataLogger (const char* fileName);
	~dataLogger ();
	void close_();
	void write_(const char* value);
	void write_(float value);
	void write_(double value);
private:
	// file descriptor
	FILE * fd;
}; // class dataLogger

#endif
