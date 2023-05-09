#include "stack.h"
#include "bmp.h"

int main()
{
	//runStack();
	Bmp i(BM, 63, 30, Color(55, 62, 124));
	i.fillColor(Color(255, 0, 0));
	
	i.writeBmpFile("C:\\Users\\0070200621\\Desktop\\a.bmp");
	return 0;
}

