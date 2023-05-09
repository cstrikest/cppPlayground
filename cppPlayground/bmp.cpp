#include "bmp.h"

Bmp::Bmp(BF_TYPE type, Image img)
{
	__info.biWidth = img[0].size();
	__info.biHeight = img.size();
	setRowOffset();
	__header.bfType = type;
	__header.bfSize = __row_offset* __info.biHeight * 3 + 64;
	__header.bfOffBits = 64;

	__info.biSize = 48;
	__info.biSizeImage = __row_offset * __info.biHeight * 3;
}

Bmp::Bmp(BF_TYPE type, int width, int height)
{
	__info.biWidth = width;
	__info.biHeight = height;
	__header.bfType = type;
	__header.bfSize = width * height * 3 + 64;
	__header.bfOffBits = 64;

	__info.biSize = 48;
	__info.biSizeImage = width * height * 3;

	Image image(height, std::vector<Color>(width, Color(255,255,255)));
}

void Bmp::fillColor(Color& color)
{
	for (auto& i : __image)
	{
		for (auto& j : i)
		{
			j.setColor(color);
		}
	}
}

void Bmp::setRowOffset()
{
	__row_offset = (__info.biWidth * 3) % 4;
	if (__row_offset != 0) __row_offset = 4 - __row_offset;
}
