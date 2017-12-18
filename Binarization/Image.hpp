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
		Image() {}

		Image(int width, int height, Pixel32* bits = nullptr)
			: width(width), height(height), size(width*height)
		{
			data = new Pixel32[size];

			if (bits != nullptr)  std::memcpy(data, bits, size * sizeof(Pixel32));
		}

		static Image Reference(int width, int height, Pixel32* bits)
		{
			Image referenceImage;
			referenceImage.width = width;
			referenceImage.height = height;
			referenceImage.size = width * height;
			referenceImage.data = bits;
			referenceImage.managedExternally = true;

			return referenceImage;
		}

		// Note: https://en.wikipedia.org/wiki/Copy_elision
		~Image() { if (!managedExternally) delete[] data; }

		Image(const Image& image, bool forceDeepCopy = false)
			: width(image.width), 
			height(image.height), 
			depth(image.depth), 
			maxVal(image.maxVal), 
			tupleType(image.tupleType), 
			size(image.size), 
			managedExternally(image.managedExternally)
		{
			if (managedExternally && !forceDeepCopy) // Shallow Copy
			{
				data = image.data;
			}
			else // Deep Copy
			{
				data = new Pixel32[size];
				std::memcpy(data, image.data, size * sizeof(Pixel32));
				managedExternally = false;
			}
		}

		// External Memory Management
		bool managedExternally = false;

		// PPM Values
		int width = 0;
		int height = 0;
		int size = 0;
		int depth = 4;
		int maxVal = 255;
		std::string tupleType = TupleTypes::RGBA;

		// Compilers are forced to optimize array access, not std::vector access.
		// This may be slightly faster for data access than vector.
		// std:vector [] operator implementation: return (*(this->_Myfirst + _Pos));
		Pixel32* data = nullptr;

		inline Pixel32& Pixel(int x, int y) { return data[(y * width) + x]; }
		inline Pixel32  Pixel(int x, int y) const { return data[(y * width) + x]; }
		inline Pixel32  Pixel(int x, int y, Pixel32 default) const { return (x < 0 || x >= width || y < 0 || y >= height) ? default: Pixel(x, y); }
	};
}


#endif // IMAGE_HPP
