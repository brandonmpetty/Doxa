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

	TEST(GrayscaleTests, GrayscaleColorSpaceTest)
	{
		const Pixel8 red = 225;
		const Pixel8 green = 128;
		const Pixel8 blue = 15;

		// Non-Linear to Linear /w LUT
		const auto lut = Grayscale::LinearLUT();

		const auto redLin = lut[red];
		const auto greenLin = lut[green];
		const auto blueLin = lut[blue];

		// Validate LUT is correct
		EXPECT_NEAR(0.753, redLin, 0.001);
		EXPECT_NEAR(0.216, greenLin, 0.001);
		EXPECT_NEAR(0.005, blueLin, 0.001);

		const auto [X, Y, Z] = Grayscale::RGBToXYZ(redLin, greenLin, blueLin);

		EXPECT_NEAR(X, .3885, 0.0002);
		EXPECT_NEAR(Y, .3148, 0.0002);
		EXPECT_NEAR(Z, .0448, 0.0002);

		const auto [L, a, b] = Grayscale::XYZToLab(X, Y, Z);

		EXPECT_NEAR(L, 62.91, 0.01);
		EXPECT_NEAR(a, 30.95, 0.01);
		EXPECT_NEAR(b, 67.00, 0.01);
	}

	TEST(GrayscaleTests, GrayscaleLinearLightnessTest)
	{
		// 3 pixels: flanking values bracket the test pixel to enable normalization
		const uint8_t input[] = {
			 64,  32, 128,  // pixel 0
			225, 128,  15,  // pixel 1 - test pixel
			200, 160,  80   // pixel 2
		};
		Pixel8 output[3] = {};

		Grayscale::ToGrayscale(output, input, 3, 1, 3, GrayscaleAlgorithms::LIGHTNESS);

		EXPECT_EQ(160, output[1]);  // TODO: replace with correct expected value
	}

	TEST(GrayscaleTests, GrayscaleLinearLABDistTest)
	{
		// 3 pixels: flanking values bracket the test pixel to enable normalization
		const uint8_t input[] = {
			 64,  32, 128,  // pixel 0
			200, 160,  80,  // pixel 1 - test pixel
			186, 128,  15   // pixel 2
		};
		Pixel8 output[3] = {};

		Grayscale::ToGrayscale(output, input, 3, 1, 3, GrayscaleAlgorithms::LABDIST);

		EXPECT_EQ(218, output[1]);  // TODO: replace with correct expected value
	}
}
