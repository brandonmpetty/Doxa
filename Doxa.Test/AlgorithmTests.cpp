#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class AlgorithmTests : public ::testing::Test {
	protected:
		const Pixel8 input[4] = {
			Palette::Black, Palette::White,
			Palette::White, Palette::Black
		};

		const Pixel8 expected[4] = {
			Palette::Black, Palette::Black,
			Palette::Black, Palette::Black
		};
	};

	// A dummy binarization algorithm that turns everything black
	class BinarizationTestharness : public Algorithm<BinarizationTestharness>
	{
	public:
		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// NOTE: Linker unable to find Palette:Black on Linux with Clang and G++
			std::fill_n(binaryImageOut.data, binaryImageOut.size, 0/* Palette::Black */);
		}
	};

	TEST_F(AlgorithmTests, AlgorithmToBinaryTest)
	{
		// Obtain 2x2 Gray Scale Image
		const Image grayScaleImageIn(2, 2, input);

		// Initialize the memory for our 2x2 Binary Image
		Image binaryImageOut(grayScaleImageIn.width, grayScaleImageIn.height);

		// Execute our method under test
		BinarizationTestharness algorithm;
		algorithm.Initialize(grayScaleImageIn);
		algorithm.ToBinary(binaryImageOut);

		// Assert correctness
		TestUtilities::AssertImageData(binaryImageOut, expected);
	}

	TEST_F(AlgorithmTests, AlgorithmToBinaryImageTest)
	{
		// Obtain 2x2 Gray Scale Image
		const Image grayScaleImageIn(2, 2, input);

		// Execute our method under test
		Image binaryImageOut = BinarizationTestharness::ToBinaryImage(grayScaleImageIn, Parameters());

		// Assert correctness
		TestUtilities::AssertImageData(binaryImageOut, expected);
	}

	TEST_F(AlgorithmTests, AlgorithmUpdateToBinaryTest)
	{
		// Obtain 2x2 Gray Scale Image
		Image image(2, 2, input);

		// Execute our method under test
		BinarizationTestharness::UpdateToBinary(image);

		// Assert correctness
		TestUtilities::AssertImageData(image, expected);
	}
}
