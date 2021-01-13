// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef BATAINEH_HPP
#define BATAINEH_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "IntegralImageMeanVarianceCalc.hpp"

//////////////////////////////////////////////////////////////////////////////
// This algorithm is being deemed unreproducible as of 09/10/2019.          //
// See: BatainehTests for a deep analysis of this implementation.           //
//////////////////////////////////////////////////////////////////////////////

namespace Doxa
{
	/// <summary>
	/// The Bataineh Algorithm: Bilal Bataineh, Siti Norul Huda Sheikh Abdullah, Khairuddin Omar
	/// 
	/// This implementation was painstakingly put together and does not match up perfectly with the results of the paper.
	/// While the results are usable, I have been unable to work with the authors to overcome many challenges presented
	/// in the paper.  Due to the number of issues, this work is being deemed unreproducible.
	/// 
	/// This algorithm should not be cited by any reputable research paper until these items have been addressed:
	///		1. An obvious divide by zero problem in the SAdaptive equation
	///		2. Partial code snippet from the author shows part of the Window Threshold equation being mult. by 2
	///		3. No independent example of this algorithm actually working
	/// 
	/// Bilal Bataineh did provided me with a code snippet that was of some assistance.
	/// It should be noted that his implementation uses a Luma BT601 conversion: PNM::GrayscaleConversion::BT601
	/// 
	/// </summary>
	/// <remarks>"An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows", 2011.</remarks>
	class Bataineh : public Algorithm<Bataineh>, public IntegralImageMeanVarianceCalc
	{
	public:

		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);

			// Initialize Integral Images
			Bataineh::imageWidth = grayScaleImageIn.width;
			Bataineh::integralImage.resize(grayScaleImageIn.size);
			Bataineh::integralSqrImage.resize(grayScaleImageIn.size);
			BuildIntegralImages(Bataineh::integralImage, Bataineh::integralSqrImage, Algorithm::grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Get global std-dev and mean values
			double sigmaGlobal;
			double meanGlobal;
			CalculateGlobals(meanGlobal, sigmaGlobal);

			// Get Max Gray Value
			const Pixel8 maxGrayValue = GetMaxGrayValue();

			// Calculate Confusion Threshold
			const double confThreshold = ConfusionThreshold(meanGlobal, sigmaGlobal, maxGrayValue);

			// Find total Red and Black pixels and temp. store them in our output.  Red pixels are the confused pixels.
			int redCountImage;
			int blackCountImage;
			RedBlack(redCountImage, blackCountImage, binaryImageOut, confThreshold, sigmaGlobal);

			// Break the image into Primary and Secondary windows
			// Our output image is temporarily storing our Black/White/Red image
			std::vector<DetailedWindow> windows = GetWindows(binaryImageOut, blackCountImage, redCountImage, sigmaGlobal, maxGrayValue);

			// Get Sigma Max and Min as well as local window Sigma and Mean
			double sigmaMax;
			double sigmaMin;
			SigmaMinMaxAndMean(sigmaMin, sigmaMax, windows);

			// Apply threshold
			for (auto &detailedWindow : windows)
			{
				// Calculate threshold for the Window
				const double sigmaAdaptive = SigmaAdaptive(detailedWindow.stddev, sigmaMin, sigmaMax, maxGrayValue);
				const double threshold = WindowThreshold(detailedWindow.mean, meanGlobal, detailedWindow.stddev, sigmaAdaptive);

				// Convert to binary
				LocalWindow::Iterate(Algorithm::grayScaleImageIn.width, detailedWindow.window, [&](const int& positionWindow) {
					binaryImageOut.data[positionWindow] =
						Algorithm::grayScaleImageIn.data[positionWindow] <= threshold ? Palette::Black : Palette::White;
				});
			}
		}

	protected:
		enum PixelColor
		{
			BLACK = Palette::Black,
			RED = 128,
			WHITE = Palette::White
		};

		struct DetailedWindow
		{
			Region window;
			double mean;
			double stddev;
		};

		void CalculateGlobals(double& mean, double& stddev) const
		{
			const Region window(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);

			CalculateMeanStdDev(mean, stddev, window);
		}

		inline void CalculateMeanStdDev(double& mean, double& stddev, const Region& window) const
		{
			double variance;
			CalculateMeanVariance(mean, variance, Bataineh::imageWidth, Bataineh::integralImage, Bataineh::integralSqrImage, window);

			stddev = std::sqrt(variance);
		}

