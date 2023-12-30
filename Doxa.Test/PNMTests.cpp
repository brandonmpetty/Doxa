#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	// Exposes protected members for Unit Testing
	class PNMTestharness : public PNM
	{
	public:
		PNMTestharness() :PNM() {}

		// Reads
		using PNM::Read1BitBinary;
		using PNM::Read8BitBinary;
		using PNM::Read24BitBinary;
		using PNM::Read32BitBinary;
		using PNM::ReadPNM;

		// Writes
		using PNM::WriteP4;
		using PNM::WriteP5;
		using PNM::WriteP6;
		using PNM::WriteP7;
	};

	class PNMTests : public ::testing::Test
	{
	protected:
		void TestWriteAndReadGrayScale(std::function<void(std::ostream& outputStream, const Image& image)> writeFunc)
		{
			// Setup
			Image input(3, 2);

			input.data[0] = 255;
			input.data[1] = 0;
			input.data[2] = 255;
			input.data[3] = 55;
			input.data[4] = 125;
			input.data[5] = 200;

			// Test
			TestWriteAndRead(input, writeFunc);
		}

		void TestWriteAndReadBinary(std::function<void(std::ostream& outputStream, const Image& image)> writeFunc)
		{
			// Setup - Image will require padding
			Image input1(3, 2);

			// Row 1
			input1.data[0] = 255;
			input1.data[1] = 0;
			input1.data[2] = 255;

			// Row 2
			input1.data[3] = 0;
			input1.data[4] = 255;
			input1.data[5] = 255;

			// Test Padded Image
			TestWriteAndRead(input1, writeFunc);

			// Setup - Image will NOT require padding
			Image input2(8, 2);

			// Row 1
			input2.data[0] = 255;
			input2.data[1] = 0;
			input2.data[2] = 255;
			input2.data[3] = 0;
			input2.data[4] = 255;
			input2.data[5] = 255;
			input2.data[6] = 255;
			input2.data[7] = 255;

			// Row 2
			input2.data[8] = 0;
			input2.data[9] = 0;
			input2.data[10] = 0;
			input2.data[11] = 0;
			input2.data[12] = 255;
			input2.data[13] = 0;
			input2.data[14] = 0;
			input2.data[15] = 0;

			// Test Padded Image
			TestWriteAndRead(input2, writeFunc);
		}

		void TestWriteAndRead(const Image& inputImage, std::function<void(std::ostream& outputStream, const Image& image)> writeFunc)
		{
			// Execute - Write
			std::ostringstream stream;
			writeFunc(stream, inputImage);

			// Execute - Read
			PNMTestharness pnm;
			Image outputImage;
			std::istringstream iss(stream.str());
			pnm.ReadPNM(iss, outputImage);

			// Assert
			EXPECT_EQ(inputImage.width, outputImage.width);
			EXPECT_EQ(inputImage.height, outputImage.height);
			TestUtilities::AssertImages(inputImage, outputImage);
		}
	};

	TEST_F(PNMTests, PNMRead1BitBinaryTest)
	{
		// Setup - 1-bit Binary Data
		char buffer[] = { 0xA0, 0x40, 0xA0 }; // 10100000 01000000 10100000
		std::istringstream stream(buffer);

		// Execute - Will convert to 8-bit Gray Scale
		PNMTestharness pnm;
		Image image(3, 3);
		pnm.Read1BitBinary(stream, image);

		// Assert
		const Pixel8 expected[] = { 
			Palette::Black, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::White,
			Palette::Black, Palette::White, Palette::Black 
		};

		TestUtilities::AssertImageData(image, expected);
	}

	TEST_F(PNMTests, PNMRead8BitBinaryTest)
	{
		// Setup - 8-bit Gray Scale Data (0 to 255)
		const char buffer[] = { 
			0xFF, 0x01, 0xFF, 
			0x01, 0x7C, 0x7B, 
			0x7A, 0x79, 0x78 
		};
		std::istringstream stream(buffer);

		// Execute
		PNMTestharness pnm;
		Image image(3, 3);
		pnm.Read8BitBinary(stream, image);

		// Assert
		TestUtilities::AssertImageData(image, (Pixel8*)buffer);
	}

	TEST_F(PNMTests, PNMRead24BitBinaryTest)
	{
		// Setup - 24-bit RGB Data
		const char buffer[] = { 
			0xFF, 0x01, 0x01,	0x01, 0xFF, 0x01,	0x01, 0x01, 0xFF, 
			0xFF, 0xFF, 0xFF,	0x78, 0x78, 0x78,	0x01, 0x01, 0x01 
		};
		std::istringstream stream(buffer);

		// Execute - Will convert to 8-bit Gray Scale
		PNMTestharness pnm;
		Image image(3, 2);
		pnm.Read24BitBinary(stream, image);

		// Assert
		const Pixel8 expected[] = { 
			Grayscale::Mean(0xFF, 0x01, 0x01), Grayscale::Mean(0x01, 0xFF, 0x01), Grayscale::Mean(0x01, 0x01, 0xFF),
			Grayscale::Mean(0xFF, 0xFF, 0xFF), Grayscale::Mean(0x78, 0x78, 0x78), Grayscale::Mean(0x01, 0x01, 0x01)
		};

		TestUtilities::AssertImageData(image, expected);
	}

	TEST_F(PNMTests, PNMRead32BitBinaryTest)
	{
		// Setup - 32-bit RGBA
		const char buffer[] = {
			0xFF, 0x01, 0x01, 0x01,		0x01, 0xFF, 0x01, 0x01,		0x01, 0x01, 0xFF, 0x01,
			0xFF, 0xFF, 0xFF, 0x01,		0x78, 0x78, 0x78, 0x01,		0x01, 0x01, 0x01, 0x01
		};
		std::istringstream stream(buffer);

		// Execute - Will convert to 8-bit Gray Scale
		PNMTestharness pnm;
		Image image(3, 2);
		pnm.Read32BitBinary(stream, image);

		// Assert
		const Pixel8 expected[] = {
			Grayscale::Mean(0xFF, 0x01, 0x01), Grayscale::Mean(0x01, 0xFF, 0x01), Grayscale::Mean(0x01, 0x01, 0xFF),
			Grayscale::Mean(0xFF, 0xFF, 0xFF), Grayscale::Mean(0x78, 0x78, 0x78), Grayscale::Mean(0x01, 0x01, 0x01)
		};

		TestUtilities::AssertImageData(image, expected);
	}

	TEST_F(PNMTests, PNMReadPNMBadFormatTest)
	{
		// There is no P8
		std::istringstream stream("P8 1 0 255");
		PNMTestharness pnm;
		Image image;

		EXPECT_ANY_THROW(pnm.ReadPNM(stream, image));
	}

	TEST_F(PNMTests, PNMWriteAndReadP4Test)
	{
		PNMTestharness pnm;
		TestWriteAndReadBinary([&](std::ostream &outputStream, const Image &image) {
			pnm.WriteP4(outputStream, image);
		});
	}

	TEST_F(PNMTests, PNMWriteAndReadP5Test)
	{
		PNMTestharness pnm;
		TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
			pnm.WriteP5(outputStream, image);
		});
	}

	TEST_F(PNMTests, PNMWriteAndReadP6Test)
	{
		PNMTestharness pnm;
		TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
			pnm.WriteP6(outputStream, image);
		});
	}

	TEST_F(PNMTests, PNMWriteAndReadP7Test)
	{
		PNMTestharness pnm;
		TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
			pnm.WriteP7(outputStream, image);
		});
	}
}
