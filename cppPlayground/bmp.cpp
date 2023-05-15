#include "bmp.h"
#include "colors.h"

std::pair<int, int> Bmp::getBmpHead(const char* path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw BmpFileNotExistException();
	BmpInfoHeader i;
	ifs.read((char*)&i, sizeof(BmpFileHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp header.");
	ifs.read((char*)&i, sizeof(BmpInfoHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp info.");
	return std::make_pair(i.biWidth, i.biHeight);
}

Bmp::Bmp(bmp_type::BF_TYPE type, int width, int height): ImageRgb24b(width, height)
{
	header_.bfType = type;
	info_.biWidth = width;
	info_.biHeight = height;

	setRowOffset();

	header_.bfSize = (width * 3 + row_offset_) * height + header_.bfOffBits;
	info_.biSizeImage = (width * 3 + row_offset_) * height;
}

//从BMP文件读
Bmp::Bmp(const char* path): ImageRgb24b(getBmpHead(path).first, getBmpHead(path).second)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw BmpFileNotExistException();
	ifs.read((char*)&header_, sizeof(BmpFileHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp header.");
	ifs.read((char*)&info_, sizeof(BmpInfoHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp info.");

	setRowOffset();

	char sink = ' ';

	for (int row = 0; row < info_.biHeight; row++)
	{
		for (int column = 0; column < info_.biWidth; column++)
		{
			ifs.read((char*)(data_ + (row * info_.biWidth + column)), sizeof(TripleRGB));
		}
		//埋掉占位符
		ifs.read(&sink, row_offset_);
	}
	ifs.close();
}

//根据width与4的模计算行偏移量
void Bmp::setRowOffset()
{
	row_offset_ = (info_.biWidth * 3) % 4;
	if (row_offset_ != 0) row_offset_ = 4 - row_offset_;
}

//写BMP文件
void Bmp::writeBmpFile(const char* path)
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) throw BmpFileNotCantWrite(path);
	ofs.write((char*)&header_, sizeof(BmpFileHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp header.");
	ofs.write((char*)&info_, sizeof(BmpInfoHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp info.");
	for (int row = 0; row < info_.biHeight; row++)
	{
		for (int column = 0; column < info_.biWidth; column++)
		{
			ofs.write((char*)(data_ + (row * info_.biWidth + column)), 3);
		}
		for (int t = row_offset_; t > 0; t--)
		{
			ofs.write(ZERO_CHAR, 1);
		}
		if (ofs.fail()) throw std::runtime_error("Failed to write Bmp image data.");
	}
	ofs.flush();	
	ofs.close();
}
