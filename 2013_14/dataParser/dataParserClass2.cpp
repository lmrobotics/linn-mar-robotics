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
	
	   file.read(reinterpret_cast<char *>(&myfloat), sizeof(myfloat));
	   if (file.gcount()==sizeof(myfloat))
	   {
	      cout << myfloat << endl;
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