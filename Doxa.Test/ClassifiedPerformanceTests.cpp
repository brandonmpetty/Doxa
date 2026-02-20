#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	TEST(ClassifiedPerformanceTests, PerformanceClassificationsTest)
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

	TEST(ClassifiedPerformanceTests, PerformanceTest)
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

	TEST(PerformanceTests, PseudoMetrics)
	{
		// NOTE: Based off of 2018 DIBCO Metrics PR sample
		ClassifiedPerformance::Classifications classification;

		/*
		std::string projFolder = TestUtilities::ProjectFolder();
		auto precisionWeights = DIBCOUtils::ReadWeightsFile(projFolder + "PR_PWeights.dat");
		auto recallWeights = DIBCOUtils::ReadWeightsFile(projFolder + "PR_RWeights.dat");
		auto controlImage = PNM::Read(projFolder + "PR_GT.pbm");
		auto experimentImage = PNM::Read(projFolder + "PR_bin.pbm");

		ClassifiedPerformance::CompareImages(classification, controlImage, experimentImage, precisionWeights, recallWeights);
		*/

		classification.truePositive = 61573;
		classification.trueNegative = 251404;
		classification.falsePositive = 1929;
		classification.falseNegative = 6493;
		classification.wpTruePositive = 0.0;
		classification.wpFalsePositive = 644.86664099999996;
		classification.wrTruePositive = 11562.182811000408;
		classification.wrFalseNegative = 64.369443000000018;

		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoPrecision(classification), 95.9875, 0.0001);
		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoRecall(classification), 99.4464, 0.0001);
		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoFMeasure(classification), 97.6863, 0.0001);
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

	TEST(ClassifiedPerformanceTests, FMeasureBoundsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 0; // Possible Divide By Zero
		classification.trueNegative = 5;
		classification.falsePositive = 7;
		classification.falseNegative = 11;

		EXPECT_EQ(ClassifiedPerformance::CalculateFMeasure(classification), 0.0);
	}

	TEST(ClassifiedPerformanceTests, NRMBoundsTest)
	{
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 0; // Possible Divide By Zero
		classification.trueNegative = 5;
		classification.falsePositive = 7;
		classification.falseNegative = 0; // Possible Divide By Zero

		EXPECT_TRUE(ClassifiedPerformance::CalculateNRM(classification) > 1000);
	}

	TEST(ClassifiedPerformanceTests, MCCTest)
	{
		// Numbers and expected value pulled from: https://en.wikipedia.org/wiki/Matthews_correlation_coefficient
		ClassifiedPerformance::Classifications classification;
		classification.truePositive = 6;
		classification.trueNegative = 3;
		classification.falsePositive = 1;
		classification.falseNegative = 2;

		EXPECT_NEAR(ClassifiedPerformance::CalculateMCC(classification), 0.478, 0.001);
	}

	TEST(ClassifiedPerformanceTests, ClassifiedPerformanceSauvola)
	{
		std::string projFolder = TestUtilities::ProjectFolder();

		// Grayscale Image
		const std::string filePathBinary = projFolder + "2JohnC1V3-Sauvola.pbm";
		Image binaryImage = PNM::Read(filePathBinary);

		// Ground Truth
		const std::string filePathGT = projFolder + "2JohnC1V3-GroundTruth.pbm";
		Image groundTruthImage = PNM::Read(filePathGT);

		// Load Pseudo Weights
		const std::string filePathRWeights = projFolder + "2JohnC1V3-GroundTruth_RWeights.dat";
		auto rWeights = DIBCOUtils::ReadWeightsFile(filePathRWeights);

		const std::string filePathPWeights = projFolder + "2JohnC1V3-GroundTruth_PWeights.dat";
		auto pWeights = DIBCOUtils::ReadWeightsFile(filePathPWeights);

		// Run Classified Metrics
		ClassifiedPerformance::Classifications classifications;
		bool canCompare = ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage, pWeights, rWeights);
		EXPECT_TRUE(canCompare);

		const double accuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
		const double fm = ClassifiedPerformance::CalculateFMeasure(classifications);
		const double recall = ClassifiedPerformance::CalculateRecall(classifications);
		const double precision = ClassifiedPerformance::CalculatePrecision(classifications);
		const double pfm = ClassifiedPerformance::CalculatePseudoFMeasure(classifications);
		const double precall = ClassifiedPerformance::CalculatePseudoRecall(classifications);
		const double pprecision = ClassifiedPerformance::CalculatePseudoPrecision(classifications);
		const double mcc = ClassifiedPerformance::CalculateMCC(classifications);
		const double nrm = ClassifiedPerformance::CalculateNRM(classifications);
		const double psnr = ClassifiedPerformance::CalculatePSNR(classifications);

		// Test
		EXPECT_NEAR(accuracy, 97.671, 0.001);
		EXPECT_NEAR(fm, 93.204, 0.001);
		EXPECT_NEAR(recall, 91.3811, 0.001);
		EXPECT_NEAR(precision, 95.1025, 0.001);
		EXPECT_NEAR(pfm, 93.393, 0.001);
		EXPECT_NEAR(precall, 92.7954, 0.001);
		EXPECT_NEAR(pprecision, 93.9983, 0.001);
		EXPECT_NEAR(mcc, 0.918, 0.001);
		EXPECT_NEAR(nrm, 0.048, 0.001);
		EXPECT_NEAR(psnr, 16.329, 0.001);
	}
}
