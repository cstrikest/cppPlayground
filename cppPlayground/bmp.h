#pragma once
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<int>[3]> Image;

class FileReader
{
	
};

class FileWriter
{
private:
	std::ofstream ofs;

public:
	FileWriter() {}
	inline FileWriter(const char* path) { ofs.open(path, std::ios::binary | std::ios::in); }
	~FileWriter() { ofs.close(); }

	void writeByte(char);
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
//https://blog.csdn.net/m0_62505136/article/details/121153508
