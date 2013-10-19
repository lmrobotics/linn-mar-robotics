#include <iostream>
#include <string>
#include "dataParserClass.h"
using namespace std;

// our main
int main(int argc, char* argv[])
{
   if (argc > 1)
   {
   dataParserClass *dp = new dataParserClass(argv[1]);
   dp->parseDoublesReversed();
   return 0;
   }
   else {
      dataParserClass *dp = new dataParserClass("U:\\dataParser\\byteSwappedFloats.bin");
      dp->parseDoublesReversed();
      return 0;
   }
}

