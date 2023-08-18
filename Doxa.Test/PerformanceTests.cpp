#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	TEST(PerformanceTests, PerformanceClassificationsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 3;
		classification.trueNegative = 5;
		classification.falsePositive = 7;
		classification.falseNegative = 11;

		EXPECT_EQ(classification.Total(), 26);

		classification.Clear();

		EXPECT_EQ(classification.Total(), 0);
	}

	TEST(PerformanceTests, PerformanceTest)
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
		const bool ret = ClassifiedPerformance::CompareImages(classifications, control, experiment);
		EXPECT_TRUE(ret);

		// Assert correctness
		EXPECT_EQ(classifications.truePositive, 4);
		EXPECT_EQ(classifications.trueNegative, 3);
		EXPECT_EQ(classifications.falsePositive, 1);
		EXPECT_EQ(classifications.falseNegative, 1);

		// Calculate Performance
		EXPECT_NEAR(ClassifiedPerformance::CalculateAccuracy(classifications), 77.777, 0.001);

		EXPECT_NEAR(ClassifiedPerformance::CalculateFMeasure(classifications), 80.0, 0.001);

		EXPECT_NEAR(ClassifiedPerformance::CalculatePSNR(classifications), 6.532, 0.001);

		// TODO - Calculate the NRM and verify
		//EXPECT_EQ(ClassifiedPerformance::CalculateNRM(classifications), 0.00);
	}

	TEST(PerformanceTests, PSNRBoundsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 3;
		classification.trueNegative = 5;
		classification.falsePositive = 0; // Possible Divide By Zero
		classification.falseNegative = 0; // Possible Divide By Zero

		EXPECT_TRUE(ClassifiedPerformance::CalculatePSNR(classification) > 1000);
	}

	TEST(PerformanceTests, FMeasureBoundsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 0; // Possible Divide By Zero
		classification.trueNegative = 5;
		classification.falsePositive = 7;
		classification.falseNegative = 11;

		EXPECT_EQ(ClassifiedPerformance::CalculateFMeasure(classification), 0.0);
	}

	TEST(PerformanceTests, NRMBoundsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 0; // Possible Divide By Zero
		classification.trueNegative = 5;
		classification.falsePositive = 7;
		classification.falseNegative = 0; // Possible Divide By Zero

		EXPECT_TRUE(ClassifiedPerformance::CalculateNRM(classification) > 1000);
	}

	TEST(PerformanceTests, DRDMTest)
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

		EXPECT_EQ((72357 + 72357 + 32359) / (double)1000000, drdm);
	}

	TEST(PerformanceTests, MCCTest)
	{
		// Numbers and expected value pulled from: https://en.wikipedia.org/wiki/Matthews_correlation_coefficient
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 6;
		classification.trueNegative = 3;
		classification.falsePositive = 1;
		classification.falseNegative = 2;

		EXPECT_NEAR(ClassifiedPerformance::CalculateMCC(classification), 0.478, 0.001);
	}

	TEST(PerformanceTests, MCCTest_LargeValues)
	{
		// MCC will generate some extremely large values.  Ensure we can handle those by using a real image.
		std::string projFolder = TestUtilities::ProjectFolder();

		const std::string filePathBinary = projFolder + "2JohnC1V3-Sauvola.pbm";
		Image binaryImage = PNM::Read(filePathBinary);

		const std::string filePathGT = projFolder + "2JohnC1V3-GroundTruth.pbm";
		Image groundTruthImage = PNM::Read(filePathGT);

		ClassifiedPerformance::Classifications classifications;
		bool canCompare = ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
		EXPECT_TRUE(canCompare);

		double result = ClassifiedPerformance::CalculateMCC(classifications);
		EXPECT_NEAR(result, 0.918, 0.001);
	}
}
