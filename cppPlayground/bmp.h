﻿#pragma once
//#pragma once 和 #ifndef #define 的作用确实是防止一个头文件在同一个源文件中被多次包含。
//然而，这并不能解决链接时的重复符号问题，因为这个问题是由多个源文件包含同一个头文件导致的。
//在这种情况下，虽然每个源文件都只包含一份头文件的内容，但是当链接器将所有源文件链接在一起时，
//它会发现有多个相同的符号定义，从而导致重复符号错误。

//各种防止重复包含的方法是防止同一个源文件包含多个相同的头文件（间接重复包含）
//不是防止多个源文件包含同一个。毕竟头文件用途就是为了让多个源文件去包含他。
//所以在头文件定义了非成员函数之后，会出现符号错误。

//bmp.h
//BMP文件操作类 定义BMP文件结构与读写函数
//使用包含RGB三个颜色数据的结构代表每个像素（RAW数据

#include <iostream>
#include <fstream>
#include <vector>

//0x00指针
constexpr const char* ZERO_CHAR = "";

//BMP文件标识符
enum BF_TYPE
{
	BM = 0x4d42,	//Windows3+ ,NT
	BA = 0x4142,	//OS/2	Bitmap Array
	CI = 0x4943,	//		Color Icon
	CP = 0x5043,	//		Color pointer
	IC = 0x4349,	//		Icon
	PT = 0x5450		//		Pointer
};

//按照n字节对齐
//不对齐的话bfSize会落到0x04上，文件头就会变成16字节，无法读取
#pragma pack(2)
//BMP文件头 定义了文件标识符 文件大小等											14bytes
struct BmpFileHeader
{
	unsigned short			bfType;					//标识符，现在一般是BM		2
	unsigned int			bfSize;					//文件大小				4
	const unsigned short	bfReserved1 = 0x00;		//固定置0				2
	const unsigned short	bfReserved2 = 0x00;		//固定置0				2
	const unsigned int		bfOffBits = 0x36;		//图片信息偏移量			4
};

//这里按min(SIZE,MAX_SIZE)对齐正好，所以恢复默认
#pragma pack()
//BMP信息头 定义了图片具体信息													40bytes
struct BmpInfoHeader
{
	const unsigned int		biSize = 40;			//信息头长度				4
	int						biWidth;				//宽 为负则是翻转			4
	int						biHeight;				//高						4
	const unsigned short	biPlanes = 1;			//面数 都是平面图所以置1	2
	const unsigned short	biBitCount = 24;		//像素位数 3原色8bit分解能	2
	const unsigned int		biCompression = 0;		//压缩方式 0不压缩			4
	unsigned int			biSizeImage;			//图像信息大小			4
	const int				biXPelsPerMeter = 300;	//横向PPI				4
	const int				biYPelsPerMeter = 300;	//纵向PPI				4
	const unsigned int		biClrUsed = 0;			//彩色表中的颜色索引数		4
	const unsigned int		biClrImportant = 0;		//重要颜色索引数 0为都重要	4
};

struct TripleRGB
{
	unsigned char			b;
	unsigned char			g;
	unsigned char			r;
};

class Bmp
{
private:
	//文件头
	BmpFileHeader __header;
	//信息头
	BmpInfoHeader __info;
	//补0行偏移量
	unsigned int __row_offset;

public:
	//RAW像素颜色数据指针
	TripleRGB* surface;

	//通过RAW直接载入
	Bmp(BF_TYPE type, int width, int height, TripleRGB* surface);
	//指定颜色创建RAW
	Bmp(BF_TYPE type, int width, int height, TripleRGB color);
	//从BMP文件读
	Bmp(BF_TYPE type, const char* path);
	//复制构造函数 防止多重delete[]
	Bmp(const Bmp& bmp);
	//delete RAW指针
	inline ~Bmp() { delete[] surface; }

	inline int getImgSize() const { return __info.biWidth * __info.biHeight * 3; }
	inline int getPixelNumber() const { return __info.biWidth * __info.biHeight; }
	inline int getBfSize() const { return __header.bfSize; }
	inline int getBiSize() const { return __info.biSize; }
	inline int getWidth() const { return __info.biWidth; }
	inline int getHeight() const { return __info.biHeight; }
	inline int getRowOffset() const { return __row_offset; }

	//根据width与4的模计算行偏移量
	void setRowOffset();

	//写BMP文件
	void writeBmpFile(const char* path);
};
