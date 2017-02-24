#include "CppUnitTest.h"
#include "../Performance.hpp"
#include "../Palette.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(PerformanceTests)
	{
	public:

		TEST_METHOD(PerformanceClassificationsTest)
		{
			Performance::Classifications classification;
			classification.truePositive = 3;
			classification.trueNegative = 5;
			classification.falsePositive = 7;
			classification.falseNegative = 11;

			Assert::AreEqual(classification.Total(), 26);

			classification.Clear();

			Assert::AreEqual(classification.Total(), 0);
		}

		TEST_METHOD(PerformanceTest)
		{
			Image control(3, 3);
			control.Pixel(0, 0) = Palette::Black;
			control.Pixel(1, 0) = Palette::White;
			control.Pixel(2, 0) = Palette::Black;
			control.Pixel(0, 1) = Palette::White;
			control.Pixel(1, 1) = Palette::Black;
			control.Pixel(2, 1) = Palette::White;
			control.Pixel(0, 2) = Palette::Black;
			control.Pixel(1, 2) = Palette::White;
			control.Pixel(2, 2) = Palette::Black;

			Image experiment(3, 3);
			experiment.Pixel(0, 0) = Palette::Black;
			experiment.Pixel(1, 0) = Palette::White;
			experiment.Pixel(2, 0) = Palette::White; // False Negative
			experiment.Pixel(0, 1) = Palette::White;
			experiment.Pixel(1, 1) = Palette::Black;
			experiment.Pixel(2, 1) = Palette::White;
			experiment.Pixel(0, 2) = Palette::Black;
			experiment.Pixel(1, 2) = Palette::Black; // False Positive
			experiment.Pixel(2, 2) = Palette::Black;

			// Compare
			Performance::Classifications classifications;
			bool ret = Performance::CompareImages(classifications, control, experiment);
			Assert::IsTrue(ret);

			// Assert correctness
			Assert::AreEqual(classifications.truePositive, 4);
			Assert::AreEqual(classifications.trueNegative, 3);
			Assert::AreEqual(classifications.falsePositive, 1);
			Assert::AreEqual(classifications.falseNegative, 1);

			// Calculate Performance
			Assert::AreEqual(Performance::CalculateAccuracy(classifications), 77.777, 0.001);

			Assert::AreEqual(Performance::CalculateFMeasure(classifications), 80.0, 0.001);

			Assert::AreEqual(Performance::CalculatePSNR(classifications), 6.532, 0.001);
		}
	};
}
