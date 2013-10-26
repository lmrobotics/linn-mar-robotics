// dataParserClass.h

#include <fstream>
#include <string>
using namespace std;

class dataParserClass
{
public:
	dataParserClass (string fileName);
	~dataParserClass ();
	void parseFloats();
	void parseFloatsReversed(int columns);
	void parseDoublesReversed();
private:
	ifstream file;
}; // class dataLogger
