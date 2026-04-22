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

		/// <summary>
		/// Calculates Ne, meanE, and stdE in one iteration.
		/// This is a very optimized set of calculations compared to the math found in the paper.
		/// </summary>
		void SuCalculations(int& Ne, double& meanE, double& stdE,
							const Image& contrastImage, const Image& grayScaleImage,
							const Region& window) const
		{
			uint64_t sumI  = 0;  // Σ I(x,y)
			uint64_t sumI2 = 0;  // Σ I(x,y)²
			Ne = 0;

			// Single pass: accumulate first and second raw moments over high-contrast pixels.
			// Uses identity:  Var(X) = E[X²] - (E[X])²
			LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& position)
			{
				if (Palette::White == contrastImage.data[position])
				{
					const uint32_t I = grayScaleImage.data[position]; // promote once
					sumI  += I;
					sumI2 += I * I;
					++Ne;
				}
			});

			if (Ne == 0) { meanE = 0.0; stdE = 0.0; return; }

			meanE = static_cast<double>(sumI) / Ne;

			// variance = ΣI²/Ne − meanE²
			const double variance = static_cast<double>(sumI2) / Ne - meanE * meanE;

			// Clamp tiny negatives from floating-point round-off (happens when true variance ≈ 0)
			stdE = variance > 0.0 ? std::sqrt(variance) : 0.0;
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
