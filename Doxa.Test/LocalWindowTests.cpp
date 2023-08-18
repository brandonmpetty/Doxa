#include "pch.h"


namespace Doxa::UnitTests
{
	TEST(LocalWindowTests, LocalWindowIterateTest)
	{
		// Build dummy image for a 3x3 window
		// This array will be updated by our iterator
		Pixel8 data[] =
			{  1,  2,  3,  4,  5,  6,
				7,  8,  9, 10, 11, 12,
				13, 14, 15, 16, 17, 18,
				19, 20, 21, 22, 23, 24,
				25, 26, 27, 28, 29, 30,
				31, 32, 33, 34, 35, 36  };

		Image image(6, 6, data);

		// Test that we can iterate a 3x3 window around our image
		LocalWindow::Iterate(image, 3, [&](const Region& window, const int& positionImage) {

			int sum = 0;

			LocalWindow::Iterate(image.width, window, [&](const int& positionWindow) {
				sum += image.data[positionWindow];
			});

			data[positionImage] = (std::min)(sum, 255);
		});

		// Compare to our known output
		const Pixel8 expected[] =
			{  18,  30,  36,  42,  48,  34,
				45,  72,  81,  90,  99,  69,
				81, 126, 135, 144, 153, 105,
				117, 180, 189, 198, 207, 141,
				153, 234, 243, 252, 255, 177,
				114, 174, 180, 186, 192, 130  };

		EXPECT_TRUE(std::equal(std::begin(data), std::end(data), std::begin(expected), std::end(expected)));
	}
}
