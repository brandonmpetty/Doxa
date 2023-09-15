#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	// Exposes protected members for Unit Testing
	class ISauvolaTestharness : public ISauvola
	{
	public:
		ISauvolaTestharness() : ISauvola() {}
		using ISauvola::Combine;
		using ISauvola::Spider;
	};

	Pixel8 sauvolaBinaryOutput[38] = { 
		Palette::White,  Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,
		Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,  Palette::White,
		Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::Black,
		Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,
		Palette::White,  Palette::White,  Palette::Black,  Palette::White,  Palette::Black,  Palette::Black,
		Palette::Black,  Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::Black
	};

	TEST(ISauvolaTests, ISauvolaSpiderTest)
	{
		// Setup
		Image image(6, 6, sauvolaBinaryOutput);			// Sauvola Binary
		Image outputImage(image.width, image.height);	// Output of Spider
		outputImage.Fill(Palette::White);

		// Method under Test
		ISauvolaTestharness isauvola;
		isauvola.Spider(outputImage, image, 19);

		// Assert Correctness
		Pixel8 expected[] = { 
			Palette::White,  Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,
			Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,  Palette::White,
			Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::Black,
			Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,
			Palette::White,  Palette::White,  Palette::Black,  Palette::White,  Palette::Black,  Palette::Black,
			Palette::White,  Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::Black 
		};

		TestUtilities::AssertImageData(outputImage, expected);
	}

	TEST(ISauvolaTests, ISauvolaSpiderSinglePixelTest)
	{
		// Setup
		Image image(6, 6, sauvolaBinaryOutput);			// Sauvola Binary
		Image outputImage(image.width, image.height);	// Output of Spider
		outputImage.Fill(Palette::White);

		// Method under Test
		ISauvolaTestharness isauvola;
		isauvola.Spider(outputImage, image, 30);

		// Assert Correctness
		Pixel8 expected[] = {
			Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,
			Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,
			Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,
			Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,
			Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,
			Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White
		};

		TestUtilities::AssertImageData(outputImage, expected);
	}

	TEST(ISauvolaTests, ISauvolaCombineTest)
	{
		// Setup
		Pixel8 highContrastData[] = {
			Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,  Palette::White,
			Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,  Palette::White,
			Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,
			Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,
			Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,
			Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::Black
		};
		Image highContrastImage(6, 6, highContrastData);  // High Contrast Image

		Image sauvolaImage(6, 6, sauvolaBinaryOutput);  // Sauvola Binary
		Image outputImage(sauvolaImage.width, sauvolaImage.height);  // Output of Spider

		// Method under Test
		ISauvolaTestharness isauvola;
		isauvola.Combine(outputImage, highContrastImage, sauvolaImage);

		// Assert Correctness
		Pixel8 expected[] = {
			Palette::White,  Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White,
			Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,  Palette::White,
			Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::Black,
			Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::White,  Palette::Black,
			Palette::White,  Palette::White,  Palette::Black,  Palette::White,  Palette::Black,  Palette::Black,
			Palette::Black,  Palette::White,  Palette::Black,  Palette::Black,  Palette::White,  Palette::Black
		};

		TestUtilities::AssertImageData(outputImage, expected);
	}
}
