#include "CppUnitTest.h"
#include "../Grayscale.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(GrayscaleTests)
	{
	public:

		TEST_METHOD(GrayscaleAlgorithmsTest)
		{
			// Mean, Value, and Luster contain obvious formulas.
			Assert::AreEqual(100, Grayscale::Mean(100, 30, 170));

			Assert::AreEqual(200, Grayscale::Value(50, 100, 200));
			Assert::AreEqual(200, Grayscale::Value(50, 200, 100));
			Assert::AreEqual(200, Grayscale::Value(200, 100, 50));

			Assert::AreEqual(125, Grayscale::Luster(50, 100, 200));

			// Assert that all weights sum to exactly 1
			Assert::AreEqual(1.0, Grayscale::BT601(1.0, 1.0, 1.0), 0.001);
			Assert::AreEqual(1.0, Grayscale::BT709(1.0, 1.0, 1.0), 0.001);
			Assert::AreEqual(1.0, Grayscale::BT2100(1.0, 1.0, 1.0), 0.001);
		}

		TEST_METHOD(GrayscalesRgbToLightnessTest)
		{
			const Pixel8 y = Grayscale::sRgbToLightness(47, 155, 220);

			// Note: .6030 is using the d50 weights, not the 709 weights which our algorithm uses.
			// The weights are only slightly different, so I am keeping the d50 value for posterity.
			// See: https://observablehq.com/@mbostock/lab-and-rgb
			Assert::AreEqual(0.6030 * 255, y, 0.01 * 255);
		}
	};
}
