#include "CppUnitTest.h"
#include "../Algorithms.hpp"
#include "../ShafaitCalculator.hpp"
#include "../PPM.hpp"
#include "../Preprocessor.hpp"
#include "../Performance.hpp"
#include "../MetricUtils.hpp"

// Used for expanding macro based directives
#define STR(x) #x
#define EXPAND(x) STR(x)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(Kumite)
	{
		void Display(const std::string desc, const MetricUtils::Score& score, const double time)
		{
			Logger::WriteMessage(desc.c_str());

			Logger::WriteMessage("\tAccuracy:");
			Logger::WriteMessage(std::string("\t\tAccuracy: " + std::to_string(score.accuracy)).c_str());
			Logger::WriteMessage(std::string("\t\tF-Measure: " + std::to_string(score.fmeasure)).c_str());
			Logger::WriteMessage(std::string("\t\tPSNR: " + std::to_string(score.psnr)).c_str());
			Logger::WriteMessage(std::string("\t\tTotal: " + std::to_string(score.total)).c_str());

			Logger::WriteMessage("\tBest Arguments:");
			Logger::WriteMessage(std::string("\t\tWindow Size: " + std::to_string(score.windowSize)).c_str());
			Logger::WriteMessage(std::string("\t\tK Value: " + std::to_string(score.k)).c_str());

			Logger::WriteMessage(std::string("\tSpeed (Seconds): " + std::to_string(time)).c_str());
		}

		// Initialized Objects
		static Image grayScaleImage;
		static Image groundTruthImage;
		static std::string projFolder;

	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			// Obtain the project folder
			// Note: Tests are to be ran in VS.  If this is not the case, change how this is being set.
			//       This was done to avoid baking in the images into the .exe, or copying them on build.
			projFolder = EXPAND(UNITTESTPRJ);
			projFolder.erase(0, 1); // Erase first quote
			projFolder.erase(projFolder.size() - 2); // Erase first quote and period, which is used to excape the trailing slash

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.pam";
			PPM::Read(filePath, grayScaleImage);

			// Convert to Gray Scale
			// Note: Not a legitimate PAM image, so do not save this image.
			Preprocessor::ToGreyScale(grayScaleImage);

			// Load Ground Truth
			const std::string gtPath = projFolder + "2JohnC1V3-GroundTruth.pam";
			PPM::Read(gtPath, groundTruthImage);
		}

		// The Dim Mak is a very expensive test and should only be performed purposefully
		BEGIN_TEST_METHOD_ATTRIBUTE(DimMak)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(DimMak)
		{
			const int windowSizeStart = 11;
			const int windowSizeStop = 125;
			const double kStart = 0.10;
			const double kStop = 0.90;

			{ // Sauvola Shafait

				// Calculate Best Accuracy Stats
				MetricUtils::Score score = MetricUtils::Accuracy(groundTruthImage, grayScaleImage, windowSizeStart, windowSizeStop, kStart, kStop,
					[](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
					Algorithms::Sauvola<Shafait>(expirementImage, inputImage, ws, k);
				});

				// Time the algorithm
				Image imageSauvolaShafait(grayScaleImage.width, grayScaleImage.height);

				double time = MetricUtils::Time([&]() {
					Algorithms::Sauvola<Shafait>(imageSauvolaShafait, grayScaleImage, score.windowSize, score.k);
				});

				// Display results
				Display("Sauvola Algorithm with Shafait optimization", score, time);
			}

			{ // Sauvola Shafait LowMem

				// Calculate Best Accuracy Stats
				MetricUtils::Score score = MetricUtils::Accuracy(groundTruthImage, grayScaleImage, windowSizeStart, windowSizeStop, kStart, kStop,
					[](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
					Algorithms::Sauvola<Shafait_LowMem>(expirementImage, inputImage, ws, k);
				});

				// Time again with a different Calculator
				Image imageSauvolaShafaitLowMem(grayScaleImage.width, grayScaleImage.height);

				double time = MetricUtils::Time([&]() {
					Algorithms::Sauvola<Shafait_LowMem>(imageSauvolaShafaitLowMem, grayScaleImage, score.windowSize, score.k);
				});

				// Display results
				Display("Sauvola Algorithm with Shafait LowMem optimization", score, time);

				//PPM::Write(imageSauvolaShafaitLowMem, projFolder + "2JohnC1V3-Sauvola-Best.pam");
			}

			{ // Niblack LowMem Shafait

				const double kStartNiblack = -0.90;
				const double kStopNiblack = 0.50;

				// Calculate Best Accuracy Stats
				MetricUtils::Score score = MetricUtils::Accuracy(groundTruthImage, grayScaleImage, windowSizeStart, windowSizeStop, kStartNiblack, kStopNiblack,
					[](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
					Algorithms::Niblack<Shafait>(expirementImage, inputImage, ws, k);
				});

				// Time the algorithm
				Image imageNiblackShafait(grayScaleImage.width, grayScaleImage.height);

				double time = MetricUtils::Time([&]() {
					Algorithms::Niblack<Shafait>(imageNiblackShafait, grayScaleImage, score.windowSize, score.k);
				});

				// Display results
				Display("Niblack Algorithm with Shafait optimization", score, time);

				//PPM::Write(imageNiblackShafaitLowMem, projFolder + "2JohnC1V3-Niblack-Best.pam");
			}

			{ // Wolf LowMem Shafait

				// Calculate Best Accuracy Stats
				MetricUtils::Score score = MetricUtils::Accuracy(groundTruthImage, grayScaleImage, windowSizeStart, windowSizeStop, kStart, kStop,
					[](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
					Algorithms::Wolf<Shafait>(expirementImage, inputImage, ws, k);
				});

				// Time the algorithm
				Image imageWolfShafait(grayScaleImage.width, grayScaleImage.height);

				double time = MetricUtils::Time([&]() {
					Algorithms::Wolf<Shafait>(imageWolfShafait, grayScaleImage, score.windowSize, score.k);
				});

				// Display results
				Display("Wolf Algorithm with Shafait optimization", score, time);

				//PPM::Write(imageWolfShafaitLowMem, projFolder + "2JohnC1V3-Wolf-Best.pam");
			}

			{ // NICK LowMem Shafait
				const double kStartNick = -0.20;
				const double kStopNick = -0.10;

				// Calculate Best Accuracy Stats
				MetricUtils::Score score = MetricUtils::Accuracy(groundTruthImage, grayScaleImage, windowSizeStart, windowSizeStop, kStartNick, kStopNick,
					[](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
					Algorithms::Nick<Shafait>(expirementImage, inputImage, ws, k);
				});
				Image imageNICKShafait(grayScaleImage.width, grayScaleImage.height);

				// Time the algorithm
				double time = MetricUtils::Time([&]() {
					Algorithms::Nick<Shafait>(imageNICKShafait, grayScaleImage, score.windowSize, score.k);
				});

				// Display results
				Display("NICK Algorithm with Shafait optimization", score, time);

				//PPM::Write(imageNICKShafaitLowMem, projFolder + "2JohnC1V3-NICK-Best.pam");
			}

		} // End Dim Mak

	};

	// Static objects
	Image UnitTests::Kumite::grayScaleImage;
	Image UnitTests::Kumite::groundTruthImage;
	std::string UnitTests::Kumite::projFolder;
}
