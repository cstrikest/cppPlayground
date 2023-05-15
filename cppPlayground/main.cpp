#include "stack.h"
#include "bmp.h"
#include "colors.h"
#include "image_func.h"

using namespace image_func;

int main()
{
	//runStack();
	try
	{
		Bmp t("b.bmp");
		t.getImageBgr24b() >> chaos;
		t.save("s.bmp");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
