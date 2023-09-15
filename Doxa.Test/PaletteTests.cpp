#include "pch.h"


namespace Doxa::UnitTests
{
	TEST(PaletteTests, PaletteTest)
	{
		constexpr Pixel32 rgb = Palette::RGB(10, 21, 32);
		constexpr Pixel32 rgba = Palette::RGBA(10, 21, 32, 43);
		constexpr Pixel32 gray = Palette::RGB(124, 124, 124);

		// Verify Endian
		EXPECT_EQ((Pixel32)0xFF20150A, rgb); // 0A = 10, 15 = 21, 20 = 32
		EXPECT_EQ((Pixel32)0x2B20150A, rgba); // 2B = 43

		// Compaire that the colors are equivolent
		EXPECT_EQ(Palette::Red(rgb), Palette::Red(rgba));
		EXPECT_EQ(Palette::Green(rgb), Palette::Green(rgba));
		EXPECT_EQ(Palette::Blue(rgb), Palette::Blue(rgba));

		// Get individual colors from Pixel
		EXPECT_EQ(Palette::Red(rgba), 10);
		EXPECT_EQ(Palette::Green(rgba), 21);
		EXPECT_EQ(Palette::Blue(rgba), 32);

		// Update Alpha
		EXPECT_EQ(Palette::Alpha(rgb), 255);
		EXPECT_EQ(Palette::Alpha(rgba), 43);
		EXPECT_EQ(Palette::UpdateAlpha(rgb, 43), rgba);

		// Gray Values
		EXPECT_FALSE(Palette::IsGray(rgba));
		EXPECT_TRUE(Palette::IsGray(gray));
	}

	TEST(PaletteTests, PaletteColorDistanceTest)
	{
		// When there are no differences, 0
		int noDistance = Palette::ColorDistance(Palette::RGB(255, 0, 0), Palette::RGB(255, 0, 0));
		EXPECT_EQ(0, noDistance);

		// Changing from one color to the next should result in a distance change
		int hueDistance1 = Palette::ColorDistance(Palette::RGB(0, 255, 0), Palette::RGB(0, 0, 255));
		EXPECT_NE(0, hueDistance1);

		int hueDistance2 = Palette::ColorDistance(Palette::RGB(255, 0, 0), Palette::RGB(0, 0, 255));
		EXPECT_NE(0, hueDistance2);

		int hueDistance3 = Palette::ColorDistance(Palette::RGB(0, 0, 255), Palette::RGB(0, 255, 0));
		EXPECT_NE(0, hueDistance3);

		// Ensure that evenly distributed changes have an effect
		int brightnessDistance1 = Palette::ColorDistance(Palette::RGB(10, 20, 30), Palette::RGB(12, 22, 32));
		EXPECT_NE(0, brightnessDistance1);

		// Technically this is grayscale, it is questionable if this should effect things.
		// TODO: Research this.  It seems to comply with CIE Delta-E results. 
		int brightnessDistance2 = Palette::ColorDistance(Palette::RGB(10, 10, 10), Palette::RGB(12, 12, 12));
		EXPECT_NE(0, brightnessDistance2);

		// Verify the degree of change is great enough to be detected
		int colorDistance1 = Palette::ColorDistance(Palette::RGB(255, 255, 0), Palette::RGB(255, 128, 0)); // Yellow to Orange
		int colorDistance2 = Palette::ColorDistance(Palette::RGB(255, 255, 0), Palette::RGB(128, 255, 0)); // Yellow to Light Green
		int colorDistance3 = Palette::ColorDistance(Palette::RGB(255, 128, 0), Palette::RGB(128, 255, 0)); // Orange to Light Green

		// Orange to Green should obviously be farther that the difference between Yellow to Orange, and Yellow to Light Green.
		EXPECT_TRUE(colorDistance3 > colorDistance1 && colorDistance3 > colorDistance2);

		// Even though equally distributed, Light Green is a lot closer to Yellow than Orange.
		// This is consistant with CIE Delta-E calculations.
		EXPECT_TRUE(colorDistance1 > colorDistance2);

		// Ensure that color comparison order does not matter
		int left = Palette::ColorDistance(Palette::RGB(255, 128, 50), Palette::RGB(50, 128, 128));
		int right = Palette::ColorDistance(Palette::RGB(50, 128, 128), Palette::RGB(255, 128, 50));
		EXPECT_EQ(left, right);
	}
}
