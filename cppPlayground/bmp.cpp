#include "bmp.h"
#include "colors.h"

//通过RAW直接载入
Bmp::Bmp(bmp_type::BF_TYPE type, int width, int height, TripleRGB* surface)
{
	info_.biWidth = width;
	info_.biHeight = height;

	setRowOffset();

	header_.bfType = type;
	header_.bfSize = (width * 3 + row_offset_) * height + header_.bfOffBits;
	info_.biSizeImage = (width * 3 + row_offset_) * height;

	if (width * height > MAX_DATA_SIZE) 
		throw BmpTooBigToLoadException(width * height, MAX_DATA_SIZE);
	surface_ = new TripleRGB[width * height];

	*surface_ = *surface;
}

//指定颜色创建RAW
Bmp::Bmp(bmp_type::BF_TYPE type, int width, int height, TripleRGB color = Color::WHITE)
{
	info_.biWidth = width;
	info_.biHeight = height;

	setRowOffset();

	header_.bfType = type;
	header_.bfSize = (width * 3 + row_offset_) * height + header_.bfOffBits;
	info_.biSizeImage = (width * 3 + row_offset_) * height;

	surface_ = new TripleRGB[width * height];

	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			*(surface_ + (row * width + column)) = color;
		}
	}
}

//从BMP文件读
Bmp::Bmp(bmp_type::BF_TYPE type, const char* path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw BmpFileNotExistException();

	ifs.read((char*)&header_, sizeof(BmpFileHeader));
	ifs.read((char*)&info_, sizeof(BmpInfoHeader));

	setRowOffset();

	surface_ = new TripleRGB[info_.biWidth * info_.biHeight];

	char sink = ' ';

	for (int row = 0; row < info_.biHeight; row++)
	{
		for (int column = 0; column < info_.biWidth; column++)
		{
			ifs.read((char*)(surface_ + (row * info_.biWidth + column)), sizeof(TripleRGB));
		}
		//埋掉占位符
		ifs.read(&sink, row_offset_);
	}
	ifs.close();
}

Bmp::Bmp(const Bmp& bmp) :
	header_(bmp.header_),
	info_(bmp.info_),
	row_offset_(bmp.row_offset_)
{
	int len = info_.biWidth * info_.biHeight;
	surface_ = new TripleRGB[len];
	memcpy(surface_, bmp.surface_, len);
}

Bmp::Bmp(Bmp&& bmp) noexcept :
	header_(bmp.header_),
	info_(bmp.info_),
	row_offset_(bmp.row_offset_)
{
	surface_ = bmp.surface_;
	bmp.surface_ = nullptr;
}

Bmp& Bmp::operator=(const Bmp& bmp)
{
	if (this == &bmp) return *this;
	delete[] surface_;
	int len = info_.biWidth * info_.biHeight;
	surface_ = new TripleRGB[len];
	memcpy(surface_, bmp.surface_, len);
	memcpy(&header_, &bmp.header_, sizeof(bmp.header_));
	memcpy(&info_, &bmp.info_, sizeof(bmp.info_));
	row_offset_ = bmp.row_offset_;
	return *this;
}

Bmp& Bmp::operator=(Bmp&& bmp) noexcept
{
	if (this == &bmp) return *this;
	delete[] surface_;
	int len = info_.biWidth * info_.biHeight;
	surface_ = new TripleRGB[len];
	surface_ = bmp.surface_;
	memcpy(&header_, &bmp.header_, sizeof(bmp.header_));
	memcpy(&info_, &bmp.info_, sizeof(bmp.info_));
	row_offset_ = bmp.row_offset_;
	bmp.surface_ = nullptr;
	return *this;
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
			ofs.write((char*)(surface_ + (row * info_.biWidth + column)), 3);
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

//指定像素重载
TripleRGB* Bmp::operator()(int x, int y)
{
	if (x < 0 || y < 0 || x >= info_.biWidth || y >= info_.biHeight) throw BmpInvalidIndexException(x, y);
	return surface_ + ((info_.biHeight - y - 1) * info_.biWidth + x);
}
