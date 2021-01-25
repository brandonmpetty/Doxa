// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef SU_HPP
#define SU_HPP

#include "Types.hpp"
#include "Otsu.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "Morphology.hpp"
#include "ContrastImage.hpp"

////////////////////////////////////////////////////////////////////////
// This code is highly experimental and has not been unit tested yet! //
////////////////////////////////////////////////////////////////////////

namespace Doxa
{
	/// <summary>
	/// The Su Algorithm: Bolan Su, Shijian Lu, and Chew Lim Tan
	/// This is a 3 step workflow consisting of:
	///		Contrast Image generation
	///		High contrast pixel detection using Otsu binarization
	///		A novel local thresholding algorithm
	/// 
	/// Currently Su requires two parameters that can be autodetected, as detailed at end of the paper.
	/// For now, they must be entered manually.
	/// </summary>
	/// <remarks>"Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.</remarks>
	class Su : public Algorithm<Su>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// 0 will trigger the auto detection of these parameters as detailed in the paper
			int windowSize = parameters.Get("window", 0); // Based on Stroke Size
			int minN = parameters.Get("minN", windowSize); // Roughly basd on size of window

			// Step 1 - Contrast Image Construction
			Image contrastImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			ContrastImage::GenerateContrastImage(contrastImage, Algorithm::grayScaleImageIn);

			// Optional Parameter Auto Detection
			if (windowSize == 0)
			{
				AutoDetectParameters(windowSize, minN, contrastImage);
			}

			// Step 2 - High Contrast Pixel Detection
			Otsu::UpdateToBinary(contrastImage, parameters);

			// Step 3 - Historical Document Thresholding
			Threshold(binaryImageOut, contrastImage, Algorithm::grayScaleImageIn, windowSize, minN);
		}

	protected:
		void AutoDetectParameters(int& windowSize, int& minN, const Image& contrastImage)
		{
			// TODO: Implement parameter auto-detection based on stroke width in the Contrast Image
			windowSize = 9;
			minN = windowSize;
		}

		/// <summary>
		/// Calculates Ne, meanE, and stdE in one iteration.
		/// This is a very optimized set of calculations compared to the math found in the paper.
		/// </summary>
		void SuCalculations(int& Ne, double& meanE, double& stdE, const Image& contrastImage, const Image& grayScaleImage, const Region& window) const
		{
			int sumGrayScale = 0;
			Ne = 0;

			LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& position)
			{
				if (Palette::White == contrastImage.data[position])
				{
					sumGrayScale += grayScaleImage.data[position];
					++Ne;
				}
			});

			meanE = (double)sumGrayScale / Ne;

			const double stdENom = (double)sumGrayScale - (Ne * meanE);
			stdE = std::sqrt((stdENom * stdENom) / 2);
		};

		void Threshold(Image& binaryImageOut, const Image& contrastImageIn, const Image& grayScaleImageIn, int windowSize, int minN) const
		{
			int Ne;
			double meanE, stdE;

			LocalWindow::Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position)
			{
				SuCalculations(Ne, meanE, stdE, contrastImageIn, grayScaleImageIn, window);

				binaryImageOut.data[position] =
					(Ne >= minN && grayScaleImageIn.data[position] <= meanE + (stdE / 2)) ?
					Palette::Black : Palette::White;
			});
		}
	};
}


#endif //SU_HPP
