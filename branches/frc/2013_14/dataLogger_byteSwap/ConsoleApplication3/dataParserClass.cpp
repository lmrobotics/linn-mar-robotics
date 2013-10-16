// This is the main DLL file.

#include <iostream>
#include <string>
#include "dataParserClass.h"

dataParserClass::dataParserClass (string fileName):
file(fileName, ifstream::binary)
{
	float myfloat;
	while (!file.eof())
	{
	   
       char readBytes[sizeof(float)];
       char swappedBytes[sizeof(float)];

       file.read(readBytes, sizeof(float));
	   if (file) {

	   for (int i=0; i<sizeof(float); i++)
	   {
	     swappedBytes[sizeof(float) - i] = readBytes[i];
       }
	   memcpy(&myfloat, swappedBytes, sizeof(myfloat));
	   cout << myfloat << endl;
	   }
	   else {
		   cout <<"fail to read file" ;
		   return ;
	   }
	}
}

dataParserClass::~dataParserClass ()
{
	file.close();
}

void writefloat(float v, FILE *f) {
	fwrite((void*)(&v), sizeof(v), 1, f);
}

float readfloat(FILE *f) {
	float v;
	fread((void*)(&v), sizeof(v), 1, f);
	return v;
}