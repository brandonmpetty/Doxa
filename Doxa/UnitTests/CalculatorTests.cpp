#include "CppUnitTest.h"
#include "../KitchenSinkCalculator.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(CalculatorTests)
	{
	public:

		// Exposes protected members for Unit Testing
		class CalculatorTestharness : public KitchenSinkCalculator
		{
		public:
			CalculatorTestharness() : KitchenSinkCalculator() {}
			using KitchenSinkCalculator::integral_image;
			using KitchenSinkCalculator::integral_sqimg;
			using KitchenSinkCalculator::CalculateDiffs;
			using KitchenSinkCalculator::CalculateDiff;
		};


		TEST_METHOD(CalculateIntegralImagesTest)
		{
			// Setup
			Pixel8 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image image(3, 3, bits);

			IntegralImage integralImage = {
				18,  66, 144,
				56, 124, 235,
				60, 140, 265
			};

			IntegralImage integralSquareImage = {
				324, 2628,  8712,
				1768, 4472, 11645,
				1784, 4632, 12001
			};

			// Test Integral and Squared Integral Image Creation
			CalculatorTestharness calculator;
			calculator.Initialize(image);

			// Assert Single and Squared Integral Image Creation
			Assert::IsTrue(calculator.integral_image == integralImage);
			Assert::IsTrue(calculator.integral_sqimg == integralSquareImage);
		}

		TEST_METHOD(CalculateMeanVarianceTest)
		{
			// Setup
			Pixel8 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image image(3, 3, bits);

			MeanCalculator meanCalculator;
			meanCalculator.Initialize(image);

			MeanVarianceCalculator meanVarianceCalculator;
			meanVarianceCalculator.Initialize(image);

			double mean, mean2 = 0.0;
			double stddev = 0.0;
			double variance = 0.0;

			Region window(0, 0, 2, 2);

			// Calculate Mean
			meanCalculator.CalculateMean(mean, window);
			meanVarianceCalculator.CalculateMean(mean2, window);
			Assert::AreEqual(mean, mean2);

			// Calculate Mean and Variance
			meanVarianceCalculator.CalculateMeanVariance(mean, variance, window);
			Assert::AreEqual(mean, 29.44, 0.01);
			Assert::AreEqual(variance, 524.77, 0.01);

			// Calculate Mean and Std Dev
			meanVarianceCalculator.CalculateMeanStdDev(mean, stddev, window);
			Assert::AreEqual(mean, 29.44, 0.01);
			Assert::AreEqual(stddev, 22.90, 0.01);
		}

		TEST_METHOD(CalculateMinMaxTest)
		{
			MinMaxCalculator calculator;

			const Pixel8 data[] = {
				1,  2,  3,  4,  5,  6,
				7,  8,  9, 10, 11, 12,
				13, 14, 15, 16, 17, 18,
				19, 20, 21, 22, 23, 24,
				25, 26, 27, 28, 29, 30,
				31, 32, 33, 34, 35, 36
			};

			const Pixel8 minArray[] = {
				1,  1,  2,  3,  4,  5,
				1,  1,  2,  3,  4,  5,
				7,  7,  8,  9, 10, 11,
				13, 13, 14, 15, 16, 17,
				19, 19, 20, 21, 22, 23,
				25, 25, 26, 27, 28, 29
			};

			const Pixel8 maxArray[] = {
				8,  9, 10, 11, 12, 12,
				14, 15, 16, 17, 18, 18,
				20, 21, 22, 23, 24, 24,
				26, 27, 28, 29, 30, 30,
				32, 33, 34, 35, 36, 36,
				32, 33, 34, 35, 36, 36
			};

			Image image(6, 6, data);
			calculator.Initialize(image);

			LocalWindow::Iterate(image, 3, [&](const Region& window, const int& position) {
				Pixel8 min, max, max2;

				// Method Under Test 
				calculator.CalculateMinMax(min, max, window);
				calculator.CalculateMax(max2, window);

				// Assertions
				Assert::AreEqual(max, max2);
				Assert::AreEqual(minArray[position], min, std::wstring(L"Min: Failed at position: " + std::to_wstring(position)).c_str());
				Assert::AreEqual(maxArray[position], max, std::wstring(L"Max: Failed at position: " + std::to_wstring(position)).c_str());
			});
		}
	};
}
