#include "stack.h"
#include "bmp.h"
#include "colors.h"

int main()
{
	//runStack();
	try
	{
		//打开一个bmp，随便画画线，写到新文件
		Bmp bmp(bmp_type::BM, "C:\\Users\\0070200621\\Desktop\\b.bmp");
		for (int i = bmp.getWidth() - 1; i >= 0; --i)
		{
			*bmp(i, 0) = Color::GREEN;
		}
		for (int i = bmp.getHeight() - 1; i >= 0; --i)
		{
			*bmp(0, i) = Color::BLUE;
		}
		bmp.writeBmpFile("C:\\Users\\0070200621\\Desktop\\c.bmp");

		//新建一个空白bmp 随便画画
		Bmp mosaic(bmp_type::BM, 1920, 1080, Color::WHITE);
		for (int i = mosaic.getWidth() - 1; i >= 0; --i)
		{
			if (i % 2 == 0)
			{
				for (int j = mosaic.getHeight() - 1; j >= 0; --j)
				{
					if (i % 3 == 0) *mosaic(i, j) = Color::RED;
					else if (i % 4 == 0) *mosaic(i, j) = Color::BLUE;
					else *mosaic(i, j) = Color::GREEN;
				}
			}
		}
		mosaic.writeBmpFile("C:\\Users\\0070200621\\Desktop\\s.bmp");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
