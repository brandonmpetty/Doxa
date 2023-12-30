#include "pch.h"


namespace Doxa::UnitTests
{
	TEST(GrayscaleTests, GrayscaleAlgorithmsTest)
	{
		// Mean, Value, and Luster contain obvious formulas.
		EXPECT_EQ(100, Grayscale::Mean(100, 30, 170));

		EXPECT_EQ(200, Grayscale::Value(50, 100, 200));
		EXPECT_EQ(200, Grayscale::Value(50, 200, 100));
		EXPECT_EQ(200, Grayscale::Value(200, 100, 50));

		EXPECT_EQ(125, Grayscale::Luster(50, 100, 200));

		EXPECT_EQ(150, Grayscale::MinAvg(100, 200, 300));

		// Assert that all weights sum to exactly 1
		EXPECT_NEAR(1.0, Grayscale::BT601(1.0, 1.0, 1.0), 0.001);
		EXPECT_NEAR(1.0, Grayscale::BT709(1.0, 1.0, 1.0), 0.001);
		EXPECT_NEAR(1.0, Grayscale::BT2100(1.0, 1.0, 1.0), 0.001);
	}

	TEST(GrayscaleTests, GrayscalesRgbToLightnessTest)
	{
		const Pixel8 y = Grayscale::sRgbToLightness(47, 155, 220);

		// Note: .6030 is using the d50 weights, not the 709 weights which our algorithm uses.
		// The weights are only slightly different, so I am keeping the d50 value for posterity.
		// See: https://observablehq.com/@mbostock/lab-and-rgb
		EXPECT_NEAR(0.6030 * 255, y, 0.01 * 255);
	}
}
