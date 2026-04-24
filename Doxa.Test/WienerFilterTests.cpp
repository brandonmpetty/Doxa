#include "pch.h"
#include "TestUtilities.hpp"
#include <WienerFilter.hpp>


namespace Doxa::UnitTests
{
	// A Wiener filter (per MATLAB's wiener2) is an adaptive denoiser.
	// For each pixel, given local mean (m) and local variance (v):
	//
	// This test uses a flat background with a single bright pixel.  The expected
	// behavior is:
	//   - All windows that don't see the bright pixel have v=0, output = m = input.
	//   - The 9 windows containing the bright pixel get smoothed: the bright pixel
	//     is pulled down toward its local mean, the 8 neighbors nudged up.
	TEST(WienerFilterTests, WienerFilterCenterPixelTest)
	{
		const Pixel8 data[] = {
			50, 50, 50,  50, 50, 50, 50,
			50, 50, 50,  50, 50, 50, 50,
			50, 50, 50,  50, 50, 50, 50,
			50, 50, 50, 100, 50, 50, 50, // Bright pixel at (3,3)
			50, 50, 50,  50, 50, 50, 50,
			50, 50, 50,  50, 50, 50, 50,
			50, 50, 50,  50, 50, 50, 50
		};

		// Derivation:
		//   9 windows contain the spike:  m = (8*50 + 100)/9 = 500/9,  v = 20000/81
		//   40 flat windows:              m = 50,               v = 0
		//   noiseVar = (9 * 20000/81) / 49 = 180000/3969
		//   noiseVar / v = 9/49,  so the dampening factor (1 - noiseVar/v) = 40/49
		//
		// Center spike (input = 100):
		//   out = 500/9 + (40/49)*(100 - 500/9) = 40500/441 ~= 91.837 -> 91 (uint8 trunc)
		//
		// 8 neighbors (input = 50):
		//   out = 500/9 + (40/49)*( 50 - 500/9) = 22500/441 ~= 51.020 -> 51
		const Pixel8 expected[] = {
			50, 50, 50, 50, 50, 50, 50,
			50, 50, 50, 50, 50, 50, 50,
			50, 50, 51, 51, 51, 50, 50,
			50, 50, 51, 91, 51, 50, 50,
			50, 50, 51, 51, 51, 50, 50,
			50, 50, 50, 50, 50, 50, 50,
			50, 50, 50, 50, 50, 50, 50
		};

		const Image inputImage(7, 7, data);
		Image outputImage(7, 7);

		WienerFilter::Filter(outputImage, inputImage, 3);

		TestUtilities::AssertImageData(outputImage, expected);
	}
}
