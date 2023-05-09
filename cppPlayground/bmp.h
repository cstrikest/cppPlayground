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

typedef int simple_line[1][50][3];

typedef std::vector<std::vector<std::vector<int>>> Image;

Image createImage(int width, int height);

class FileReader
{
	
};

class FileWriter
{
private:
	std::ofstream ofs;

public:
	FileWriter() {}
	inline FileWriter(const char* path) { ofs.open(path, std::ios::binary | std::ios::out); }
	~FileWriter() { ofs.close(); }

	inline void writeByte(char byte) {ofs.write(&byte, 1);}
	inline void writeBuffer(char* buffer, int length) { ofs.write(buffer, length); }
};

class BmpReader : FileReader
{
	
};

class BmpWriter : FileWriter
{
public:
	inline BmpWriter(const char* path) : FileWriter(path) {};
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
	int biXPelsPerMeter = 300; 
	int biYPelsPerMeter = 300; 
	unsigned int    biClrUsed = 0;      
	unsigned int    biClrImportant = 0;  

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

void fillColor(simple_line& l);
void fillColor(Image& image);
