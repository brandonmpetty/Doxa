#include "TestUtilities.hpp"
#include "../Morphology.hpp"
#include "../Wan.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(MorphologyTests)
	{
		/// <summary>
		/// A modified version of WAN that uses Dilate instead of CalculateMax.
		/// Both should produce an identical image.
		/// </summary>
		class WanMorphed : public Algorithm<Wan>, public MeanVarianceCalculator
		{
		public:
			void Initialize(const Image& grayScaleImageIn)
			{
				Algorithm::Initialize(grayScaleImageIn);
				MeanVarianceCalculator::Initialize(grayScaleImageIn);
			}

			void ToBinary(Image& binaryImageOut, const Parameters& parameters)
			{
				double mean, stddev;

				// Read parameters, utilizing defaults
				const int windowSize = parameters.Get("window", 75);
				const double k = parameters.Get("k", 0.2);

				// Use Dilate to generate a Max Image
				Image maxImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
				Morphology::Dilate(maxImage, Algorithm::grayScaleImageIn, windowSize);

				LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
					CalculateMeanStdDev(mean, stddev, window);

					return (((double)maxImage.data[position] + mean) / 2) * (1 + k * ((stddev / 128) - 1));
				});
			}
		};

	public:

		TEST_METHOD(MorphologyErodeTest)
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

		TEST_METHOD(MorphologyDilateTest)
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

		TEST_METHOD(MorphologySpeedTest)
		{
			// Find sample image
			std::string projFolder = EXPAND(UNITTESTPRJ);
			projFolder.erase(0, 1);
			projFolder.erase(projFolder.size() - 2);

			const std::string filePath = projFolder + "2JohnC1V3.ppm";

			// Read image
			Image grayScaleImage = PNM::Read(filePath);
			Image wanMorphedBinary(grayScaleImage.width, grayScaleImage.height);
			Image wanBinary(grayScaleImage.width, grayScaleImage.height);

			// Window Size 13 is the tipping for my CPU.
			const Parameters parameters({ { "window", 25 },{ "k", 0.2 } });

			// Time both algorithms
			double wanMorphedSpeed = TestUtilities::Time([&]() {
				WanMorphed wan;
				wan.Initialize(grayScaleImage);
				wan.ToBinary(wanMorphedBinary, parameters);
			});

			double wanSpeed = TestUtilities::Time([&]() {
				Wan wan;
				wan.Initialize(grayScaleImage);
				wan.ToBinary(wanBinary, parameters);
			});

			// Assert correctness
			TestUtilities::AssertImages(wanMorphedBinary, wanBinary);

			Logger::WriteMessage(("WanMorphedSpeed: " + std::to_string(wanMorphedSpeed)).c_str());
			Logger::WriteMessage(("WanSpeed: " + std::to_string(wanSpeed)).c_str());
			Assert::IsTrue(wanMorphedSpeed < wanSpeed);
		}
	};
}
