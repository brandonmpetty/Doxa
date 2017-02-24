#include "CppUnitTest.h"
#include "../Algorithms.hpp"
#include "../ShafaitCalculator.hpp"
#include "../PPM.hpp"
#include "../Preprocessor.hpp"
#include "../Performance.hpp"
#include "../MetricUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(MetricUtilsTests)
	{
		TEST_METHOD(MetricUtilsAccuracyTest)
		{
			// Build a small image.  This image mirrors the one used in our Shafait calculator tests.
			Pixel32 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image grayScaleImage(3, 3, bits);

			const int windowSize = 3;
			const double k = 0.15;

			// Create a psuedo ground truth to verify that we can detect 100% accuracy
			Image imageSauvolaShafait(grayScaleImage.width, grayScaleImage.height);
			Algorithms::Sauvola<Shafait>(imageSauvolaShafait, grayScaleImage, windowSize, k);

			Image imageSauvolaShafait2(grayScaleImage.width, grayScaleImage.height);
			Algorithms::Sauvola<Shafait>(imageSauvolaShafait2, grayScaleImage, windowSize, k);

			// Verify that our performance calculator is operational
			double accuracy = Performance::CalculateAccuracy(imageSauvolaShafait, imageSauvolaShafait2);
			Assert::AreEqual(accuracy, 100.00);

			// Search parameters
			const int windowSizeStart = 1;
			const int windowSizeStop = 3;
			const double kStart = 0.10;
			const double kStop = 0.20;

			// Calculate Best Accuracy Stats
			MetricUtils::Score score = MetricUtils::Accuracy(imageSauvolaShafait, grayScaleImage, windowSizeStart, windowSizeStop, kStart, kStop,
				[](Image& binaryImageOut, const Image& grayScaleImageIn, const int ws, const double k) {
					Algorithms::Sauvola<Shafait>(binaryImageOut, grayScaleImageIn, ws, k);
			});

			// Note: We cannot assert windowSize nor k, because other values could also achieve 100% accuracy.
			Assert::AreEqual(score.accuracy, 100.00);
			Assert::AreEqual(score.fmeasure, 100.00);
			Assert::AreEqual(score.psnr, std::numeric_limits<double>::infinity());
			Assert::AreEqual(score.total, std::numeric_limits<double>::infinity());
		}
	};
}
