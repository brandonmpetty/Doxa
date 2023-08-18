#include "pch.h"
#include "ImageFixture.hpp"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class MorphologyTests : public ImageFixture {};

	class MorphologyTestHarness : public Morphology
	{
	public:
		MorphologyTestHarness() : Morphology() {}
		using Morphology::Morph;
		using Morphology::IterativelyErode;
		using Morphology::IterativelyDilate;
	};


	TEST_F(MorphologyTests, MorphologyErodeTest)
	{
		const Pixel8 data[] = {
			1,  2,  3,  4,  5,  6,
			7,  8,  9, 10, 11, 12,
			13, 14, 15, 16, 50, 18, // Note 5th column
			19, 20,  3, 22, 23, 24, // Note 3rd column
			25, 26, 27, 28, 29, 30,
			31, 32, 33, 34, 35, 36
		};

		// For each row (y) in data, calculate the min value within the window for that row
		const Pixel8 minArrayX[] = {
			1,  1,  2,  3,  4,  5,
			7,  7,  8,  9, 10, 11,
			13, 13, 14, 15, 16, 18,
			19,  3,  3,  3, 22, 23,
			25, 25, 26, 27, 28, 29,
			31, 31, 32, 33, 34, 35
		};

		// For each column (x) in minArrayX, calculate the min value within the window for that column
		const Pixel8 minArray[] = {
			1,  1,  2,  3,  4,  5,
			1,  1,  2,  3,  4,  5,
			7,  3,  3,  3, 10, 11,
			13,  3,  3,  3, 16, 18,
			19,  3,  3,  3, 22, 23,
			25, 25, 26, 27, 28, 29
		};

		const Image grayScaleImage(6, 6, data);

		Image erodedImage(6, 6);
		Morphology::Erode(erodedImage, grayScaleImage, 3);

		TestUtilities::AssertImageData(erodedImage, minArray);
	}

	TEST_F(MorphologyTests, MorphologyDilateTest)
	{
		const Pixel8 data[] = {
			1,  2,  3,  4,  5,  6,
			7,  8,  9, 10, 11, 12,
			13, 14, 15, 16, 50, 18, // Note 5th column
			19, 20,  3, 22, 23, 24, // Note 3rd column
			25, 26, 27, 28, 29, 30,
			31, 32, 33, 34, 35, 36
		};

		// For each row (y) in data, calculate the max value within the window for that row
		const Pixel8 maxArrayX[] = {
			2,  3,  4,  5,  6,  6,
			8,  9, 10, 11, 12, 12,
			14, 15, 16, 50, 50, 50,
			20, 20, 22, 23, 24, 24,
			26, 27, 28, 29, 30, 30,
			32, 33, 34, 35, 36, 36
		};

		// For each column (x) in maxArrayX, calculate the max value within the window for that column
		const Pixel8 maxArray[] = {
			8,  9, 10, 11, 12, 12,
			14, 15, 16, 50, 50, 50,
			20, 20, 22, 50, 50, 50,
			26, 27, 28, 50, 50, 50,
			32, 33, 34, 35, 36, 36,
			32, 33, 34, 35, 36, 36
		};

		const Image grayScaleImage(6, 6, data);

		Image dilatedImage(6, 6);
		Morphology::Dilate(dilatedImage, grayScaleImage, 3);

		TestUtilities::AssertImageData(dilatedImage, maxArray);
	}

	// TODO: Update this test to force calls to Morph(...), IterativelyDilate(...), etc using a test harness.
	TEST_F(MorphologyTests, MorphologySpeedTest)
	{
		// Find sample image
		const std::string filePath = TestUtilities::ProjectFolder() + "2JohnC1V3.ppm";

		// Read image
		Image grayScaleImage = PNM::Read(filePath);
		Image wanBinary(grayScaleImage.width, grayScaleImage.height);

		// Window Size 17 is the tipping for my CPU.  This will trigger the Morph algorithm to be applied.
		Parameters parameters({ { "window", 17 },{ "k", 0.2 } });

		// Time algorithms
		double wanMorphedSpeed = TestUtilities::Time([&]() {
			Wan wan;
			wan.Initialize(grayScaleImage);
			wan.ToBinary(wanBinary, parameters);
		});

		// This window size will trigger a manual window analysis to be ran.
		// This is faster for small window sizes, but very costly for large windows.
		parameters.Set("window", 15);
		double wanSpeed = TestUtilities::Time([&]() {
			Wan wan;
			wan.Initialize(grayScaleImage);
			wan.ToBinary(wanBinary, parameters);
		});

		SUCCEED() << "Morphed Wan Speed (W=17): " << wanMorphedSpeed;
		SUCCEED() << "Manual Wan Speed (W=15): " << wanSpeed;
		EXPECT_TRUE(wanSpeed < wanMorphedSpeed);
	}

	TEST_F(MorphologyTests, MorphologyErodeComparisonTest)
	{
		const int windowSize = 25;
		Image morphedImage(image.width, image.height);
		Image iterativelyMorphedImage(image.width, image.height);

		// Manually find the min within each window
		MorphologyTestHarness::IterativelyErode(iterativelyMorphedImage, image, windowSize);

		// Utilize a Max Image to speed up the morphology transformation
		MorphologyTestHarness::Morph(morphedImage, image, windowSize, [](const std::multiset<Pixel8>& set) {
			return *set.begin(); // Min Value
		});

		TestUtilities::AssertImages(iterativelyMorphedImage, morphedImage);
	}

	TEST_F(MorphologyTests, MorphologyDilateComparisonTest)
	{
		const int windowSize = 25;
		Image morphedImage(image.width, image.height);
		Image iterativelyMorphedImage(image.width, image.height);

		// Manually find the max within each window
		MorphologyTestHarness::IterativelyDilate(iterativelyMorphedImage, image, windowSize);

		// Utilize a Max Image to speed up the morphology transformation
		MorphologyTestHarness::Morph(morphedImage, image, windowSize, [](const std::multiset<Pixel8>& set) {
			return *std::prev(set.end()); // Max Value
		});

		TestUtilities::AssertImages(iterativelyMorphedImage, morphedImage);
	}
}
