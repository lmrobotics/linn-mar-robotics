#include <iostream>
#include <string>
#include "dataParserClass.h"
using namespace std;

// our main
int main(int argc, char* argv[])
{
	int numColumns = 1;
	if (argc > 2)
	{
		try
		{
			numColumns = stoi(argv[2]);
		}
		catch (exception e)
		{
			cout << "Error: " << e.what();
		}
	}

   if (argc > 1)
   {
   dataParserClass *dp = new dataParserClass(argv[1]);
   dp->parseFloatsReversed(numColumns);
   return 0;
   }
   else {

      dataParserClass *dp = new dataParserClass("U:\\dataParser\\byteSwappedFloats.bin");
      dp->parseFloatsReversed(numColumns);
      return 0;
   }
}

