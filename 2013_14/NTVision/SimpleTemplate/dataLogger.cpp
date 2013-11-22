// This is the main DLL file.

#include "dataLogger.h"
#include "ioLib.h"


dataLogger::dataLogger (const char* fileName): buffer(0)
{
	fd = fopen(fileName, "w");
	buffer = new char[buffer_size]();
	buffer_index = 0;
}

dataLogger::~dataLogger ()
{
}


void dataLogger::write_float(float value)
{
    if((buffer_index + sizeof(value)) <= buffer_size) 
    {
	   memcpy(&buffer[buffer_index], (void*)&value, sizeof(value));
	   buffer_index += sizeof(value);
    }
}

void dataLogger::close_()
{
	fwrite(buffer, 1, buffer_index, fd);
	fclose(fd);
}