		/// <summary>
		/// Calculates the size of the Primary Window.  These windows are fixed to the image and do not surround the pixel.
		/// Note: While this algorithm does not have a fixed Windows Size nor K value, it does have these magic numbers.
		/// I believe these numbers assume an image of a certain size, with a certain resolution or character size.
		/// </summary>
		void inline constexpr PrimaryWindow(int& primaryWidth, int& primaryHeight, double p, double sigmaGlobal, Pixel8 maxGray, int imageWidth, int imageHeight)
		{

			if (p >= 2.5 || (sigmaGlobal < 0.1*maxGray))
			{
				primaryWidth = imageWidth / 6;
				primaryHeight = imageHeight / 4;
			}
			else if (p > 1 || (imageWidth + imageHeight < 400))
			{
				primaryWidth = imageWidth / 30;
				primaryHeight = imageHeight / 20;
			}
			else
			{
				primaryWidth = imageWidth / 40;
				primaryHeight = imageHeight / 30;
			}
		}

		double inline constexpr SigmaAdaptive(const double sigmaWindow, const double sigmaMin, const double sigmaMax, const Pixel8 maxGray)
		{
			// Note: In the original paper, this had a divide by 0 problem (SigmaMax - SigmaMax).  Bilal helped clear this confusion.
			return ((sigmaWindow - sigmaMin) / (sigmaMax - sigmaMin)) * maxGray;
		}

		double inline constexpr WindowThreshold(const double meanWindow, const double meanGlobal, const double sigmaWindow, const double sigmaAdaptive)
		{
			// Note: In the original paper, the Mw^2 * Sw was Mw^2 - Sw.  The authors later corrected it.
			// Note: The author gave me some partial code that contained this function.  SigmaAdaptive was multiplied by 2!
			// This threshold value can go negative at times, and even return NAN!  In both cases the block will be white.
			return meanWindow - ((meanWindow*meanWindow * sigmaWindow) / ((meanGlobal + sigmaWindow)*(2*sigmaAdaptive + sigmaWindow)));
		}

		double inline constexpr ConfusionThreshold(const double meanGlobal, const double sigmaGlobal, const Pixel8 maxGray)
		{
			// Note: In the original paper, the Mg^2 * Sg was Mg^2 - Sg.  The authors later corrected it.
			return meanGlobal - ((meanGlobal*meanGlobal * sigmaGlobal) / ((meanGlobal + sigmaGlobal)*(0.5*maxGray + sigmaGlobal)));
		}

		/// <summary>
		/// Returns the largest gray value in the image.
		/// </summary>
		Pixel8 GetMaxGrayValue() const
		{
			Pixel8 maxGrayValue = 0;
			for (int position = 0; position < Algorithm::grayScaleImageIn.size; ++position)
			{
				const Pixel8 tmpMax = Algorithm::grayScaleImageIn.data[position];
				if (tmpMax > maxGrayValue) maxGrayValue = tmpMax;
			}

			return maxGrayValue;
		}

		/// <summary>
		/// Gets the local std dev and mean, as well as calculates the global sigma min and max
		/// </summary>
		void SigmaMinMaxAndMean(double& sigmaMin, double& sigmaMax, std::vector<DetailedWindow>& windows) const
		{
			sigmaMax = 0;
			sigmaMin = std::numeric_limits<double>::max();

			for (auto &detailedWindow : windows)
			{
				CalculateMeanStdDev(detailedWindow.mean, detailedWindow.stddev, detailedWindow.window);

				if (detailedWindow.stddev > sigmaMax) sigmaMax = detailedWindow.stddev;
				if (detailedWindow.stddev < sigmaMin) sigmaMin = detailedWindow.stddev;
			}
		}

		/// <summary>
		/// Returns the total Red and Black count for the image and builds a Red Black White image.
		/// </summary>
		void RedBlack(int& redCountImage, int& blackCountImage, Image& redBlackImage, const double confusionThreshold, const double sigmaGlobal) const
		{
			const double halfSigmaGlobal = sigmaGlobal / 2;

			redCountImage = 0;
			blackCountImage = 0;

			for (int position = 0; position < Algorithm::grayScaleImageIn.size; ++position)
			{
				const Pixel8 val = Algorithm::grayScaleImageIn.data[position];

				if (val <= confusionThreshold - halfSigmaGlobal)
				{
					++blackCountImage;
					redBlackImage.data[position] = PixelColor::BLACK;
				}
				else if (val >= confusionThreshold + halfSigmaGlobal)
				{
					redBlackImage.data[position] = PixelColor::WHITE;
				}
				else
				{
					++redCountImage;
					redBlackImage.data[position] = PixelColor::RED;
				}
			}
		}

