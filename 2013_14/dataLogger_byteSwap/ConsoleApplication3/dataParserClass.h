// dataParserClass.h

#include <fstream>
#include <string>
using namespace std;

class dataParserClass
{
public:
	dataParserClass (string fileName);
	~dataParserClass ();
private:
	ifstream file;
}; // class dataLogger
