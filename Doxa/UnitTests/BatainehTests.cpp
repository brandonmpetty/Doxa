#include "TestUtilities.hpp"
#include "../Bataineh.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(BatainehTests)
	{
		// Exposes protected members for Unit Testing
		class BatainehTestharness : public Bataineh
		{
		public:
			BatainehTestharness() : Bataineh() {}
			using Bataineh::GetMaxGrayValue;
			using Bataineh::ConfusionThreshold;
			using Bataineh::RedBlack;
			using Bataineh::PrimaryWindow;
			using Bataineh::GetWindows;
			using Bataineh::SigmaMinMaxAndMean;
			using Bataineh::SigmaAdaptive;
			using Bataineh::WindowThreshold;

			using Bataineh::DetailedWindow;
		};

	public:
		TEST_METHOD(BatainehToBinaryTest)
		{
			// Note: This algorithm, nor the numbers asserted, may be correct.
			// This test is mainly used, for now, to analyze the characteristics of an image
			// If you just want image details - turn off the assertions.
			bool enableAssertions = true;
			Logger::WriteMessage("Bataineh Algorithm Analysis");

			// Setup
			const std::string filePath = TestUtilities::ProjectFolder() + "2JohnC1V3.ppm";
			const Image grayScaleImage = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Mean} });
			BatainehTestharness bataineh;
			bataineh.Initialize(grayScaleImage);

			// Get global std-dev and mean values
			double sigmaGlobal;
			double meanGlobal;
			bataineh.CalculateMeanStdDev(meanGlobal, sigmaGlobal, Region(grayScaleImage.width, grayScaleImage.height));
			if (enableAssertions) Assert::AreEqual(32.3004, sigmaGlobal, 0.001);
			if (enableAssertions) Assert::AreEqual(181.6902, meanGlobal, 0.001);
			Logger::WriteMessage(("Mg = " + std::to_string(meanGlobal) + ", Sg = " + std::to_string(sigmaGlobal)).c_str());

			// Get Max Gray Value
			const Pixel8 maxGrayValue = bataineh.GetMaxGrayValue();
			if (enableAssertions) Assert::AreEqual((Pixel8)219, maxGrayValue);
			Logger::WriteMessage(("MAXlevel = " + std::to_string(maxGrayValue)).c_str());

			// Calculate Confusion Threshold
			const double confThreshold = bataineh.ConfusionThreshold(meanGlobal, sigmaGlobal, maxGrayValue);
			if (enableAssertions) Assert::AreEqual(146.5504, confThreshold, 0.001);
			Logger::WriteMessage(("Tc = " + std::to_string(confThreshold)).c_str());

			// Find total Red and Black pixels
			Image rbwImage(grayScaleImage.width, grayScaleImage.height);
			int redCountImage;
			int blackCountImage;
			bataineh.RedBlack(redCountImage, blackCountImage, rbwImage, confThreshold, sigmaGlobal);
			if (enableAssertions) Assert::AreEqual(20221, redCountImage);
			if (enableAssertions) Assert::AreEqual(35056, blackCountImage);
			Logger::WriteMessage(("REDg = " + std::to_string(redCountImage) + ", BLACKg = " + std::to_string(blackCountImage)).c_str());

			// Create a Red Black White image for analysis
			PNM::Write(rbwImage, TestUtilities::ProjectFolder() + "2JohnC1V3-Bataineh-RBW.pgm");

			// Calculate the Primary Window size
			int primaryWindowWidth;
			int primaryWindowHeight;
			bataineh.PrimaryWindow(primaryWindowWidth, primaryWindowHeight,
				(double)blackCountImage / redCountImage,
				sigmaGlobal,
				maxGrayValue,
				rbwImage.width,
				rbwImage.height
			);
			if (enableAssertions) Assert::AreEqual(23, primaryWindowWidth);
			if (enableAssertions) Assert::AreEqual(22, primaryWindowHeight);
			Logger::WriteMessage(("PWw = " + std::to_string(primaryWindowWidth) + ", PWh = " + std::to_string(primaryWindowHeight)).c_str());

			// Break the image into Primary and Secondary windows
			std::vector<BatainehTestharness::DetailedWindow> windows = bataineh.GetWindows(rbwImage, blackCountImage, redCountImage, sigmaGlobal, maxGrayValue);
			if (enableAssertions) Assert::AreEqual((size_t)1136, windows.size());
			Logger::WriteMessage(("PW & SW Count = " + std::to_string(windows.size())).c_str());

			// Get Sigma Max and Min as well as local window Sigma and Mean
			double sigmaMax;
			double sigmaMin;
			bataineh.SigmaMinMaxAndMean(sigmaMin, sigmaMax, windows);
			if (enableAssertions) Assert::AreEqual(0.8952, sigmaMin, 0.001);
			if (enableAssertions) Assert::AreEqual(53.1309, sigmaMax, 0.001);
			Logger::WriteMessage(("Smin = " + std::to_string(sigmaMin) + ", Smax = " + std::to_string(sigmaMax)).c_str());

			// Get a target Window and analyze it
			Logger::WriteMessage("First Window Details:");

			BatainehTestharness::DetailedWindow detailedWindow = windows.front(); // First Window
			if (enableAssertions) Assert::AreEqual(182.4861, detailedWindow.mean, 0.001);
			if (enableAssertions) Assert::AreEqual(27.81389, detailedWindow.stddev, 0.001);
			Logger::WriteMessage(("Mw = " + std::to_string(detailedWindow.mean) + ", Sw = " + std::to_string(detailedWindow.stddev)).c_str());

			if (enableAssertions) Assert::AreEqual(23, detailedWindow.window.Width());
			if (enableAssertions) Assert::AreEqual(22, detailedWindow.window.Height());
			Logger::WriteMessage(("Ww = " + std::to_string(detailedWindow.window.Width()) + ", Wh = " + std::to_string(detailedWindow.window.Height())).c_str());

			const double sigmaAdaptive = bataineh.SigmaAdaptive(detailedWindow.stddev, sigmaMin, sigmaMax, maxGrayValue);
			if (enableAssertions) Assert::AreEqual(112.8572, sigmaAdaptive, 0.001);
			Logger::WriteMessage(("Sadaptive = " + std::to_string(sigmaAdaptive)).c_str());

			const Pixel8 threshold = bataineh.WindowThreshold(detailedWindow.mean, meanGlobal, detailedWindow.stddev, sigmaAdaptive);
			if (enableAssertions) Assert::AreEqual((Pixel8)151, threshold);
			Logger::WriteMessage(("Tw = " + std::to_string(threshold)).c_str());
		}
	};
}
