// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef PPM_HPP
#define PPM_HPP

#include <string>
#include <fstream>
#include <cassert>
#include "Image.hpp"


namespace Binarization
{
	/// <summary>
	/// Portable Pixel Map: Portable Arbitrary Map (P7) 32 bit RGBA
	/// This class will allow you to read and write .pam files natively, without a 3rd party library.
	/// </summary>
	class PPM
	{
	public:
		static void Read(const std::string& fileLocation, Image& image)
		{
			if (image.data != nullptr) delete image.data;

			std::ifstream file;
			file.open(fileLocation.c_str(), std::ios::binary);

			file >> image;

			file.clear();
			file.close();
		}

		static void Write(const Image& image, const std::string& fileLocation)
		{
			if (image.data == nullptr) return;

			std::ofstream file;
			file.open(fileLocation.c_str(), std::ios::binary);

			file << image;

			file.clear();
			file.close();
		}

	private:
		friend std::istream& operator >> (std::istream& inputStream, Image& image);
		friend std::ostream& operator <<(std::ostream& outputStream, const Image& image);
	};


	static std::istream& operator >> (std::istream& inputStream, Image& image)
	{
		std::string magicNumber, widthTxt, heightTxt, depthTxt, maxValTxt, tuplTypeTxt, endHeader;

		inputStream >> magicNumber;

		if (magicNumber != "P7") throw "PAM: Unsupported file format.  P7 is the only supported format.";

		inputStream
			>> widthTxt >> image.width
			>> heightTxt >> image.height
			>> depthTxt >> image.depth
			>> maxValTxt >> image.maxVal
			>> tuplTypeTxt >> image.tupleType
			>> endHeader;

		// Assertions about our header
		assert(widthTxt == "WIDTH");
		assert(heightTxt == "HEIGHT");
		assert(depthTxt == "DEPTH");
		assert(maxValTxt == "MAXVAL");
		assert(tuplTypeTxt == "TUPLTYPE");
		assert(endHeader == "ENDHDR");

		if (image.depth != 4) throw "PAM: Unsupported depth.  Only 32 bit images are supported.";
		if (image.tupleType != TupleTypes::RGBA) throw "PAM: Unsupported data format.  Only RGBA is supported.";

		inputStream.get(); // Skip trailing white space

		// Read Data
		image.size = image.width * image.height;
		//if (image.data != nullptr) delete[] image.data; // Read into an existing object
		image.data = new Pixel32[image.size];

		const size_t size = image.size * sizeof(Pixel32);
		inputStream.read(reinterpret_cast<char *>(image.data), size);

		return inputStream;
	}


	static std::ostream& operator <<(std::ostream &outputStream, const Image &image)
	{
		outputStream
			<< "P7" << "\n"
			<< "WIDTH " << image.width << "\n"
			<< "HEIGHT " << image.height << "\n"
			<< "DEPTH " << image.depth << "\n"
			<< "MAXVAL " << image.maxVal << "\n"
			<< "TUPLTYPE " << image.tupleType << "\n"
			<< "ENDHDR\n";

		const size_t size = image.size * sizeof(Pixel32);
		outputStream.write(reinterpret_cast<char *>(image.data), size);

		return outputStream;
	}
}


#endif // PPM_HPP
