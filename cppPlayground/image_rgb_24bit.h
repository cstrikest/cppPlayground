#pragma once
#include <exception>
#include <string>
#include <iostream>

constexpr int MAX_DATA_SIZE = 32768 * 32768;

struct TripleRGB
{
	unsigned char			b;
	unsigned char			g;
	unsigned char			r;
};

typedef TripleRGB Color;

class ImageRgb24b
{
protected:
	int width_;
	int height_;
	TripleRGB* data_;

public:

	ImageRgb24b(int width, int height);

	inline virtual ~ImageRgb24b() { delete[] data_; std::cout << "del image" << std::endl;}
	ImageRgb24b(const ImageRgb24b&);
	ImageRgb24b(ImageRgb24b&&) noexcept;
	ImageRgb24b& operator=(const ImageRgb24b&);
	ImageRgb24b& operator=(ImageRgb24b&&) noexcept;

	inline int getWidth() const { return width_; }
	inline int getHeight() const { return height_; }
	inline int getArea() const { return width_ * height_; }

	void setColor(Color c);
	//指定像素重载 括号有点不好读，想用多重方括弧。但是好麻烦
	TripleRGB* operator()(int, int);
};

class TooBigToLoadException : public std::exception
{
public:
	inline TooBigToLoadException(int actualSize, int maxSize)
		: std::exception(("Image too big to load. Actual size: " +
			std::to_string(actualSize) + ", Max size: " +
			std::to_string(maxSize)).c_str()) {}
};
