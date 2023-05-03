#include "bmp.h"

int readBmp(const char* path)
{
	std::ifstream r;
	r.open(path, std::ios::in);
	char* data = new char[1000];
	r >> data;
	std::cout << data << std::endl;
	delete[] data;
	return 0;
}

