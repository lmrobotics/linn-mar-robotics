// This is the main DLL file.

#include "dataLogger.h"
#include "ioLib.h"

dataLogger::dataLogger (const char* fileName)
{
	fd = fopen(fileName, "w");
}

dataLogger::~dataLogger ()
{
	fclose(fd);
}

void dataLogger::close_()
{
	fclose(fd);
}

void dataLogger::write_float(float value)
{
	char* temp=(char*)(&value);
	fwrite(temp, 1, sizeof(value), fd);
}
