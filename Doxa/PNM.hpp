// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef PNM_HPP
#define PNM_HPP

#include <bitset>
#include <string>
#include <fstream>
#include <filesystem>
#include <functional>
#include <cassert>
#include "Image.hpp"
#include "Palette.hpp"
#include "Parameters.hpp"
#include "Grayscale.hpp"

namespace Doxa
{
	namespace fs = std::filesystem;

	/// <summary>
	/// Portable Any-Map (PNM)
	/// 
	/// This class will allow you to read and write PNM formatted files natively, without a 3rd party library.
	/// 
	/// Reading a 24 or 32 bit image will automatically convert it into grayscale.
	/// It should be assume that external PNM images are gamma compressed.
	/// See the Grayscale class for more information.
	/// 
	/// File Format Support:
	///		Portable Bitmap (PBM P4)
	///		8bit Portable Graymap (PGM P5)
	///		Portable Pixmap (PPM P6)
	///		Portable Arbitrary-Map (PAM P7) - Supports reading 8 bit Grayscale, 24 bit RGB, and 32 bit RGBA
	/// 
	/// We do not support ASCII formats (P1, P2, or P3) nor 16bit Grayscale.
	/// </summary>
	class PNM
	{
	public:

		/// <summary>
		/// Values associated with the Parameter: grayscale
		/// The meaning of what these algorithms will produce is entirely up to the input image.
		/// You should not apply Lightness on a Gamma Corrected color image, for example.
		/// </summary>
		enum GrayscaleConversion
		{
			Qt,
			Mean,
			BT601,
			BT709,
			BT2100,
			Value,
			Luster,
			Lightness,
			MinAvg
		};

		/// <summary>
		/// Reads any supported (aka: binary) PNM image from the filesystem.
		/// 24 and 32 bit images will be converted to 8-bit grayscale automatically.
		/// The PNM format specifies 709 gamma compression, but some are know to use sRGB.
		/// When converting to grayscale, this could impact your choice of algorithm.
		/// </summary>
		/// <param name="params">Select a grayscale conversion algorithm via: grayscale</param>
		/// <returns>An 8 bit Image object</returns>
		static Image Read(const std::string& fileLocation, const Parameters& params = Parameters())
		{
			std::ifstream file;
			file.open(fileLocation.c_str(), std::ios::binary);

			PNM pnm;
			Image image;
			pnm.ReadPNM(file, image, params);

			file.clear();
			file.close(); // Automatically closes, but done explicitly for posterity.

			return image;
		}

		/// <summary>
		/// Writes an 8-bit grayscale Image to the filesystem
		/// </summary>
		static void Write(const Image& image, const std::string& fileLocation)
		{
			if (image.data == nullptr) return;

			std::ofstream file;
			file.open(fileLocation.c_str(), std::ios::binary);

			// Save the file based on file extension
			std::string ext = fs::path(fileLocation).extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // C++, please steal from C#

			PNM pnm;
			if (ext == ".pbm")
			{
				pnm.WriteP4(file, image);
			}
			else if (ext == ".pgm")
			{
				pnm.WriteP5(file, image);
			}
			else if (ext == ".ppm")
			{
				pnm.WriteP6(file, image);
			}
			else if (ext == ".pam")
			{
				pnm.WriteP7(file, image);
			}

			file.clear();
			file.close(); // Automatically closes, but done explicitly for posterity.
		}

	protected:
		// Hide default CTOR
		PNM() {}

		void Read1BitBinary(std::istream& inputStream, Image& image)
		{
			const int delta = image.width % 8;
			const int paddedWidth = delta == 0 ? image.width : image.width + 8 - delta;

			for (int y = 0; y < image.height; ++y)
			{
				for (int x = 0; x < paddedWidth; x+=8)
				{
					// Each row is always padded to a full byte
					const std::bitset<8> byte(inputStream.get());
					const int position = (y * image.width) + x;

					for (int offset = 0; offset < 8 && x + offset < image.width; ++offset)
					{
						image.data[position + offset] = byte.test(7 - offset) ? Palette::Black : Palette::White;
					}
				}
			}
		}

