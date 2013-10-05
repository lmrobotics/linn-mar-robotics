// This is the main DLL file.

#include "dataLogger.h"
#include "ioLib.h"

dataLogger::dataLogger (const char* fileName)
{
	fd = open(fileName, O_WRONLY, 777);
}

dataLogger::~dataLogger ()
{
	close(fd);
}


void dataLogger::write_(int value)
{
	write(fd, reinterpret_cast<char *>(&value), (size_t)sizeof(value));
}

void dataLogger::write_(float value)
{
	write(fd, reinterpret_cast<char *>(&value), (size_t)sizeof(value));
}

void dataLogger::write_(double value)
{
	write(fd, reinterpret_cast<char *>(&value), (size_t)sizeof(value));
}
