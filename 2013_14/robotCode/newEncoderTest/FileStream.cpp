#include "FileStream.h"

bool FileStream::Open(char* fileName, const char* fileMode)
{
	//Fail if a file is already open
	if(openedFile)
		return FAILURE;

	file = fopen(fileName, fileMode);
	if(file == NULL)
		return FAILURE;
	else
	{
		openedFile = true;
		return SUCCESS;
	}
}

bool FileStream::ReOpen(char* fileName, const char* fileMode)
{
	//use reopen function
	file = freopen(fileName, fileMode, file);
	if(file == NULL)
	{
		openedFile = false;
		return FAILURE;
	}
	else
	{
		openedFile = true;
		return SUCCESS;
	}
}

bool FileStream::Close(void)
{
	//Fail if there is no open file
	if(!openedFile)
		return FAILURE;

	if(fclose(file) == 0)
	{
		openedFile = false;
		return SUCCESS;
	}
	else
	{
		openedFile = false;
		return FAILURE;
	}
}

bool FileStream::WriteBool(bool *data)
{
	if(fwrite(data, sizeof(bool), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::ReadBool(bool *data)
{
	if(fread(data, sizeof(bool), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::WriteUINT32(UINT32 *data)
{
	if(fwrite(data, sizeof(UINT32), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::WriteINT32(INT32 *data)
{
	if(fwrite(data, sizeof(INT32), 1, file) != 1)
		return FAILURE;
	else 
		return SUCCESS;
}

bool FileStream::ReadUINT32(UINT32 *data)
{
	if(fread(data, sizeof(UINT32), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::ReadINT32(INT32 *data)
{
	if(fread(data, sizeof(INT32), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::WriteFloat(float *data)
{
	if(fwrite(data, sizeof(float), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::WriteDouble(double *data)
{
	if(fwrite(data, sizeof(double), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::ReadFloat(float *data)
{
	if(fread(data, sizeof(float), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::ReadDouble(double *data)
{
	if(fread(data, sizeof(double), 1, file) != 1)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::Write(void *data, size_t dataItemSize, size_t itemCount)
{
	if(fwrite(data, dataItemSize, itemCount, file) != itemCount)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::Read(void *data, size_t dataItemSize, size_t itemCount)
{
	if(fread(data, dataItemSize, itemCount, file) != itemCount)
		return FAILURE;
	else
		return SUCCESS;
}

bool FileStream::Seek(int basePoint, INT64 offset)
{
	if(fseek(file, offset, basePoint) == 0)
		return SUCCESS;
	else
		return FAILURE;
}

bool FileStream::Flush(void)
{
	if(fflush(file) == 0)
		return SUCCESS;
	else
		return FAILURE;
}

bool FileStream::IsError(void)
{
	if(ferror(file) == 0)
		return false;
	else
		return true;
}

bool FileStream::IsFileOpen()
{
	return openedFile;
}

INT64 FileStream::CurrentPos(void)
{
	return ftell(file);
}

bool DeleteFile(const char* FileName)
{
	if(remove(FileName) == 0)
		return SUCCESS;
	else
		return FAILURE;
}