		void Read8BitBinary(std::istream& inputStream, Image& image)
		{
			inputStream.read(reinterpret_cast<char *>(image.data), image.size);
		}

		void Read24BitBinary(std::istream& inputStream, Image& image, const Parameters& params = Parameters())
		{
			auto toGrayscale = GrayscaleFactory(params);

			Pixel8 red, green, blue;
			for (int idx = 0; idx < image.size; ++idx)
			{
				red = inputStream.get();
				green = inputStream.get();
				blue = inputStream.get();

				// If the pixel is already gray, do not apply apply the correction
				image.data[idx] = (red == green && green == blue) ?
					blue :
					toGrayscale(red, green, blue); // Convert to GrayScale
			}
		}

		void Read32BitBinary(std::istream& inputStream, Image& image, const Parameters& params = Parameters())
		{
			auto toGrayscale = GrayscaleFactory(params);

			Pixel8 red, green, blue, alpha;
			for (int idx = 0; idx < image.size; ++idx)
			{
				red = inputStream.get();
				green = inputStream.get();
				blue = inputStream.get();
				alpha = inputStream.get(); // TODO - Apply alpha to lower RGB illuminocity

				// If the pixel is already gray, do not apply apply the correction
				image.data[idx] = (red == green && green == blue) ?
					blue :
					toGrayscale(red, green, blue); // Convert to GrayScale
			}
		}

		void ReadPNM(std::istream& inputStream, Image& image, const Parameters& params = Parameters())
		{
			std::string magicNumber;

			inputStream >> magicNumber;

			// Note: We do not currently suppor the ASCII formats (P1, P2, P3)

			if (magicNumber == "P4") // PBM 1 bit - Binary
			{
				// Read Header
				inputStream >> image.width >> image.height;
				inputStream.get(); // Skip trailing white space

				// Initialize storage structure
				image.size = image.width * image.height;
				image.data = new Pixel8[image.size];

				return Read1BitBinary(inputStream, image);
			}
			else if (magicNumber == "P5") // PGM 8 bit - Binary
			{
				// Read Header
				inputStream >> image.width >> image.height >> image.maxVal;
				inputStream.get(); // Skip trailing white space

				// Assertions about our header
				assert(image.maxVal >= 0 && image.maxVal <= 255);

				// Initialize storage structure
				image.size = image.width * image.height;
				image.data = new Pixel8[image.size];

				return Read8BitBinary(inputStream, image);
			}
			else if (magicNumber == "P6") // PPM 24 bit - Binary
			{
				// Read Header
				inputStream >> image.width >> image.height >> image.maxVal;
				inputStream.get(); // Skip trailing white space

				// Assertions about our header
				assert(image.maxVal >= 0 && image.maxVal <= 255);

				// Initialize storage structure
				image.size = image.width * image.height;
				image.data = new Pixel8[image.size];

				return Read24BitBinary(inputStream, image, params);
			}
			else if (magicNumber == "P7") // PAM arbitrary bit - Binary
			{
				std::string widthTxt, heightTxt, depthTxt, maxValTxt, tuplTypeTxt, endHeader;

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

				inputStream.get(); // Skip trailing white space

				// Initialize storage structure
				image.size = image.width * image.height;
				image.data = new Pixel8[image.size];

				switch (image.depth)
				{
				case 1:
					// "Such a PAM image has a depth of 1 and maxval 1 where the one sample in each tuple is 0 to represent a black pixel and 1 to represent a white one."
					// We are not supporting B&W at this time because they want 0 = black and 1 = white.  It offends me to even think about writing such a routine.
					// Why not fall back to PBM's 1bit B&W, or 0 for black and 255 for white.  But 8 bits and 1 is suppose to equal white?  Please.
					if (image.tupleType == TupleTypes::BLACK_WHITE && image.maxVal == 1) throw "PAM: Black and White not supported.  Use PBM instead.";

					return Read8BitBinary(inputStream, image);
				case 3:
					return Read24BitBinary(inputStream, image, params);
				case 4:
					if (image.tupleType != TupleTypes::RGBA) throw "PAM: Only 32bit RGBA is supported.";
					return Read32BitBinary(inputStream, image, params);
				}
			}

			throw "Unsupported Format";
		}

