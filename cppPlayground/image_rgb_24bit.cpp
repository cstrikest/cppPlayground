#include "image.h"
#include "bmp.h"
#include "colors.h"

ImageRgb24b::ImageRgb24b(int width, int height): width_(width), height_(height)
{
	if (getArea() > MAX_DATA_SIZE)
		throw TooBigToLoadException(getArea(), MAX_DATA_SIZE);
	data_ = new TripleRGB[getArea()];
	std::cout << "new image" << std::endl;
}

ImageRgb24b::ImageRgb24b(const ImageRgb24b& i): width_(i.width_), height_(i.height_)
{
	data_ = new TripleRGB[getArea()];
	memcpy(data_, i.data_, getArea());
	std::cout << "copy image" << std::endl;
}

ImageRgb24b::ImageRgb24b(ImageRgb24b&& i) noexcept
{
	data_ = new TripleRGB[getArea()];
	data_ = i.data_;
	i.data_ = nullptr;
	std::cout << "move image" << std::endl;
}

ImageRgb24b& ImageRgb24b::operator=(const ImageRgb24b& i)
{
	if (this != &i)
	{
		width_ = i.width_;
		height_ = i.height_;
		delete[] data_;
		data_ = new TripleRGB[getArea()];
		memcpy(data_, i.data_, getArea());
	}
	std::cout << "=copy image" << std::endl;
	return *this;
}

ImageRgb24b& ImageRgb24b::operator=(ImageRgb24b&& i) noexcept
{
	if (this != &i)
	{
		width_ = i.width_;
		height_ = i.height_;
		delete[] data_;
		data_ = new TripleRGB[getArea()];
		data_ = i.data_;
		i.data_ = nullptr;
	}
	std::cout << "=move image" << std::endl;
	return *this;
}

void ImageRgb24b::setColor(Color c)
{
	for (int row = 0; row < height_; row++)
	{
		for (int column = 0; column < width_; column++)
		{
			*(data_ + (row * width_ + column)) = c;
		}
	}
}

//指定像素重载
TripleRGB* ImageRgb24b::operator()(int x, int y)
{
	if (x < 0 || y < 0 || x >= width_ || y >= height_) throw BmpInvalidIndexException(x, y);
	return data_ + ((height_ - y - 1) * width_ + x);
}
