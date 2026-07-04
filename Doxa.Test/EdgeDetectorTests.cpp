#include "pch.h"
#include "ImageFixture.hpp"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	// Exposes protected members for Unit Testing
	class EdgeDetectorTestharness : public EdgeDetector
	{
	public:
		using EdgeDetector::NonMaxSuppressAndClassify;
		using EdgeDetector::Hysteresis;
	};

	class EdgeDetectorTests : public ImageFixture {};

	TEST_F(EdgeDetectorTests, EdgeDetectorSobelTest)
	{
		Image edges(image.width, image.height);
		EdgeDetector::Sobel(edges, image);

		TestUtilities::AssertImageFile(edges, projFolder + "2JohnC1V3-Sobel.pgm");
	}

	TEST_F(EdgeDetectorTests, EdgeDetectorLaplacianTest)
	{
		Image edges(image.width, image.height);
		EdgeDetector::Laplacian(edges, image);

		TestUtilities::AssertImageFile(edges, projFolder + "2JohnC1V3-Laplacian.pgm");
	}

	TEST_F(EdgeDetectorTests, EdgeDetectorCannyTest)
	{
		const Parameters parameters({
			{ "gaussian-size", 5 }, { "sigma", 0.0 },
			{ "low", 50 }, { "high", 150 }
		});

		Image edges(image.width, image.height);
		EdgeDetector::Canny(edges, image, parameters);

		TestUtilities::AssertImageFile(edges, projFolder + "2JohnC1V3-Canny.pbm");
	}

	// -- Canny Stage Tests --
	// Pin the two protected units Canny calls: NonMaxSuppressAndClassify
	// (step 4) and Hysteresis (step 5).  Filter::Gaussian (step 1) is
	// covered by FilterTests.

	TEST_F(EdgeDetectorTests, CannyNonMaxSuppressTest)
	{
		// Synthetic 5x5 magnitude grid with two horizontal ridges and
		// dir=0 (W/E comparison) everywhere.  Pins all five outcomes:
		// border=0, suppressed neighbor=0, below-low=0, weak=128, strong=255.
		const int W = 5, H = 5;
		const std::vector<int> mag = {
			  0,   0,   0,   0,   0,
			  0,  10,  20,  10,   0,
			  0,  40, 200,  40,   0,
			  0,  40, 100,  40,   0,
			  0,   0,   0,   0,   0,
		};
		const std::vector<uint8_t> dir(W * H, 0);

		Image out(W, H);
		std::vector<int> seeds;

		EdgeDetectorTestharness::NonMaxSuppressAndClassify(
			out, seeds, mag.data(), dir.data(), W, H, /*low=*/30, /*high=*/150);

		const Pixel8 expected[] = {
			  0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,
			  0,   0, 255,   0,   0,
			  0,   0, 128,   0,   0,
			  0,   0,   0,   0,   0,
		};
		TestUtilities::AssertImageData(out, expected);

		ASSERT_EQ(1u, seeds.size());
		EXPECT_EQ(2 * W + 2, seeds[0]);  // (row 2, col 2)
	}

	TEST_F(EdgeDetectorTests, CannyHysteresisTest)
	{
		// Strong seed at (2,2) with a chain of weak pixels at (1,1), (1,2),
		// (2,1) -- all 8-connected to the seed.  An isolated weak pixel at
		// (4,4) has no strong neighbor.  After BFS the chain is promoted
		// to 255 and the isolated weak is cleared to 0.
		const int W = 5, H = 5;
		const Pixel8 initial[] = {
			  0,   0,   0,   0,   0,
			  0, 128, 128,   0,   0,
			  0, 128, 255,   0,   0,
			  0,   0,   0,   0,   0,
			  0,   0,   0,   0, 128,
		};
		Image out(W, H, initial);
		std::vector<int> seeds = { 2 * W + 2 };

		EdgeDetectorTestharness::Hysteresis(out, seeds, W, H);

		const Pixel8 expected[] = {
			  0,   0,   0,   0,   0,
			  0, 255, 255,   0,   0,
			  0, 255, 255,   0,   0,
			  0,   0,   0,   0,   0,
			  0,   0,   0,   0,   0,
		};
		TestUtilities::AssertImageData(out, expected);
	}
}
