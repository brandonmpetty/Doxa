#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	// Exposes protected members for Unit Testing
	class DRDMTestHarness : public Doxa::DRDM
	{
	public:
		using DRDM::SumDRDkForMismatchedPixels;
		using DRDM::NUBN;

		// NUBN may call any of these three routines
		using DRDM::NUBN_STD;
		using DRDM::NUBN_STD_8x8;

		#if defined(DOXA_SIMD)
			using DRDM::NUBN_SIMD_8x8;
		#endif
	};

	TEST(DRDMTests, DRDMSauvolaTest)
	{
		// Setup
		std::string projFolder = TestUtilities::ProjectFolder();

		const std::string filePathGT = projFolder + "2JohnC1V3-GroundTruth.pbm";
		Image gtImage = PNM::Read(filePathGT);

		const std::string filePathSauvola = projFolder + "2JohnC1V3-Sauvola.pbm";
		Image binImage = PNM::Read(filePathSauvola);

		// Run DRDM
		const double drdm = DRDMTestHarness::CalculateDRDM(gtImage, binImage);
		const uint64_t sumDRDk = DRDMTestHarness::SumDRDkForMismatchedPixels(gtImage, binImage);
		const int nubn = DRDMTestHarness::NUBN_STD(gtImage, 8);

		// DRDM - Value optained from the DIBCO perf tool
		EXPECT_NEAR(1.9519, drdm, 0.0001);
		EXPECT_EQ(4122339441, sumDRDk);
		EXPECT_EQ(2112, nubn);
	}

	TEST(DRDMTests, DRDMTest)
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

		EXPECT_EQ((double)(72357 + 72357 + 32359) / 1000000, drdm);
	}

	TEST(DRDMTests, NUBNUniformityCountTest)
	{
		// This is a 24x24 image creating a 3x3 set of windows that are 8x8
		Pixel8 data[] = {
			// ===== Window Row 1 (rows 0-7 of array) =====
			// Window 1-1: All White | Window 1-2: All Black | Window 1-3: White with black center

			// Window row 0: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 1: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 2: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 3: Window 1-1 | Window 1-2 | Window 1-3 (black center)
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 4: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 5: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 6: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 7: Window 1-1 | Window 1-2 | Window 1-3
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// ===== Window Row 2 (rows 8-15 of array) =====
			// Window 2-1: Checkerboard | Window 2-2: All White | Window 2-3: All Black

			// Window row 0: Window 2-1 | Window 2-2 | Window 2-3
			Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 1: Window 2-1 | Window 2-2 | Window 2-3
			Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 2: Window 2-1 | Window 2-2 | Window 2-3
			Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 3: Window 2-1 | Window 2-2 | Window 2-3
			Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 4: Window 2-1 | Window 2-2 | Window 2-3
			Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 5: Window 2-1 | Window 2-2 | Window 2-3
			Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 6: Window 2-1 | Window 2-2 | Window 2-3
			Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// Window row 7: Window 2-1 | Window 2-2 | Window 2-3
			Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White, Palette::Black, Palette::White,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,

			// ===== Window Row 3 (rows 16-23 of array) =====
			// Window 3-1: Black with white center | Window 3-2: White with black border | Window 3-3: Black with white border

			// Window row 0: Window 3-1 | Window 3-2 (top border) | Window 3-3 (top border)
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,

			// Window row 1: Window 3-1 | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 2: Window 3-1 | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 3: Window 3-1 (white center) | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 4: Window 3-1 | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 5: Window 3-1 | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 6: Window 3-1 | Window 3-2 | Window 3-3
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::Black,
			Palette::White, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::White,

			// Window row 7: Window 3-1 | Window 3-2 (bottom border) | Window 3-3 (bottom border)
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black, Palette::Black,
			Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White, Palette::White,
		};

		// This image contains 4 fully black or white windows
		// and 5 mixed windows
		Image binaryImage(24, 24, data);

		const unsigned int countStd = DRDMTestHarness::NUBN_STD(binaryImage, 8);
		const unsigned int countStd8x8 = DRDMTestHarness::NUBN_STD_8x8(binaryImage);
		
		EXPECT_EQ(countStd, 5);
		EXPECT_EQ(countStd8x8, 5);


		#if defined(DOXA_SIMD)
			const unsigned int countSimd8x8 = DRDMTestHarness::NUBN_SIMD_8x8(binaryImage);
			EXPECT_EQ(countSimd8x8, 5);
		#endif
	}

	TEST(DRDMTests, NUBNVariousWindowSizesTest)
	{
		// This a 15x15 image with window sizes of 8x8, 7x7, and 25x25
		Image binaryImage(24, 24);
		binaryImage.Fill(Palette::White);
		binaryImage.Pixel(7, 3) = Palette::Black;
		binaryImage.Pixel(15, 3) = Palette::Black;
		binaryImage.Pixel(23, 3) = Palette::Black;

		const unsigned int count1 = DRDMTestHarness::NUBN(binaryImage, 8);

		// Try an smaller window size of 7
		// We do not process partial windows, so 7x7 should only see 2
		const unsigned int count2 = DRDMTestHarness::NUBN(binaryImage, 7);

		// Lets make our window size larger than the image
		// Since we don't do partial windows, this is an interesting edge case
		const unsigned int count3 = DRDMTestHarness::NUBN(binaryImage, 25);

		EXPECT_EQ(count1, 3); // Window 8x8
		EXPECT_EQ(count2, 2); // Window 7x7
		EXPECT_EQ(count3, 0); // Window 25x25
	}

    TEST(DRDMTests, NUBNImplementationConsistencyTest)
    {
		std::string projFolder = TestUtilities::ProjectFolder();
        const std::string filePathGT = projFolder + "2JohnC1V3-GroundTruth.pbm";
		Image binaryImage = PNM::Read(filePathGT);

		const unsigned int countSTD = DRDMTestHarness::NUBN_STD(binaryImage, 8);
		const unsigned int countSTD8x8 = DRDMTestHarness::NUBN_STD_8x8(binaryImage);
		
		EXPECT_EQ(countSTD, countSTD8x8);

		
		#if defined(DOXA_SIMD)
			const unsigned int countSimd8x8 = DRDMTestHarness::NUBN_SIMD_8x8(binaryImage);
			EXPECT_EQ(countSTD8x8, countSimd8x8);
		#endif
    }
}
