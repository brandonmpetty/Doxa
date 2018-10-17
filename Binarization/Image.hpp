// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstring>
#include "Types.hpp"


namespace Binarization
{
	struct Image
	{
		// Default CTOR
		Image() {}

		// CTOR
		Image(int width, int height, Pixel8* bits = nullptr)
			: width(width), 
			height(height), 
			size(width*height)
		{
			data = new Pixel8[size];

			if (bits != nullptr)  
				std::memcpy(data, bits, size);
		}

		// DTOR
		// Note: https://en.wikipedia.org/wiki/Copy_elision
		~Image() 
		{ 
			if (!managedExternally) 
				delete[] data;
		}

		// Copy Constructor
		Image(const Image& image)
			: width(image.width), 
			height(image.height), 
			depth(image.depth), 
			maxVal(image.maxVal), 
			tupleType(image.tupleType), 
			size(image.size)
		{
			data = new Pixel8[size];
			std::memcpy(data, image.data, size);
		}

		// Move Constructor
		Image(Image&& image)
			: width(image.width),
			height(image.height),
			depth(image.depth),
			maxVal(image.maxVal),
			tupleType(image.tupleType),
			size(image.size),
			data(image.data),
			managedExternally(image.managedExternally)
		{
			image.managedExternally = true; // Now managed by the copy
		}

		// Copy Assignment Operator - This will always deep copy, even a reference.
		Image& operator=(const Image& that)
		{
			if (this != &that)
			{
				if (size != that.size)
				{
					delete[] data;

					// Reset in case of a thrown exception allocating memory
					size = 0;
					data = nullptr;

					// Reallocate
					data = new Pixel8[that.size];
					size = that.size;
				}

				width = that.width;
				height = that.height;
				managedExternally = false;

				std::memcpy(data, that.data, size);
			}

			return *this;
		}

		Image Reference()
		{
			return Reference(width, height, data);
		}

		static Image Reference(int width, int height, Pixel8* data)
		{
			Image referenceImage;
			referenceImage.width = width;
			referenceImage.height = height;
			referenceImage.size = width * height;
			referenceImage.data = data;
			referenceImage.managedExternally = true;

			return referenceImage;
		}

		// External Memory Management
		bool managedExternally = false;

		// PNM Values
		int width = 0;
		int height = 0;
		int size = 0;
		int depth = 1;
		int maxVal = 255;
		std::string tupleType = TupleTypes::GRAYSCALE;

		// Compilers are forced to optimize array access, not std::vector access.
		// This may be slightly faster for data access than vector.
		// std:vector [] operator implementation: return (*(this->_Myfirst + _Pos));
		Pixel8* data = nullptr;

		inline Pixel8& Pixel(int x, int y) { return data[(y * width) + x]; }
		inline Pixel8  Pixel(int x, int y) const { return data[(y * width) + x]; }
		inline Pixel8  Pixel(int x, int y, Pixel8 default) const { return (x < 0 || x >= width || y < 0 || y >= height) ? default: Pixel(x, y); }
	};
}


#endif // IMAGE_HPP
