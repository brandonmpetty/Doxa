#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
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
		using Bataineh::CalculateMeanStdDev;

		using Bataineh::DetailedWindow;

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

	TEST(BatainehTests, BatainehToBinaryTest)
	{
		// Note: This algorithm, nor the numbers asserted, may be correct.
		// This test is mainly used, for now, to analyze the characteristics of an image
		// If you just want image details - turn off the assertions.
		bool enableAssertions = true;
		SUCCEED() << "Bataineh Algorithm Analysis";

		// Setup
		const std::string filePath = TestUtilities::ProjectFolder() + "2JohnC1V3.ppm";
		const Image grayScaleImage = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::BT601} });
		BatainehTestharness bataineh;
		bataineh.Initialize(grayScaleImage);

		// Get global std-dev and mean values
		double sigmaGlobal;
		double meanGlobal;
		bataineh.CalculateMeanStdDev(meanGlobal, sigmaGlobal, Region(grayScaleImage.width, grayScaleImage.height));
		if (enableAssertions) EXPECT_NEAR(31.6197, sigmaGlobal, 0.001);
		if (enableAssertions) EXPECT_NEAR(186.3858, meanGlobal, 0.001);
		SUCCEED() << "Mg = " << meanGlobal << ", Sg = " << sigmaGlobal;

		// Get Max Gray Value
		const Pixel8 maxGrayValue = bataineh.GetMaxGrayValue();
		if (enableAssertions) EXPECT_EQ((Pixel8)222, maxGrayValue);
		SUCCEED() << "MAXlevel = " << maxGrayValue;

		// Calculate Confusion Threshold
		const double confThreshold = bataineh.ConfusionThreshold(meanGlobal, sigmaGlobal, maxGrayValue);
		if (enableAssertions) EXPECT_NEAR(151.0563, confThreshold, 0.001);
		SUCCEED() << "Tc = " << confThreshold;

		// Find total Red and Black pixels
		Image rbwImage(grayScaleImage.width, grayScaleImage.height);
		int redCountImage;
		int blackCountImage;
		bataineh.RedBlack(redCountImage, blackCountImage, rbwImage, confThreshold, sigmaGlobal);
		if (enableAssertions) EXPECT_EQ(19513, redCountImage);
		if (enableAssertions) EXPECT_EQ(34320, blackCountImage);
		SUCCEED() << "REDg = " << redCountImage << ", BLACKg = " << blackCountImage;

		// Create a Red Black White image for analysis
		PNM::Write(rbwImage, TestUtilities::ProjectFolder() + "2JohnC1V3-Bataineh-RBW.pgm");

		// Calculate P Value - helps determine window size
		double p = (double)blackCountImage / redCountImage;
		SUCCEED() << "p = " << p;

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
		if (enableAssertions) EXPECT_EQ(23, primaryWindowWidth);
		if (enableAssertions) EXPECT_EQ(22, primaryWindowHeight);
		SUCCEED() << "PWw = " << primaryWindowWidth << ", PWh = " << primaryWindowHeight;

		// Break the image into Primary and Secondary windows
		std::vector<BatainehTestharness::DetailedWindow> windows = bataineh.GetWindows(rbwImage, blackCountImage, redCountImage, sigmaGlobal, maxGrayValue);
		if (enableAssertions) EXPECT_EQ((size_t)1121, windows.size());
		SUCCEED() << "PW & SW Count = " << windows.size();

		// Create a window breakdown image for analysis
		Image windowImage = bataineh.GenerateWindowImage(rbwImage, windows);
		PNM::Write(windowImage, TestUtilities::ProjectFolder() + "2JohnC1V3-Bataineh-Windows.pgm");

		// Get Sigma Max and Min as well as local window Sigma and Mean
		double sigmaMax;
		double sigmaMin;
		bataineh.SigmaMinMaxAndMean(sigmaMin, sigmaMax, windows);
		// Note: Values calculated with Population Variance
		if (enableAssertions) EXPECT_NEAR(0.7890, sigmaMin, 0.001);
		if (enableAssertions) EXPECT_NEAR(52.6966, sigmaMax, 0.001);
		SUCCEED() << "Smin = " << sigmaMin << ", Smax = " << sigmaMax;

		// Get a target Window and analyze it
		SUCCEED() << "First Window Details:";

		BatainehTestharness::DetailedWindow detailedWindow = windows.front(); // First Window
		if (enableAssertions) EXPECT_NEAR(185.8893, detailedWindow.mean, 0.001);
		if (enableAssertions) EXPECT_NEAR(26.9451, detailedWindow.stddev, 0.001);
		SUCCEED() << "Mw = " << detailedWindow.mean << ", Sw = " << detailedWindow.stddev;

		if (enableAssertions) EXPECT_EQ(23, detailedWindow.window.Width());
		if (enableAssertions) EXPECT_EQ(22, detailedWindow.window.Height());
		SUCCEED() << "Ww = " << detailedWindow.window.Width() << ", Wh = " << detailedWindow.window.Height();

		const double sigmaAdaptive = bataineh.SigmaAdaptive(detailedWindow.stddev, sigmaMin, sigmaMax, maxGrayValue);
		if (enableAssertions) EXPECT_NEAR(111.865, sigmaAdaptive, 0.001);
		SUCCEED() << "Sadaptive = " << sigmaAdaptive;

		const Pixel8 threshold = bataineh.WindowThreshold(detailedWindow.mean, meanGlobal, detailedWindow.stddev, sigmaAdaptive);
		if (enableAssertions) EXPECT_EQ((Pixel8)168, threshold);
		SUCCEED() << "Tw = " << threshold;
	}
}
