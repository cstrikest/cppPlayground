#include "stack.h"
#include "bmp.h"
#include "colors.h"

int main()
{
	//runStack();
	auto p = "C:\\Users\\0070200621\\Desktop\\a.bmp";
	auto b = "C:\\Users\\0070200621\\Desktop\\b.bmp";
	auto c = "C:\\Users\\0070200621\\Desktop\\c.bmp";
	Bmp i(BM, 1243, 10, SAKURA);
	i.writeBmpFile(p);
	Bmp r(BM,b);
	std::cout <<r.getPixelNumber() << std::endl << r.getRowOffset() << std::endl;
	r.writeBmpFile(c);
	return 0;
}
