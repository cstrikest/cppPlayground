#include "bmp.h"

Bmp::Bmp(BF_TYPE type, int width, int height, Image img)
{
	__header.bfType = type;
	__header.bfSize = width*height*3+64;
	__header.bfOffBits = 64;

	__info.biSize = 48;
	__info.biWidth = width;
	__info.biHeight = height;
	__info.biSizeImage = width * height * 3;
}
