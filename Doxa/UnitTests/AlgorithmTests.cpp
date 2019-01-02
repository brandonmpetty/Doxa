#include "CppUnitTest.h"
#include "../Algorithm.hpp"
#include "../Palette.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(AlgorithmTests)
	{
		// A dummy binarization algorithm that turns everything black
		class BinarizationTestharness : public Algorithm<BinarizationTestharness>
		{
		public:
			void ToBinary(Image& binaryImageOut, const Parameters& parameters)
			{
				std::fill_n(binaryImageOut.data, binaryImageOut.size, Palette::Black);
			}
		};

		const Pixel8 input[4] = {
			Palette::Black, Palette::White,
			Palette::White, Palette::Black
		};

		const Pixel8 expected[4] = {
			Palette::Black, Palette::Black,
			Palette::Black, Palette::Black
		};

	public:
		TEST_METHOD(AlgorithmToBinaryTest)
		{
			// Obtain 2x2 Gray Scale Image
			const Image grayScaleImageIn(2, 2, input);

			// Initialize the memory for our 2x2 Binary Image
			Image binaryImageOut(grayScaleImageIn.width, grayScaleImageIn.height);

			// Execute our method under test
			BinarizationTestharness algorithm;
			algorithm.Initialize(grayScaleImageIn);
			algorithm.ToBinary(binaryImageOut, Parameters());

			// Assert correctness
			Assert::AreEqual(0, std::memcmp(binaryImageOut.data, expected, sizeof(Pixel8) * binaryImageOut.size));
		}

		TEST_METHOD(AlgorithmToBinaryImageTest)
		{
			// Obtain 2x2 Gray Scale Image
			const Image grayScaleImageIn(2, 2, input);

			// Execute our method under test
			Image binaryImageOut = BinarizationTestharness::ToBinaryImage(grayScaleImageIn, Parameters());

			// Assert correctness
			Assert::AreEqual(0, std::memcmp(binaryImageOut.data, expected, sizeof(Pixel8) * binaryImageOut.size));
		}

		TEST_METHOD(AlgorithmUpdateToBinaryTest)
		{
			// Obtain 2x2 Gray Scale Image
			Image image(2, 2, input);

			// Execute our method under test
			BinarizationTestharness::UpdateToBinary(image, Parameters());

			// Assert correctness
			Assert::AreEqual(0, std::memcmp(image.data, expected, sizeof(Pixel8) * image.size));
		}
	};
}
