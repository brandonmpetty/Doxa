// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef SU_HPP
#define SU_HPP

#include <cmath>
#include "Types.hpp"
#include "Otsu.hpp"
#include "Palette.hpp"
#include "Morphology.hpp"
#include "ContrastImage.hpp"
#include "ChanCalc.hpp"

namespace Doxa
{
	/// <summary>
	/// The Su Algorithm: Bolan Su, Shijian Lu, and Chew Lim Tan
	/// This is a 3 step workflow consisting of:
	///		Contrast Image generation
	///		High contrast pixel detection using Otsu binarization
	///		A novel local thresholding algorithm
	/// 
	/// Parameters window and minN are auto-detected from stroke width when not provided.
	/// </summary>
	/// <remarks>"Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.</remarks>
	class Su : public Algorithm<Su>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// 0 will trigger the auto detection of these parameters as detailed in the paper
			int windowSize = parameters.Get("window", 0); // Based on Stroke Size
			int minN = parameters.Get("minN", windowSize); // Roughly based on size of window

			// Step 1 & 2 - Generate Hight Contrast Image Construction
			Image contrastImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			ContrastImage::GenerateHighContrastImage(contrastImage, Algorithm::grayScaleImageIn);

			// Optional Parameter Auto Detection
			if (windowSize == 0)
			{
				AutoDetectParameters(windowSize, minN, contrastImage);
			}

			// Step 3 - Historical Document Thresholding
			Threshold(binaryImageOut, contrastImage, Algorithm::grayScaleImageIn, windowSize, minN);
		}

	protected:
		// <summary>
		// Calculates Stroke Width and Min-N from the estimated stroke width.
		// 
		// In Su's 2010 paper, they provide no specifics on window size... just make it bigger than the stroke width.
		// In their 2013 paper, "Robust Document Image Binarization Technique for Degraded Document Images",
		// they empirically show that (Window Size = 2 x Stroke Width) to be the best.
		// </summary>
		void AutoDetectParameters(int& windowSize, int& minN, const Image& contrastImage)
		{
			const int strokeWidth = ContrastImage::EstimateStrokeWidth(contrastImage);
			windowSize = strokeWidth * 2;
			minN = windowSize;
		}

		void Threshold(Image& binaryImageOut, const Image& contrastImageIn, const Image& grayScaleImageIn, int windowSize, int minN) const
		{
			const Pixel8* gray = grayScaleImageIn.data;

			// LocalWindow treats a window of size N as +/- N/2 inclusive, which for an even N
			// (Su's auto-detected size is 2 x stroke width) is really a window of N + 1.
			// ChanMaskedCalc takes the exact size, so round even sizes up to stay identical.
			const int chanWindowSize = windowSize | 1;

			// The contrast image is the mask: White (high contrast) selects pixels.
			// Ne, ΣI, and ΣI² over those pixels give the mean and standard deviation.
			ChanMaskedCalc<true>::Iterate(grayScaleImageIn, contrastImageIn, chanWindowSize,
				[&](const int64_t Ne, const int64_t sum, const int64_t squareSum, const int position)
				{
					double meanE = 0.0;
					double stdE = 0.0;

					if (Ne != 0)
					{
						meanE = static_cast<double>(sum) / Ne;

						const double variance = static_cast<double>(squareSum) / Ne - meanE * meanE;

						// Clamp tiny negatives from floating-point round-off
						stdE = variance > 0.0 ? std::sqrt(variance) : 0.0;
					}

					binaryImageOut.data[position] =
						(Ne >= minN && gray[position] <= meanE + (stdE / 2)) ?
							Palette::Black : Palette::White;
				});
		}
	};
}


#endif //SU_HPP
