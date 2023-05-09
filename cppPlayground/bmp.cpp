#include "bmp.h"

Bmp::Bmp(BF_TYPE type, Image img)
{
	__info.biWidth = img[0].size();
	__info.biHeight = img.size();
	setRowOffset();
	__header.bfType = type;
	__header.bfSize = (__info.biWidth * 3 + __row_offset) * __info.biHeight + __header.bfOffBits;
	__info.biSizeImage = (__info.biWidth * 3 + __row_offset) * __info.biHeight;
	__image = img;
}

Bmp::Bmp(BF_TYPE type, int width, int height, Color default_color)
{
	__info.biWidth = width;
	__info.biHeight = height;
	setRowOffset();
	__header.bfType = type;
	__header.bfSize = (__info.biWidth * 3 + __row_offset) * __info.biHeight + __header.bfOffBits;
	__info.biSizeImage = (__info.biWidth * 3 + __row_offset) * __info.biHeight;
	__image = Image(height, std::vector<Color>(width, default_color));
}

void Bmp::fillColor(Color color)
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

void Bmp::writeBmpFile(const char* path)
{
	std::ofstream ofs;
	ofs.open(path, std::ios::binary | std::ios::out);
	ofs.write((char*)&__header, sizeof(BmpFileHeader));
	ofs.write((char*)&__info, sizeof(BmpInfoHeader));

	const char* zero = "";
	for (auto& i : __image)
	{
		for (auto& j : i)
		{
			ofs.write((char*)&(j.__R), 1);
			ofs.write((char*)&(j.__G), 1);
			ofs.write((char*)&(j.__B), 1);
		}
		for (int t = __row_offset; t > 0; t--)
		{
			ofs.write(zero, 1);
		}
	}
	ofs.flush();
	ofs.close();
}
