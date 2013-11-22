#ifndef FILE_STREAM_H_
#define FILE_STREAM_H_

//Make the compiler shut up about depriciation
//Also remove when included into robot
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Standard typedefs for data types
//Remove when included into robot
typedef unsigned int UINT32;
typedef int INT32;

//file modes
#define R "r"
#define W "w"
#define A "a"
#define RW_BEGINNING "r+"
#define RW_OVERWRITE "w+"
#define RW_APPEND "a+"

//Seek bases
#define BEGINNING SEEK_SET
#define CURRENT_POS SEEK_CURR
#define END SEEK_END

//exception handling
#define SUCCESS 0
#define FAILURE 1

class FileStream
{
private:
	FILE* file;
	bool openedFile;
public:
	//Basic constructor
	FileStream()
	{
		file = NULL;
		openedFile = false;
	}
	//Open a file with the constructor
	FileStream(char* fileName, const char* fileMode)
	{
		file = fopen(fileName, fileMode);
		if(file != NULL)
			openedFile = true;
		else
			openedFile = false;
	}
	//Close file if user forgot to
	~FileStream(void)
	{
		if(openedFile)
			fclose(file);
	}

	//Open a file.  Will fail if a file is already open
	bool Open(char* fileName, const char* fileMode);
	//Reopen a file.  Will close a file if it is already open
	bool ReOpen(char* fileName, const char* fileMode);
	//Close a file.  Will fail if no file is open
	bool Close(void);

	//Write booleans
	bool WriteBool(bool *data);
	//Read booleans
	bool ReadBool(bool *data);
	//Write integers
	bool WriteUINT32(UINT32 *data);
	bool WriteINT32(INT32 *data);
	//Read integers
	bool ReadUINT32(UINT32 *data);
	bool ReadINT32(INT32 *data);
	//Write floating-point integers
	bool WriteFloat(float *data);
	bool WriteDouble(double *data);
	//Read floating-point integers
	bool ReadFloat(float *data);
	bool ReadDouble(double *data);

	//Generic read and write
	bool Write(void* data, size_t dataItemSize, size_t itemCount);
	bool Read(void* data, size_t dataItemSize, size_t itemCount);

	//Seek in file
	//TODO:  see if I should use INT32 or int for robot implementation
	bool Seek(int basePoint, INT64 offset);

	//flush file
	bool Flush(void);

	//Return if error is in existance
	bool IsError(void);

	//Return if file is open or not
	bool IsFileOpen(void);
	
	//Return current offset from beginning.  Return -1L if failure
	INT64 CurrentPos(void);
};

//Delete file
bool DeleteFile(const char* fileName);

#endif
