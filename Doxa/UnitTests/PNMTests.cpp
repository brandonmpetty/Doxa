#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(PNMTests)
	{
	public:

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

		TEST_METHOD(PNMRead1BitBinaryTest)
		{
			// Setup - 1-bit Binary Data
			const char buffer[] = { 0xA0, 0x40, 0xA0 }; // 10100000 01000000 10100000
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

		TEST_METHOD(PNMRead8BitBinaryTest)
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

		TEST_METHOD(PNMRead24BitBinaryTest)
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

		TEST_METHOD(PNMRead32BitBinaryTest)
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

		TEST_METHOD(PNMReadPNMBadFormatTest)
		{
			// There is no P8
			std::istringstream stream("P8 1 0 255");
			PNMTestharness pnm;
			Image image;

			Assert::ExpectException<const char*>([&]() { pnm.ReadPNM(stream, image); });
		}

		TEST_METHOD(PNMWriteAndReadP4Test)
		{
			PNMTestharness pnm;
			TestWriteAndReadBinary([&](std::ostream &outputStream, const Image &image) {
				pnm.WriteP4(outputStream, image);
			});
		}

		TEST_METHOD(PNMWriteAndReadP5Test)
		{
			PNMTestharness pnm;
			TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
				pnm.WriteP5(outputStream, image);
			});
		}

		TEST_METHOD(PNMWriteAndReadP6Test)
		{
			PNMTestharness pnm;
			TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
				pnm.WriteP6(outputStream, image);
			});
		}

		TEST_METHOD(PNMWriteAndReadP7Test)
		{
			PNMTestharness pnm;
			TestWriteAndReadGrayScale([&](std::ostream &outputStream, const Image &image) {
				pnm.WriteP7(outputStream, image);
			});
		}

	protected:
		void TestWriteAndReadGrayScale(std::function<void(std::ostream &outputStream, const Image &image)> writeFunc)
		{
			// Setup
			Image input(3, 2);

			input.data[0] = 255;
			input.data[1] = 0;
			input.data[2] = 255;
			input.data[3] = 55;
			input.data[4] = 125;
			input.data[5] = 200;

			// Execute - Write
			std::ostringstream stream;
			writeFunc(stream, input);

			// Execute - Read
			PNMTestharness pnm;
			Image output;
			pnm.ReadPNM(std::istringstream(stream.str()), output);

			// Assert
			Assert::AreEqual(3, output.width);
			Assert::AreEqual(2, output.height);
			TestUtilities::AssertImages(input, output);
		}

		void TestWriteAndReadBinary(std::function<void(std::ostream &outputStream, const Image &image)> writeFunc)
		{
			// Setup
			Image input(3, 2);

			input.data[0] = 255;
			input.data[1] = 0;
			input.data[2] = 255;
			input.data[3] = 0;
			input.data[4] = 255;
			input.data[5] = 255;

			// Execute - Write
			std::ostringstream stream;
			writeFunc(stream, input);

			// Execute - Read
			PNMTestharness pnm;
			Image output;
			pnm.ReadPNM(std::istringstream(stream.str()), output);

			// Assert
			Assert::AreEqual(3, output.width);
			Assert::AreEqual(2, output.height);
			TestUtilities::AssertImages(input, output);
		}
	};
}
