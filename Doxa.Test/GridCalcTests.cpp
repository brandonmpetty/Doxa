#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	TEST(GridCalcTests, GridCalcIterateInterwovenTest)
	{
		// Setup
		Image image(7, 3);

		GridCalc grid = GridCalc();

		// Expected values
		const int ar1[8][5] = {
			{ 0, 0, 0, 2, 2},
			{ 2, 0, 0, 4, 2},
			{ 4, 2, 0, 6, 2},
			{ 6, 4, 0, 6, 2},

			{ 14, 0, 0, 2, 2},
			{ 16, 0, 0, 4, 2},
			{ 18, 2, 0, 6, 2},
			{ 20, 4, 0, 6, 2}
		};

		int inc = 0;

		// Function under test
		grid.Iterate(image, 5, 2, [&](const Region& window, const int& position)
		{
			const auto exp = ar1[inc];
			EXPECT_EQ(exp[0], position);
			EXPECT_EQ(exp[1], window.upperLeft.x);
			EXPECT_EQ(exp[2], window.upperLeft.y);
			EXPECT_EQ(exp[3], window.bottomRight.x);
			EXPECT_EQ(exp[4], window.bottomRight.y);

			inc++;
		});

		EXPECT_EQ(8, inc);
	}

	TEST(GridCalcTests, GridCalcIterateUnevenTest)
	{
		// Setup
		Image image(7, 7);

		GridCalc grid = GridCalc();

		// Expected values
		const int ar1[9][5] = {
			{ 0, 0, 0, 2, 2},
			{ 5, 3, 0, 6, 2},
			{ 6, 4, 0, 6, 2},

			{ 35, 0, 3, 2, 6},
			{ 40, 3, 3, 6, 6},
			{ 41, 4, 3, 6, 6},

			{ 42, 0, 4, 2, 6},
			{ 47, 3, 4, 6, 6},
			{ 48, 4, 4, 6, 6}
		};

		int inc = 0;

		// Function under test
		grid.Iterate(image, 5, 5, [&](const Region& window, const int& position) 
		{
				const auto exp = ar1[inc];
				EXPECT_EQ(exp[0], position);
				EXPECT_EQ(exp[1], window.upperLeft.x);
				EXPECT_EQ(exp[2], window.upperLeft.y);
				EXPECT_EQ(exp[3], window.bottomRight.x);
				EXPECT_EQ(exp[4], window.bottomRight.y);

				inc++;
		});

		EXPECT_EQ(9, inc);
	}

	TEST(GridCalcTests, GridCalcIterateEvenTest)
	{
		// Setup
		Image image(6, 6);

		GridCalc grid = GridCalc();

		// Expected values
		const int ar1[4][5] = {
			{ 0, 0, 0, 2, 2},
			{ 5, 3, 0, 5, 2},

			{ 30, 0, 3, 2, 5},
			{ 35, 3, 3, 5, 5}
		};

		int inc = 0;

		// Function under test
		grid.Iterate(image, 5, 5, [&](const Region& window, const int& position)
		{
			const auto exp = ar1[inc];
			EXPECT_EQ(exp[0], position);
			EXPECT_EQ(exp[1], window.upperLeft.x);
			EXPECT_EQ(exp[2], window.upperLeft.y);
			EXPECT_EQ(exp[3], window.bottomRight.x);
			EXPECT_EQ(exp[4], window.bottomRight.y);

			inc++;
		});

		EXPECT_EQ(4, inc);
	}

	TEST(GridCalcTests, GridCalcInterpolateTest)
	{
		// Setup
		const Pixel8 bits[] = {
			100, 0, 0, 80, 0, 0, 60,
			  0, 0, 0,  0, 0, 0,  0,
			  0, 0, 0,  0, 0, 0,  0,
			 90, 0, 0, 70, 0, 0, 50,
			  0, 0, 0,  0, 0, 0,  0,
			  0, 0, 0,  0, 0, 0,  0,
			100, 0, 0, 80, 0, 0, 60
		};
		Image image(7, 7, bits);

		GridCalc grid = GridCalc();

		grid.Interpolate(image, 3, [&](const int& position, const int& threshold)
		{
			image.data[position] = threshold;
		});

/*
  Directly taken from Moghaddam and Hedjam's interpolation_a_grid_on_domain
  Matlab routine, with a simple 3x3 dataset, expanded to 7x7.
  We store integers between 0-255, not decimals.

  100.0000   93.3333   86.6667   80.0000   73.3333   66.6667   60.0000
   96.6667   90.0000   83.3333   76.6667   70.0000   63.3333   56.6667
   93.3333   86.6667   80.0000   73.3333   66.6667   60.0000   53.3333
   90.0000   83.3333   76.6667   70.0000   63.3333   56.6667   50.0000
   93.3333   86.6667   80.0000   73.3333   66.6667   60.0000   53.3333
   96.6667   90.0000   83.3333   76.6667   70.0000   63.3333   56.6667
  100.0000   93.3333   86.6667   80.0000   73.3333   66.6667   60.0000
*/
		const Pixel8 expectedBits[] = {
			100, 93, 87, 80, 73, 67, 60,
			 97, 90, 83, 77, 70, 63, 57,
			 93, 87, 80, 73, 67, 60, 53,
			 90, 83, 77, 70, 63, 57, 50,
			 93, 87, 80, 73, 67, 60, 53,
			 97, 90, 83, 77, 70, 63, 57,
			100, 93, 87, 80, 73, 67, 60
		};

		TestUtilities::AssertImageData(image, expectedBits);
	}

	TEST(GridCalcTests, GridCalcInterpolateWideTest)
	{
		// Setup
		const Pixel8 bits[] = {
			100, 0, 0, 0, 80, 0, 0, 0, 60,
			  0, 0, 0, 0,  0, 0, 0, 0,  0,
			  0, 0, 0, 0,  0, 0, 0, 0,  0,
			  0, 0, 0, 0,  0, 0, 0, 0,  0,
			 90, 0, 0, 0, 70, 0, 0, 0, 50,
			  0, 0, 0, 0,  0, 0, 0, 0,  0,
			  0, 0, 0, 0,  0, 0, 0, 0,  0,
			100, 0, 0, 0, 80, 0, 0, 0, 60
		};
		Image image(9, 8, bits);

		GridCalc grid = GridCalc();

		grid.Interpolate(image, 4, [&](const int& position, const int& threshold)
		{
			image.data[position] = threshold;
		});

		const Pixel8 expectedBits[] = {
			100, 95, 90, 85, 80, 75, 70, 65, 60,
			 98, 93, 88, 83, 78, 73, 68, 63, 58,
			 95, 90, 85, 80, 75, 70, 65, 60, 55,
			 93, 88, 83, 78, 73, 68, 63, 58, 53,
			 90, 85, 80, 75, 70, 65, 60, 55, 50,
			 93, 88, 83, 78, 73, 68, 63, 58, 53,
			 97, 92, 87, 82, 77, 72, 67, 62, 57,
			100, 95, 90, 85, 80, 75, 70, 65, 60
		};

		TestUtilities::AssertImageData(image, expectedBits);
	}

	TEST(GridCalcTests, GridCalcInterpolatePlusOneTest)
	{
		// Setup
		const Pixel8 bits[] = {
			100, 0, 0, 80, 0, 0, 60,  40,
			  0, 0, 0,  0, 0, 0,  0,   0,
			  0, 0, 0,  0, 0, 0,  0,   0,
			 90, 0, 0, 70, 0, 0, 50,  60,
			  0, 0, 0,  0, 0, 0,  0,   0,
			  0, 0, 0,  0, 0, 0,  0,   0,
			100, 0, 0, 60, 0, 0, 60, 100,
			 40, 0, 0, 60, 0, 0, 80, 100
		};
		Image image(8, 8, bits);

		GridCalc grid = GridCalc();

		grid.Interpolate(image, 3, [&](const int& position, const int& threshold)
		{
				image.data[position] = threshold;
		});

		const Pixel8 expectedBits[] = {
			100, 93, 87, 80, 73, 67, 60,  40,
			 97, 90, 83, 77, 70, 63, 57,  47,
			 93, 87, 80, 73, 67, 60, 53,  53,
			 90, 83, 77, 70, 63, 57, 50,  60,
			 93, 84, 76, 67, 62, 58, 53,  73,
			 97, 86, 74, 63, 61, 59, 57,  87,
			100, 87, 73, 60, 60, 60, 60, 100,
			 40, 47, 53, 60, 67, 73, 80, 100
		};

		TestUtilities::AssertImageData(image, expectedBits);
	}

	TEST(GridCalcTests, GridCalcInterpolatePlusTwoTest)
	{
		// Setup
		const uint8_t bits[] = {
			100, 0, 0, 80, 0, 0, 60, 0,  40,
			  0, 0, 0,  0, 0, 0,  0, 0,   0,
			  0, 0, 0,  0, 0, 0,  0, 0,   0,
			 90, 0, 0, 70, 0, 0, 50, 0,  60,
			  0, 0, 0,  0, 0, 0,  0, 0,   0,
			  0, 0, 0,  0, 0, 0,  0, 0,   0,
			100, 0, 0, 60, 0, 0, 60, 0, 100,
			  0, 0, 0,  0, 0, 0,  0, 0,   0,
			 40, 0, 0, 60, 0, 0, 80, 0, 100
		};
		Image image(9, 9, bits);

		GridCalc grid = GridCalc();

		grid.Interpolate(image, 3, [&](const int& position, const int& threshold)
		{
			image.data[position] = threshold;
		});

		const Pixel8 expectedBits[] = {
			100, 93, 87, 80, 73, 67, 60, 50,  40,
			 97, 90, 83, 77, 70, 63, 57, 52,  47,
			 93, 87, 80, 73, 67, 60, 53, 53,  53,
			 90, 83, 77, 70, 63, 57, 50, 55,  60,
			 93, 84, 76, 67, 62, 58, 53, 63,  73,
			 97, 86, 74, 63, 61, 59, 57, 72,  87,
			100, 87, 73, 60, 60, 60, 60, 80, 100,
			 70, 67, 63, 60, 63, 67, 70, 85, 100,
			 40, 47, 53, 60, 67, 73, 80, 90, 100
		};

		TestUtilities::AssertImageData(image, expectedBits);
	}
}
