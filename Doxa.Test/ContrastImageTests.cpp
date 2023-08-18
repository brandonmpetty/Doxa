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

	TEST_F(ContrastImageTests, GenerateHighContrastImageTest)
	{
		Image highContrastImage(image.width, image.height);
		ContrastImage::GenerateHighContrastImage(highContrastImage, image);

		PNM::Write(highContrastImage, projFolder + "2JohnC1V3-HighContrastImage.pbm");
	}
}
