/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstring>
#include "Types.hpp"


namespace Binarization
{
	struct Image
	{
		Image() : Image(0, 0)
		{
			//CTOR - For reading PAM data into the object.  This keeps the image header information on the stack.
		}

		Image(int width, int height, Pixel32* bits = nullptr, int depth = 4, int maxVal = 255, const std::string& tupleType = TupleTypes::RGBA)
			: width(width), height(height), depth(depth), maxVal(maxVal), tupleType(tupleType), size(width*height)
		{
			data = new Pixel32[size];

			if (bits != nullptr)  std::memcpy(data, bits, size * sizeof(Pixel32));
		}

		// Note: https://en.wikipedia.org/wiki/Copy_elision
		~Image() { delete[] data; }

		Image(const Image& image)
			: width(image.width), height(image.height), depth(image.depth), maxVal(image.maxVal), tupleType(image.tupleType), size(image.size)
		{
			data = new Pixel32[size];
			std::memcpy(data, image.data, size * sizeof(Pixel32));
		}

		// PPM Values
		int width;
		int height;
		int size;
		int depth;
		int maxVal;
		std::string tupleType;

		// Compilers are forced to optimize array access, not std::vector access.
		// This may be slightly faster for data access than vector.
		// std:vector [] operator implementation: return (*(this->_Myfirst + _Pos));
		Pixel32* data;

		inline Pixel32& Pixel(int x, int y) { return data[(y * width) + x]; }
		inline Pixel32  Pixel(int x, int y) const { return data[(y * width) + x]; }
		inline Pixel32  Pixel(int x, int y, Pixel32 default) const { return (x < 0 || x >= width || y < 0 || y >= height) ? default: Pixel(x, y); }
	};
}


#endif // IMAGE_HPP
