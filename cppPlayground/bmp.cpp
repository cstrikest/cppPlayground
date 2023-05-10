#include "bmp.h"

Bmp::Bmp(BF_TYPE type, int width, int height, TripleRGB* surface)
{
	__info.biWidth = width;
	__info.biHeight = height;
	setRowOffset();
	__header.bfType = type;
	__header.bfSize = (width * 3 + __row_offset) * height + __header.bfOffBits;
	__info.biSizeImage = (width * 3 + __row_offset) * height;

	__surface = new TripleRGB[width * height];

	*__surface = *surface;
}

Bmp::Bmp(BF_TYPE type, int width, int height, TripleRGB color)
{
	__info.biWidth = width;
	__info.biHeight = height;
	setRowOffset();
	__header.bfType = type;
	__header.bfSize = (width * 3 + __row_offset) * height + __header.bfOffBits;
	__info.biSizeImage = (width * 3 + __row_offset) * height;

	__surface = new TripleRGB[width * height];

	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			*(__surface + (row * width + column)) = color;
		}
	}
}

Bmp::Bmp(BF_TYPE type, const char* path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	ifs.read((char*)&__header, sizeof(BmpFileHeader));
	ifs.read((char*)&__info, sizeof(BmpInfoHeader));
	__surface = new TripleRGB[__info.biWidth * __info.biHeight];
	for (int row = 0; row < __info.biHeight; row++)
	{
		for (int column = 0; column < __info.biWidth; column++)
		{
			ifs.read((char*)(__surface + (row * __info.biWidth + column)), sizeof(TripleRGB));
		}
	}
}

Bmp::Bmp (const Bmp& bmp): __header(bmp.__header), __info(bmp.__info), __row_offset(bmp.__row_offset)
{
	__surface = new TripleRGB[__info.biWidth * __info.biHeight];
}

void Bmp::fillColor(TripleRGB color)
{
	for (int row = 0; row < __info.biHeight; row++)
	{
		for (int column = 0; column < __info.biWidth; column++)
		{
			*(__surface + (row * __info.biWidth + column)) = color;
		}
	}
}

void Bmp::setRowOffset()
{
	__row_offset = (__info.biWidth * 3) % 4;
	if (__row_offset != 0) __row_offset = 4 - __row_offset;
}

void Bmp::writeBmpFile(const char* path)
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	ofs.write((char*)&__header, sizeof(BmpFileHeader));
	ofs.write((char*)&__info, sizeof(BmpInfoHeader));

	for (int row = 0; row < __info.biHeight; row++)
	{
			for (int column = 0; column < __info.biWidth; column++)
		{
			ofs.write((char*)(__surface + (row * __info.biWidth + column)), 3);
		}
		for (int t = __row_offset; t > 0; t--)
		{
			ofs.write(ZERO_CHAR, 1);
		}
	}
	ofs.flush();
	ofs.close();
}