		/// <summary>
		/// Breaks the image into Primary and Secondary windows.
		/// This is different from most other algorithms where the window is based around the pixel.
		/// </summary>
		/// <returns>Primary and Secondary Windows.  NRVO should not make a copy of the vector.</returns>
		std::vector<DetailedWindow> GetWindows(
			const Image& image, 
			const int blackCountImage, 
			const int redCountImage,
			const double sigmaGlobal, 
			const Pixel8 maxGrayValue)
		{
			// Calculate the Primary Window size
			int windowWidth;
			int windowHeight;
			PrimaryWindow(windowWidth, windowHeight,
				(double)blackCountImage / redCountImage,
				sigmaGlobal,
				maxGrayValue,
				image.width,
				image.height
			);

			// Build list of Primary Windows
			std::vector<DetailedWindow> windows = GetPrimaryWindows(image, windowWidth, windowHeight);

			// Break some Primary Windows into smaller Secondary Windows
			UpdateWindowsWithSecondarySize(windows, image);

			return windows;
		}

		/// <summary>
		/// Break the image into a set of fixed windows.
		/// We take some liberty on the edges, so that we are not left with a window that is too small.
		/// </summary>
		std::vector<DetailedWindow> GetPrimaryWindows(const Image& image, const int windowWidth, const int windowHeight) const
		{
			std::vector<DetailedWindow> windows;
			int offsetY = 0;
			int offsetX = 0;
			
			for (int y = 0; y < image.height; y = offsetY + 1)
			{
				// Do not overshoot Y
				offsetY = std::min(image.height - 1, y + (windowHeight - 1));

				// Do not undershoot Y
				if ((image.height - 1) - offsetY < windowHeight / 2)
					offsetY = image.height - 1;

				for (int x = 0; x < image.width; x = offsetX + 1)
				{
					// Do not overshoot X
					offsetX = std::min(image.width - 1, x + (windowWidth - 1));

					// Do not undershoot X
					if ((image.width - 1) - offsetX < windowWidth / 2)
						offsetX = image.width - 1;

					windows.push_back(DetailedWindow{ Region(x, y, offsetX, offsetY) });
				}
			}

			return windows;
		}

		/// <summary>
		/// Breaks up certain Primary Windows into smaller window sizes
		/// </summary>
		void UpdateWindowsWithSecondarySize(std::vector<DetailedWindow>& windows, const Image& image) const
		{
			// Iterate each primary window.  If it needs to be broken up, remove it and add the secondary windows.
			std::vector<DetailedWindow> secondaryWindows;
			windows.erase(std::remove_if(windows.begin(), windows.end(), [&](const DetailedWindow& detailedWindow) {
				int redCountWindow = 0;
				int blackCountWindow = 0;

				// Count Red and Black pixels in the Window
				LocalWindow::Iterate(image.width, detailedWindow.window, [&](const int& positionWindow) {
					const Pixel8 val = image.data[positionWindow];

					if (val == PixelColor::BLACK) ++blackCountWindow;
					else if (val == PixelColor::RED) ++redCountWindow;
				});

				// If there are more Red pixels, create a second window by quartering the primary window
				if (redCountWindow > blackCountWindow)
				{
					const int halfX = detailedWindow.window.Width() / 2;
					const int halfY = detailedWindow.window.Height() / 2;

					const Region& win = detailedWindow.window;
					secondaryWindows.push_back(DetailedWindow{ Region(win.upperLeft.x, win.upperLeft.y, win.upperLeft.x + halfX - 1, win.upperLeft.y + halfY - 1) });
					secondaryWindows.push_back(DetailedWindow{ Region(win.upperLeft.x + halfX, win.upperLeft.y, win.bottomRight.x, win.upperLeft.y + halfY - 1) });
					secondaryWindows.push_back(DetailedWindow{ Region(win.upperLeft.x, win.upperLeft.y + halfY, win.upperLeft.x + halfX - 1, win.bottomRight.y) });
					secondaryWindows.push_back(DetailedWindow{ Region(win.upperLeft.x + halfX, win.upperLeft.y + halfY, win.bottomRight.x, win.bottomRight.y) });

					return true;
				}

				return false;
			}), windows.end());

			// Merge Secondary Windows into our main Window vector
			windows.insert(std::end(windows), std::begin(secondaryWindows), std::end(secondaryWindows));
		}


		int imageWidth = 0;
		IntegralImage integralImage, integralSqrImage;
	};
}


#endif //BATAINEH_HPP
