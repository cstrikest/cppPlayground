#include "stack.h"
#include "bmp.h"

int main()
{
	//runStack();
	std::ifstream ifs;
	ifs.open("C:\\Users\\0070200621\\Desktop\\a.bmp", std::ios::binary | std::ios::in);
	for (int i = 0x0; i < 0x35;i++)
	std::cout << ifs.get() << std::endl;
	ifs.close();
	ifs.open("C:\\Users\\0070200621\\Desktop\\a.bmp", std::ios::binary | std::ios::in);
	ifs.close();
	return 0;
}

