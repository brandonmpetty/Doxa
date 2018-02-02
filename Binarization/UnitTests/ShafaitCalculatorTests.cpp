#include "CppUnitTest.h"
#include "../ShafaitCalculator.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(ShafaitCalculatorTests)
	{
	public:

		// Exposes protected methods for Unit Testing
		template<typename Calculator>
		class ShafaitTestharness : public Calculator
		{
		public:
			ShafaitTestharness(Image& image) : Calculator(image) {}
			using Calculator::integral_image;
			using Calculator::integral_sqimg;
		};


		TEST_METHOD(ShafaitCalculatorCompareImagesTest)
		{
			// Setup
			Pixel32 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image image(3, 3, bits);

			ShafaitTestharness<Shafait> shafait(image);

			Shafait::IntegralImage integralImage = {
				18,  66, 144,
				56, 124, 235,
				60, 140, 265
			};

			Shafait::IntegralImage integralSquareImage = {
				 324, 2628,  8712,
				1768, 4472, 11645,
				1784, 4632, 12001
			};

			// Test
			shafait.Initialize();

			// Assert
			Assert::IsTrue(shafait.integral_image == integralImage);
			Assert::IsTrue(shafait.integral_sqimg == integralSquareImage);
		}

		TEST_METHOD(ShafaitCalculatorCalculate)
		{
			// Setup
			Pixel32 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image image(3, 3, bits);

			Shafait shafait(image);
			shafait.Initialize();

			double mean = 0.0;
			double stddev = 0.0;
			double variance = 0.0;
			double diff = 0.0;
			double sqdiff = 0.0;

			Region window(0, 0, 2, 2);
			shafait.CalculateMeanStdDev(mean, stddev, window);
			Assert::AreEqual(mean, 29.44, 0.01);
			Assert::AreEqual(stddev, 22.90, 0.01);

			shafait.CalculateMeanVariance(mean, variance, window);
			Assert::AreEqual(mean, 29.44, 0.01);
			Assert::AreEqual(variance, 524.77, 0.01);

			shafait.CalculateDiffs(diff, sqdiff, window);
			Assert::AreEqual(diff, 265.00, 0.01);
			Assert::AreEqual(sqdiff, 12001.00, 0.01);
		}

		TEST_METHOD(ShafaitCalculatorOriginalVsLowMemTest)
		{
			// Setup
			Pixel32 bits[] = {
				Palette::Gray(10, 20, 30), Palette::Gray(40, 50, 60), Palette::Gray(70, 80, 90),
				Palette::Gray(30, 40, 50), Palette::Gray(50, 05, 05), Palette::Gray(50, 30, 10),
				Palette::Gray(03, 05, 07), Palette::Gray(11, 13, 17), Palette::Gray(00, 25, 12)
			};
			Image image(3, 3, bits);

			ShafaitTestharness<Shafait> shafait(image);
			ShafaitTestharness<Shafait_LowMem> shafaitLowMem(image);

			// Test
			shafait.Initialize();
			shafaitLowMem.Initialize();

			// Assert
			Assert::IsTrue(shafait.integral_image == shafaitLowMem.integral_image);
			Assert::IsTrue(shafait.integral_sqimg == shafaitLowMem.integral_sqimg);
		}
	};
}
