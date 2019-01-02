#include "CppUnitTest.h"
#include "../ClassifiedPerformance.hpp"
#include "../DRDM.hpp"
#include "../Palette.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(PerformanceTests)
	{
	public:

		TEST_METHOD(PerformanceClassificationsTest)
		{
			ClassifiedPerformance::Classifications classification;
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
			ClassifiedPerformance::Classifications classifications;
			bool ret = ClassifiedPerformance::CompareImages(classifications, control, experiment);
			Assert::IsTrue(ret);

			// Assert correctness
			Assert::AreEqual(classifications.truePositive, 4);
			Assert::AreEqual(classifications.trueNegative, 3);
			Assert::AreEqual(classifications.falsePositive, 1);
			Assert::AreEqual(classifications.falseNegative, 1);

			// Calculate Performance
			Assert::AreEqual(ClassifiedPerformance::CalculateAccuracy(classifications), 77.777, 0.001);

			Assert::AreEqual(ClassifiedPerformance::CalculateFMeasure(classifications), 80.0, 0.001);

			Assert::AreEqual(ClassifiedPerformance::CalculatePSNR(classifications), 6.532, 0.001);

			// TODO - Calculate the NRM and verify
			//Assert::AreEqual(ClassifiedPerformance::CalculateNRM(classifications), 0.00, 0.001);
		}

		TEST_METHOD(DRDMTest)
		{
			// (3, 4) = Black is changed to White
			// One 8x8 Block with a 5x5 Window
			Pixel8 dataGT[] = {
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::Black, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::Black,  Palette::Black,  Palette::Black,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::Black, Palette::White,
				Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::Black,
			};
			Image groundTruthImage(8, 8, dataGT);

			Pixel8 dataExp[] = {
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::Black, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::Black,  Palette::White,  Palette::Black,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::White,
				Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::Black, Palette::White,
				Palette::White,  Palette::Black,  Palette::White,  Palette::White,  Palette::White,  Palette::White, Palette::White, Palette::Black,
			};
			Image expImage(8, 8, dataExp);

			double drdm = DRDM::CalculateDRDM(groundTruthImage, expImage);

			Assert::AreEqual((72357 + 72357 + 32359) / (double)1000000, drdm);
		}
	};
}
