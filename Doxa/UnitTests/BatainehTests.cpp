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
			const Image grayScaleImage = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::BT601} });
			BatainehTestharness bataineh;
			bataineh.Initialize(grayScaleImage);

			// Get global std-dev and mean values
			double sigmaGlobal;
			double meanGlobal;
			bataineh.CalculateMeanStdDev(meanGlobal, sigmaGlobal, Region(grayScaleImage.width, grayScaleImage.height));
			if (enableAssertions) Assert::AreEqual(31.6197, sigmaGlobal, 0.001);
			if (enableAssertions) Assert::AreEqual(186.3858, meanGlobal, 0.001);
			Logger::WriteMessage(("Mg = " + std::to_string(meanGlobal) + ", Sg = " + std::to_string(sigmaGlobal)).c_str());

			// Get Max Gray Value
			const Pixel8 maxGrayValue = bataineh.GetMaxGrayValue();
			if (enableAssertions) Assert::AreEqual((Pixel8)222, maxGrayValue);
			Logger::WriteMessage(("MAXlevel = " + std::to_string(maxGrayValue)).c_str());

			// Calculate Confusion Threshold
			const double confThreshold = bataineh.ConfusionThreshold(meanGlobal, sigmaGlobal, maxGrayValue);
			if (enableAssertions) Assert::AreEqual(151.0563, confThreshold, 0.001);
			Logger::WriteMessage(("Tc = " + std::to_string(confThreshold)).c_str());

			// Find total Red and Black pixels
			Image rbwImage(grayScaleImage.width, grayScaleImage.height);
			int redCountImage;
			int blackCountImage;
			bataineh.RedBlack(redCountImage, blackCountImage, rbwImage, confThreshold, sigmaGlobal);
			if (enableAssertions) Assert::AreEqual(19513, redCountImage);
			if (enableAssertions) Assert::AreEqual(34320, blackCountImage);
			Logger::WriteMessage(("REDg = " + std::to_string(redCountImage) + ", BLACKg = " + std::to_string(blackCountImage)).c_str());

			// Create a Red Black White image for analysis
			PNM::Write(rbwImage, TestUtilities::ProjectFolder() + "2JohnC1V3-Bataineh-RBW.pgm");

			// Calculate P Value - helps determine window size
			double p = (double)blackCountImage / redCountImage;
			Logger::WriteMessage(("p = " + std::to_string(p)).c_str());

			// Calculate the Primary Window size
			int primaryWindowWidth;
			int primaryWindowHeight;
			bataineh.PrimaryWindow(primaryWindowWidth, primaryWindowHeight,
				p,
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
			if (enableAssertions) Assert::AreEqual((size_t)1121, windows.size());
			Logger::WriteMessage(("PW & SW Count = " + std::to_string(windows.size())).c_str());

			// Create a window breakdown image for analysis
			Image windowImage = GenerateWindowImage(rbwImage, windows);
			PNM::Write(windowImage, TestUtilities::ProjectFolder() + "2JohnC1V3-Bataineh-Windows.pgm");

			// Get Sigma Max and Min as well as local window Sigma and Mean
			double sigmaMax;
			double sigmaMin;
			bataineh.SigmaMinMaxAndMean(sigmaMin, sigmaMax, windows);
			if (enableAssertions) Assert::AreEqual(0.7923, sigmaMin, 0.001);
			if (enableAssertions) Assert::AreEqual(52.7487, sigmaMax, 0.001);
			Logger::WriteMessage(("Smin = " + std::to_string(sigmaMin) + ", Smax = " + std::to_string(sigmaMax)).c_str());

			// Get a target Window and analyze it
			Logger::WriteMessage("First Window Details:");

			BatainehTestharness::DetailedWindow detailedWindow = windows.front(); // First Window
			if (enableAssertions) Assert::AreEqual(185.8893, detailedWindow.mean, 0.001);
			if (enableAssertions) Assert::AreEqual(26.9717, detailedWindow.stddev, 0.001);
			Logger::WriteMessage(("Mw = " + std::to_string(detailedWindow.mean) + ", Sw = " + std::to_string(detailedWindow.stddev)).c_str());

			if (enableAssertions) Assert::AreEqual(23, detailedWindow.window.Width());
			if (enableAssertions) Assert::AreEqual(22, detailedWindow.window.Height());
			Logger::WriteMessage(("Ww = " + std::to_string(detailedWindow.window.Width()) + ", Wh = " + std::to_string(detailedWindow.window.Height())).c_str());

			const double sigmaAdaptive = bataineh.SigmaAdaptive(detailedWindow.stddev, sigmaMin, sigmaMax, maxGrayValue);
			if (enableAssertions) Assert::AreEqual(111.8597, sigmaAdaptive, 0.001);
			Logger::WriteMessage(("Sadaptive = " + std::to_string(sigmaAdaptive)).c_str());

			const Pixel8 threshold = bataineh.WindowThreshold(detailedWindow.mean, meanGlobal, detailedWindow.stddev, sigmaAdaptive);
			if (enableAssertions) Assert::AreEqual((Pixel8)168, threshold);
			Logger::WriteMessage(("Tw = " + std::to_string(threshold)).c_str());
		}

	protected:
		/// <summary>
		/// A method that draws the bottom, and right side of every window onto the image.
		/// </summary>
		/// <returns>An Image with window outlines</returns>
		Image GenerateWindowImage(const Image& image, const std::vector<BatainehTestharness::DetailedWindow>& windows)
		{
			Image windowImage(image); // Make a deep copy

			for (auto it = windows.begin(); it != windows.end(); ++it)
			{
				// Draw bottom horizontal bar
				for (int x = it->window.upperLeft.x; x < it->window.bottomRight.x; ++x)
				{
					windowImage.Pixel(x, it->window.bottomRight.y) = 75;
				}

				// Draw right vertical bar
				for (int y = it->window.upperLeft.y; y < it->window.bottomRight.y; ++y)
				{
					windowImage.Pixel(it->window.bottomRight.x, y) = 75;
				}
			}

			return windowImage;
		}
	};
}
