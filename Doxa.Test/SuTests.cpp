#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	// Exposes protected members for Unit Testing
	class SuTestHarness : public Su
	{
	public:
		SuTestHarness() : Su() {}
		using Su::AutoDetectParameters;
		using Su::SuCalculations;
	};

	TEST(SuTests, SuAutoDetectParametersTest)
	{
		// Setup - Create a small contrast image with a known stroke pattern.
		// Peaks at stroke edges spaced 3px apart.
		const int width = 20;
		const int height = 5;
		Pixel8 contrastData[width * height];
		std::memset(contrastData, 0, sizeof(contrastData));

		for (int y = 0; y < height; ++y)
		{
			const int row = y * width;

			contrastData[row + 3] = 200;
			contrastData[row + 6] = 200;
			contrastData[row + 10] = 200;
			contrastData[row + 13] = 200;
		}

		Image contrastImage(width, height, contrastData);

		// Method under Test
		SuTestHarness su;
		int windowSize = 0;
		int minN = 0;
		su.Initialize(contrastImage);
		su.AutoDetectParameters(windowSize, minN, contrastImage);

		// The dominant peak distance is 3, so strokeWidth = 3
		EXPECT_EQ(6, windowSize); // 3 * 2 = 6
		EXPECT_EQ(6, minN);        // windowSize
	}

	TEST(SuTests, SuCalculationsTest)
	{
		// Setup - 3x3 grayscale image with known values
		Pixel8 grayData[] = {
			100, 150, 200,
			 50, 100, 150,
			 75, 125, 175
		};
		Image grayImage(3, 3, grayData);

		// High contrast binary image: White = high contrast pixel
		Pixel8 contrastData[] = {
			Palette::White,  Palette::Black, Palette::White,
			Palette::Black,  Palette::White, Palette::Black,
			Palette::White,  Palette::Black, Palette::White
		};
		Image contrastImage(3, 3, contrastData);

		// Window covers entire image
		Region window;
		window.upperLeft = { 0, 0 };
		window.bottomRight = { 2, 2 };

		// Method under Test
		SuTestHarness su;
		su.Initialize(grayImage);
		int Ne;
		double meanE, stdE;
		su.SuCalculations(Ne, meanE, stdE, contrastImage, grayImage, window);

		// High contrast pixels (White): (0,0)=100, (0,2)=200, (1,1)=100, (2,0)=75, (2,2)=175
		EXPECT_EQ(5, Ne);
		EXPECT_DOUBLE_EQ(130.0, meanE);  // (100+200+100+75+175) / 5

		// variance = sum((x-mean)^2)/Ne = (30^2 + 70^2 + 30^2 + 55^2 + 45^2)/5 = 11750/5 = 2350
		// stdE = sqrt(2350)
		double expectedStdE = std::sqrt(11750.0 / 5.0);
		EXPECT_NEAR(expectedStdE, stdE, 0.001);
	}
}
