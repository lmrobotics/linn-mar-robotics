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

void dataLogger::write_(const char* value)
{
	fprintf(fd, value);
}
