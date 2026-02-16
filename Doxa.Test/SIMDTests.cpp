#include "pch.h"
#include "TestUtilities.hpp"
#include "ImageFixture.hpp"
#include <iostream>


namespace Doxa::UnitTests
{

    // Implements pure virtual functions
    class GlobalThresholdTestHarness: public GlobalThreshold<GlobalThresholdTestHarness>
    {
        Pixel8 Threshold(const Image& grayScaleImage, const Parameters& parameters = Parameters())
        {
            return 128;
        }
    };

    // Exposes protected members for Unit Testing
    class DRDMTestHarness : public Doxa::DRDM
    {
    public:
        using DRDM::NUBN_STD;

        #if defined(DOXA_SIMD)
            using DRDM::NUBN_SIMD_8x8;
        #endif
    };


    class SIMDTests : public ImageFixture {};

    TEST_F(SIMDTests, SIMDDetection)
    {
        std::cout << "\n=== SIMD Compile-Time Detection ===" << std::endl;

        #if defined(DOXA_SIMD)
            #if defined(DOXA_SIMD_SSE2)
                std::cout << "Detected: SSE2 (16 pixels/op)" << std::endl;
                EXPECT_EQ(Doxa::SIMD::SIMD_WIDTH, 16);

            #elif defined(DOXA_SIMD_NEON)
                std::cout << "Detected: NEON (16 pixels/op)" << std::endl;
                EXPECT_EQ(Doxa::SIMD::SIMD_WIDTH, 16);

            #elif defined(DOXA_SIMD_WASM)
                std::cout << "Detected: WASM SIMD128 (16 pixels/op)" << std::endl;
                EXPECT_EQ(Doxa::SIMD::SIMD_WIDTH, 16);

            #endif
        #else

            std::cout << "No SIMD detected - scalar only" << std::endl;
        #endif
    }

#if defined(DOXA_SIMD)

    TEST_F(SIMDTests, SIMDGlobalThresholdToBinaryTest)
    {
        const Pixel8 threshold = 128;
        Image binarySTD(image.width, image.height);
        Image binarySIMD(image.width, image.height);

        GlobalThresholdTestHarness::ToBinary_STD(image.data, binarySTD.data, image.size, threshold);
        GlobalThresholdTestHarness::ToBinary_SIMD(image.data, binarySIMD.data, image.size, threshold);

        TestUtilities::AssertImages(binarySTD, binarySIMD);
    }

    TEST_F(SIMDTests, SIMDClassifiedPerformanceCompareImagesTest)
    {
		std::string projFolder = TestUtilities::ProjectFolder();

		const std::string filePathBinary = projFolder + "2JohnC1V3-Sauvola.pbm";
        const std::string filePathGT = projFolder + "2JohnC1V3-GroundTruth.pbm";

        ClassifiedPerformance::Classifications classificationsSTD;
        ClassifiedPerformance::Classifications classificationsSIMD;

		Image binaryImage = PNM::Read(filePathBinary);
		Image groundTruthImage = PNM::Read(filePathGT);

		ClassifiedPerformance::CompareImages_STD(classificationsSTD, groundTruthImage.data, binaryImage.data, groundTruthImage.size);
		ClassifiedPerformance::CompareImages_SIMD(classificationsSIMD, groundTruthImage.data, binaryImage.data, groundTruthImage.size);

        EXPECT_EQ(classificationsSTD.truePositive, classificationsSIMD.truePositive);
        EXPECT_EQ(classificationsSTD.trueNegative, classificationsSIMD.trueNegative);
        EXPECT_EQ(classificationsSTD.falsePositive, classificationsSIMD.falsePositive);
        EXPECT_EQ(classificationsSTD.falseNegative, classificationsSIMD.falseNegative);
    }

    TEST_F(SIMDTests, SIMDDrdmNubnTest)
    {
        const std::string filePathBinary = projFolder + "2JohnC1V3-GroundTruth.pbm";
        Image binaryImage = PNM::Read(filePathBinary);

        const unsigned int nubnSTD = DRDMTestHarness::NUBN_STD(binaryImage, 8);
        const unsigned int nubnSIMD = DRDMTestHarness::NUBN_SIMD_8x8(binaryImage);

        EXPECT_EQ(nubnSTD, nubnSIMD);
    }

#endif // DOXA_SIMD
}