		void WriteP4(std::ostream &outputStream, const Image &image)
		{
			outputStream
				<< "P4" << std::endl
				<< image.width << " " << image.height << std::endl;
			
			const int delta = image.width % 8;
			const int paddedWidth = delta == 0 ? image.width : image.width + 8 - delta;

			for (int y = 0; y < image.height; ++y)
			{
				for (int x = 0; x < paddedWidth; x += 8)
				{
					// Each row is always padded to a full byte
					std::bitset<8> byte;
					const int position = (y * image.width) + x;

					for (int offset = 0; offset < 8 && x + offset < image.width; ++offset)
					{
						byte.set(7 - offset, image.data[position + offset] == Palette::Black);
					}

					outputStream << static_cast<Pixel8>(byte.to_ulong());
				}
			}
		}

		void WriteP5(std::ostream &outputStream, const Image &image)
		{
			outputStream
				<< "P5" << std::endl
				<< image.width << " " << image.height << std::endl
				<< image.maxVal << std::endl;

			const size_t size = image.size * sizeof(Pixel8);
			outputStream.write(reinterpret_cast<char *>(image.data), size);
		}

		void WriteP6(std::ostream& outputStream, const Image& image)
		{
			outputStream
				<< "P6" << std::endl
				<< image.width << " " << image.height << std::endl
				<< image.maxVal << std::endl;

			for (int idx = 0; idx < image.size; ++idx)
			{
				const Pixel8 pixel = image.data[idx];
				outputStream << pixel << pixel << pixel;
			}
		}

		void WriteP7(std::ostream &outputStream, const Image &image)
		{
			assert(image.depth == 1); // We are only supporting 8 bit for now

			outputStream
				<< "P7" << std::endl
				<< "WIDTH " << image.width << std::endl
				<< "HEIGHT " << image.height << std::endl
				<< "DEPTH " << image.depth << std::endl
				<< "MAXVAL " << image.maxVal << std::endl
				<< "TUPLTYPE " << image.tupleType << std::endl
				<< "ENDHDR" << std::endl;

			const size_t size = image.size * sizeof(Pixel8);
			outputStream.write(reinterpret_cast<char *>(image.data), size);
		}

		/// <summary>
		/// Returns a specific Grayscale algorithm based on parameter configuration.
		/// Defaulting to: Mean
		/// This default may change in the future, as Mean is expected to perform better.
		/// </summary>
		/// <param name="params">Must set: grayscale</param>
		/// <returns>A Grayscale algorithm</returns>
		std::function<Pixel8 (Pixel8, Pixel8, Pixel8)> GrayscaleFactory(const Parameters& params)
		{
			// TODO: Add support for sRGB and 709 conversion to Linear RGB, then to gray, then potentially gamma corrected.
			std::function<Pixel8(Pixel8, Pixel8, Pixel8)> algorithm;

			int gsEnum = params.Get("grayscale", (int)GrayscaleConversion::Mean);

			switch (gsEnum)
			{
			case GrayscaleConversion::Qt:
				algorithm = Grayscale::Qt<Pixel8>;
				break;
			case GrayscaleConversion::Mean:
				algorithm = Grayscale::Mean<Pixel8>;
				break;
			case GrayscaleConversion::BT601:
				algorithm = Grayscale::BT601<Pixel8>;
				break;
			case GrayscaleConversion::BT709:
				algorithm = Grayscale::BT709<Pixel8>;
				break;
			case GrayscaleConversion::BT2100:
				algorithm = Grayscale::BT2100<Pixel8>;
				break;
			case GrayscaleConversion::Value:
				algorithm = Grayscale::Value<Pixel8>;
				break;
			case GrayscaleConversion::Luster:
				algorithm = Grayscale::Luster<Pixel8>;
				break;
			case GrayscaleConversion::Lightness:
				// This requires a change in colorspace.  sRGB is assumed.
				algorithm = Grayscale::sRgbToLightness;
				break;
			case GrayscaleConversion::MinAvg:
				algorithm = Grayscale::MinAvg<Pixel8>;
				break;
			}

			return algorithm;
		}
	};
}


#endif // PNM_HPP
