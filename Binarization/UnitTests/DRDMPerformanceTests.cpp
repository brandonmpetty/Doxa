#include "CppUnitTest.h"
#include "../DRDMPerformance.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(DRDMPerformanceTests)
	{

	public:
		TEST_METHOD(DRDMPerformanceTest)
		{
			// (3, 4) = Black is changed to White
			// One 8x8 Block with a 5x5 Window
			Pixel32 dataGT[] = {
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

			Pixel32 dataExp[] = {
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

			double drdm = DRDMPerformance::CalculateDRDM(groundTruthImage, expImage);

			Assert::AreEqual((72357 + 72357 + 32359)/(double)1000000, drdm);
		}
	};
}
