#pragma once
#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<int>[3]> Image;

class FileReader
{

};

class BmpReader : FileReader
{

};

enum BF_TYPE
{
	BM = 0x4d42,	//Windows3+ ,NT
	BA = 0x4142,	//OS/2	Bitmap Array
	CI = 0x4943,	//		Color Icon
	CP = 0x5043,	//		Color pointer
	IC = 0x4349,	//		Icon
	PT = 0x5450		//		Pointer
};

struct BmpFileHeader
{
	unsigned short bfType;
	unsigned int bfSize;
	const unsigned short bfReserved1 = 0;
	const unsigned short bfReserved2 = 0;
	unsigned int bfOffBits;
};

struct BmpInfoHeader
{
	unsigned int biSize;
	int biWidth;
	int biHeight;
	const unsigned short biPlanes = 1;
	unsigned short biBitCount = 24;
	unsigned int biCompression = 0;
	unsigned int biSizeImage;
	int biXPelsPerMeter = 300; // 说明水平分辨率，用象素/米表示。一般为0 (38-41字节)
	int biYPelsPerMeter = 300; // 说明垂直分辨率，用象素/米表示。一般为0 (42-45字节)
	unsigned int    biClrUsed = 0;       // 说明位图实际使用的彩色表中的颜色索引数。 (46-49字节)
	unsigned int    biClrImportant = 0;  // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。(50-53字节)

};

class Bmp
{
private:
	BmpFileHeader __header;
	BmpInfoHeader __info;
	char* __data;

public:
	Bmp(BF_TYPE type, int width, int height, Image img);
	~Bmp() {};
	int const getSize();
	int const getWidth();
	int const getHeight();
};
//https://blog.csdn.net/m0_62505136/article/details/121153508
