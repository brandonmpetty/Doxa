#include <random>
#include "pch.h"
#include "ImageFixture.hpp"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class MorphologyTests : public ImageFixture
	{
	protected:
		/// <summary>
		/// Reference implementation: directly scan every clipped window.
		/// Slow, but obviously correct.  Used to validate the vHGW implementation.
		/// </summary>
		template<typename MinMax>
		static Image NaiveMorph(const Image& source, const int windowSize, MinMax op)
		{
			Image morphedImage(source.width, source.height);
			const int half = windowSize / 2;

			for (int y = 0; y < source.height; ++y)
			{
				for (int x = 0; x < source.width; ++x)
				{
					Pixel8 value = source.Pixel(x, y);

					for (int wy = (std::max)(0, y - half); wy <= (std::min)(source.height - 1, y + half); ++wy)
					{
						for (int wx = (std::max)(0, x - half); wx <= (std::min)(source.width - 1, x + half); ++wx)
						{
							value = op(value, source.Pixel(wx, wy));
						}
					}

					morphedImage.Pixel(x, y) = value;
				}
			}

			return morphedImage;
		}

		static Pixel8 Min(const Pixel8 a, const Pixel8 b) { return (std::min)(a, b); }
		static Pixel8 Max(const Pixel8 a, const Pixel8 b) { return (std::max)(a, b); }
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

	TEST_F(MorphologyTests, MorphologyReferenceComparisonTest)
	{
		// Deterministic noise with odd dimensions, to exercise partial vHGW blocks
		Image noise(97, 61);
		std::mt19937 prng(42);
		for (int idx = 0; idx < noise.size; ++idx)
		{
			noise.data[idx] = prng() % 256;
		}

		Image morphedImage(noise.width, noise.height);

		// Odd and even sizes, and windows larger than the image itself
		for (const int windowSize : { 1, 2, 3, 4, 5, 8, 9, 16, 17, 25, 60, 61, 75, 255 })
		{
			SCOPED_TRACE("Window Size: " + std::to_string(windowSize));

			Morphology::Erode(morphedImage, noise, windowSize);
			TestUtilities::AssertImages(morphedImage, NaiveMorph(noise, windowSize, Min));

			Morphology::Dilate(morphedImage, noise, windowSize);
			TestUtilities::AssertImages(morphedImage, NaiveMorph(noise, windowSize, Max));
		}
	}

	TEST_F(MorphologyTests, MorphologyFixtureComparisonTest)
	{
		Image morphedImage(image.width, image.height);

		// An odd size, and an even size like those MultiScale generates
		for (const int windowSize : { 18, 25 })
		{
			SCOPED_TRACE("Window Size: " + std::to_string(windowSize));

			Morphology::Erode(morphedImage, image, windowSize);
			TestUtilities::AssertImages(morphedImage, NaiveMorph(image, windowSize, Min));

			Morphology::Dilate(morphedImage, image, windowSize);
			TestUtilities::AssertImages(morphedImage, NaiveMorph(image, windowSize, Max));
		}
	}

	TEST_F(MorphologyTests, MorphologyInPlaceTest)
	{
		Image expectedImage(image.width, image.height);
		Morphology::Dilate(expectedImage, image, 25);

		Image morphedImage(image);
		Morphology::Dilate(morphedImage, morphedImage, 25);

		TestUtilities::AssertImages(morphedImage, expectedImage);
	}
}
