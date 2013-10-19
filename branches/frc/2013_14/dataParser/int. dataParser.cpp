// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "string"

	int _tmain(int argc, _TCHAR* argv[])
{
		int a;
	while (!file.eof())
	{
	
	file.read(reinterpret_cast<char *>(&a), sizeof(a));
	cout << a << endl;
	}
}
	void writeint(int v, FILE *f) {
  fwrite((void*)(&v), sizeof(v), 1, f);
}

int readint(FILE *f) {
  int v;
  fread((void*)(&v), sizeof(v), 1, f);
  return v;
}
