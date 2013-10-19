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
	void parseFloatsReversed();
	void parseDoublesReversed();
private:
	ifstream file;
}; // class dataLogger
