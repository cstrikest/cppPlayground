#include "bmp.h"

Bmp::Bmp(BF_TYPE type, int width, int height, Image img)
{
	__header.bfType = type;
	__header.bfSize = width * height * 3 + 64;
	__header.bfOffBits = 64;

	__info.biSize = 48;
	__info.biWidth = width;
	__info.biHeight = height;
	__info.biSizeImage = width * height * 3;
}

Image createImage(int width, int height)
{
	Image image(height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
	return image;
}

void fillColor(simple_line& l)
{
	for (int j = 0; j < 50; j++)
	{
		for (int c = 0; c < 3; c++)
		{
			l[0][j][c] = 255;
		}
	}
}

void fillColor(Image& image)
{
	for (auto& i : image)
	{
		for (auto& j : i)
		{
			for (auto& c : j) c = 255;
		}
	}
}
