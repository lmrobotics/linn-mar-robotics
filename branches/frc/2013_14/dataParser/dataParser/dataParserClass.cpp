// This is the main DLL file.

#include <iostream>
#include <string>
#include "dataParserClass.h"

dataParserClass::dataParserClass (string fileName):
file(fileName, ifstream::binary)
{
	
}

dataParserClass::~dataParserClass ()
{
	file.close();
}

void dataParserClass::parseDoublesReversed ()
{
	double myfloat;
	while (!file.eof())
	{
	   
       char readBytes[sizeof(double)];
       char swappedBytes[sizeof(double)];

       file.read(readBytes, sizeof(double));
	   if (file.gcount()==sizeof(myfloat)) {

	   for (int i=0; i<sizeof(double); i++)
	   {
	     swappedBytes[sizeof(double) - 1 - i] = readBytes[i];
       }
	   memcpy(&myfloat, swappedBytes, sizeof(myfloat));
	   cout << myfloat << endl;
	   }
	   else { 
		   return ;
	   }
	}
}
void dataParserClass::parseFloatsReversed (int numColumns)
{
	float myfloat;
	int currentColumn = 0;
	while (!file.eof())
	{
	   
       char readBytes[sizeof(float)];
       char swappedBytes[sizeof(float)];

       file.read(readBytes, sizeof(float));
	   if (file.gcount()==sizeof(myfloat)) {

		   for (int i=0; i<sizeof(float); i++)
		   {
			 swappedBytes[sizeof(float) - 1 - i] = readBytes[i];
		   }
		   memcpy(&myfloat, swappedBytes, sizeof(myfloat));
		   cout << myfloat << ", ";
		   currentColumn++;
		   if (currentColumn>=numColumns)
		   {
			   currentColumn = 0;
			   cout << endl;
		   }
	   } // if read succesful
	   else { 
		   return ;
	   }

	}
}

void dataParserClass::parseFloats()
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