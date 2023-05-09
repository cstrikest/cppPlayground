#pragma once
//#pragma once 和 #ifndef #define 的作用确实是防止一个头文件在同一个源文件中被多次包含。
//然而，这并不能解决链接时的重复符号问题，因为这个问题是由多个源文件包含同一个头文件导致的。
//在这种情况下，虽然每个源文件都只包含一份头文件的内容，但是当链接器将所有源文件链接在一起时，
//它会发现有多个相同的符号定义，从而导致重复符号错误。

//各种防止重复包含的方法是防止同一个源文件包含多个相同的头文件（间接重复包含）
//不是防止多个源文件包含同一个。毕竟头文件用途就是为了让多个源文件去包含他。
//所以在头文件定义了非成员函数之后，会出现符号错误。
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>

enum BF_TYPE
{
	BM = 0x4d42,	//Windows3+ ,NT
	BA = 0x4142,	//OS/2	Bitmap Array
	CI = 0x4943,	//		Color Icon
	CP = 0x5043,	//		Color pointer
	IC = 0x4349,	//		Icon
	PT = 0x5450		//		Pointer
};

// 按照2字节对齐
#pragma pack(2)
struct BmpFileHeader
{
	unsigned short bfType;
	unsigned int bfSize;
	const unsigned short bfReserved1 = 0;
	const unsigned short bfReserved2 = 0;
	unsigned int bfOffBits = 54;
};

#pragma pack(4)
struct BmpInfoHeader
{
	unsigned int biSize = 40;
	int biWidth;
	int biHeight;
	const unsigned short biPlanes = 1;
	unsigned short biBitCount = 24;
	unsigned int biCompression = 0;
	unsigned int biSizeImage;
	int biXPelsPerMeter = 300;
	int biYPelsPerMeter = 300;
	unsigned int    biClrUsed = 0;
	unsigned int    biClrImportant = 0;

};
#pragma pack()

class Color
{
public:
	unsigned char __R;
	unsigned char __G;
	unsigned char __B;
	inline Color(int r, int g, int b) : __R(r), __G(g), __B(b) {}
	inline Color(const Color& color)
	{
		__R = color.__R;
		__G = color.__G;
		__B = color.__B;
	}
	inline void setColor(int r, int g, int b) { __R = r; __G = g; __B = b; }
	inline void setColor(Color& color)
	{
		__R = color.__R;
		__G = color.__G;
		__B = color.__B;
	}
};

typedef std::vector<std::vector<Color>> Image;

class Bmp
{
private:
	BmpFileHeader __header;
	BmpInfoHeader __info;
	Image __image;
	unsigned int __row_offset;

public:
	Bmp(BF_TYPE type, Image img);
	Bmp(BF_TYPE type, int width, int height, Color default_color);
	~Bmp() {};

	inline int const getImgSize() { return __info.biWidth * __info.biHeight * 3; }
	inline int const getBfSize() { return __header.bfSize; }
	inline int const getBiSize() { return __info.biSize; }
	inline int const getWidth() { return __info.biWidth; }
	inline int const getHeight() { return __info.biHeight; }
	inline int const getRowOffset() { return __row_offset; }

	void fillColor(Color color);
	void setRowOffset();

	void writeBmpFile(const char* path);
};
