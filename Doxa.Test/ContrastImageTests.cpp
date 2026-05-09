#include "pch.h"
#include "ImageFixture.hpp"


namespace Doxa::UnitTests
{
	class ContrastImageTests : public ImageFixture {};
	TEST_F(ContrastImageTests, GenerateContrastImageTest)
	{
		Image contrastImage(image.width, image.height);
		ContrastImage::GenerateContrastImage(contrastImage, image);

		PNM::Write(contrastImage, projFolder + "2JohnC1V3-ContrastImage.ppm");
	}

	TEST_F(ContrastImageTests, EstimateStrokeWidthTest)
	{
		// Peaks spaced 5px apart
		constexpr int width = 30;
		constexpr int height = 4;
		Pixel8 contrastData[width * height];
		std::memset(contrastData, 0, sizeof(contrastData));

		for (int y = 0; y < height; ++y)
		{
			const int row = y * width;

			contrastData[row + 5] = 180;
			contrastData[row + 10] = 180;
			contrastData[row + 15] = 180;
			contrastData[row + 20] = 180;
		}

		Image contrastImage(width, height, contrastData);

		EXPECT_EQ(5, ContrastImage::EstimateStrokeWidth(contrastImage));
	}

	TEST_F(ContrastImageTests, GenerateHighContrastImageTest)
	{
		Image highContrastImage(image.width, image.height);
		ContrastImage::GenerateHighContrastImage(highContrastImage, image);

		PNM::Write(highContrastImage, projFolder + "2JohnC1V3-HighContrastImage.pbm");
	}
}
