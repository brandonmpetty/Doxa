// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef GATOSWORKFLOW_HPP
#define GATOSWORKFLOW_HPP

#include "Types.hpp"
#include "Algorithms.hpp"
#include "Preprocessor.hpp"
#include "Palette.hpp"
#include "Region.hpp"

////////////////////////////////////////////////////////////////////////
// This code is highly experimental and has not been unit tested yet! //
////////////////////////////////////////////////////////////////////////

namespace Binarization
{
	/// <summary>
	/// The Gatos binarization workflow.
	/// This is a 5 step workflow consisting of a Wiener Filter, the Sauvola algorithm, and a background estimation based thresholding algorithm.
	/// The optional Upsampling on the fourth step is not currently performed, nor the Post-processing for the fifth step.
	/// </summary>
	/// <remarks>"Adaptive degraded document image binarization", 2005.</remarks>
	class GatosWorkflow
	{
	public:

		template<typename Calculator>
		void ToBinary(Image& binaryImageOut, const Image& grayScaleImageIn, const int glyphSize = 60, const int windowSize = 75, const double k = 0.2) const
		{
			Calculator calculator;

			// Step 1 - Pre-processing: Run greyscale through Wiener Filter
			Image filteredImage(grayScaleImageIn);
			WienerFilter<Calculator>(filteredImage, grayScaleImageIn, 3);

			// Step 2 - Rough estimation of foreground regions: Apply Sauvola binarization
			// TODO - Allow this algorithm to be swapped with any in the library
			calculator.Initialize(filteredImage);
			Sauvola::ToBinary(binaryImageOut, filteredImage, calculator, windowSize, k);

			// Step 3 - Background surface estimation
			Image backgroundImage(filteredImage);
			ExtractBackground(backgroundImage, filteredImage, binaryImageOut, glyphSize * 2);

			// Step 4 - Final thresholding
			const double d = AverageFgBgDistance(backgroundImage, filteredImage, binaryImageOut);
			const double b = AverageBgTextValue(backgroundImage, binaryImageOut);

			for (int index = 0; index < binaryImageOut.size; ++index)
			{
				const double threshold = Threshold(binaryImageOut.data[index], d, b);

				Pixel32 bg = backgroundImage.data[index];
				Pixel32 fi = filteredImage.data[index];

				binaryImageOut.data[index] = backgroundImage.data[index] - filteredImage.data[index] > threshold ?
					Palette::Black : Palette::White;
			}

			// Step 4.5 - Upsampling
			// TODO - Implement

			// Step 5 - Post-processing
			// TODO - Implement
		}

	protected:

		double AverageFgBgDistance(const Image& backgroundImage, const Image& filteredImage, const Image& binaryImage) const
		{
			int numerator = 0;
			int denominator = 0;

			for (int index = 0; index < binaryImage.size; ++index)
			{
				numerator += backgroundImage.data[index] - filteredImage.data[index];
				if (Palette::Black == binaryImage.data[index])
				{
					++denominator;
				}
			}

			return numerator / (double)denominator;
		}

		double AverageBgTextValue(const Image& backgroundImage, const Image& binaryImage) const
		{
			int numerator = 0;
			int denominator = 0;

			for (int index = 0; index < binaryImage.size; ++index)
			{
				if (binaryImage.data[index] == Palette::White)
				{
					numerator += backgroundImage.data[index];
					++denominator;
				}
			}

			return numerator / (double)denominator;
		}

		double Threshold(const int backgroundValue, const double d, const double b, const double q = 0.6, const double p1 = 0.5, const double p2 = 0.8) const
		{
			const double expVal = exp(((-4 * backgroundValue) / (b * (1 - p1))) + ((2 * (1 + p1)) / (1 - p1)));
			return q * d * (((1 - p2) / (1 + expVal)) + p2);
		}

		template<typename Calculator>
		void WienerFilter(Image& outputImage, const Image& inputImage, const int windowSize = 3) const
		{
			Calculator calculator;
			calculator.Initialize(inputImage);

			// Obtain the average variance for all pixels
			double mean, variance;
			uint64_t sumVariance = 0;

			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position) {

				calculator.CalculateMeanVariance(mean, variance, window);

				sumVariance += variance;
			});

			const double avgVariance = sumVariance / (double)inputImage.size;

			// Apply Wiener Filter
			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position) {

				calculator.CalculateMeanVariance(mean, variance, window);

				// The avgVariance is simulating noise-variance.  It should always be greater than variance.
				outputImage.data[position] = variance < avgVariance ? 
					mean : // Variance can be 0, so avoid the divide by 0 issue by using mean value.
					mean + ((variance - avgVariance) * (inputImage.data[position] - mean)) / variance;
			});
		}

		// Note: backgroundImage must be a copy of grayScaleImage.  This avoids us having to set pixels for the backround entirely
		void ExtractBackground(Image& backgroundImage, const Image& filteredImage, const Image& binaryImage, const int windowSize = 51) const
		{
			LocalWindow::Iterate(filteredImage, windowSize, [&](const Region& window, const int& position){
				
				if (binaryImage.data[position] == Palette::Black)
				{
					unsigned int numerator = 0;
					unsigned int denominator = 0;

					// Build a window around our black pixel and traverse it
					for (int ix = window.upperLeft.x; ix < window.bottomRight.x; ++ix)
					{
						for (int iy = window.upperLeft.y; iy < window.bottomRight.y; ++iy)
						{
							// This is usually mathematically described as:
							// Numerator += B(x, y) * (1 − S(x, y))							// Denominator += (1 − S(x, y))							// This assumes that your binary image's black value is 1, and white 0.							// Blindly following this mathematical formula also impacts performance!
							if (binaryImage.Pixel(ix, iy) == Palette::White)
							{
								numerator += filteredImage.Pixel(ix, iy);
								++denominator;
							}
						}
					}

					backgroundImage.data[position] = numerator / denominator;
				}
			});
		}
	};
}


#endif //GATOSWORKFLOW_HPP
