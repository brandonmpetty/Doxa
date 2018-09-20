// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef GATOSWORKFLOW_HPP
#define GATOSWORKFLOW_HPP

#include "Types.hpp"
#include "Algorithms.hpp"
#include "Preprocessor.hpp"
#include "Palette.hpp"
#include "Region.hpp"

//////////////////////////////////////////////////////////////////
// This code is highly experimental and has not bee tested yet! //
//////////////////////////////////////////////////////////////////

namespace Binarization
{
	/// <summary>
	/// The Gatos binarization workflow.
	/// This is a 5 step workflow consisting of a Wiener Filter, the Sauvola algorithm, and a background estimation based thresholding algorithm.
	/// The optional Upsampling on the fourth step is not currently performed, nor the Post-processing for the fifth step.
	/// This is only a partial implementation and has not been optimized.
	/// </summary>
	/// <remarks>"Adaptive degraded document image binarization", 2005.</remarks>
	class GatosWorkflow
	{
	public:

		template<typename Calculator>
		void Run(Image& binaryImageOut, const Image& grayScaleImageIn, const int glyphSize = 60, const int windowSize = 75, const double k = 0.2) const
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
				denominator += binaryImage.data[index];
			}

			return numerator / (double)denominator;
		}

		double AverageBgTextValue(const Image& backgroundImage, const Image& binaryImage) const
		{
			int numerator = 0;
			int denominator = 0;

			for (int index = 0; index < binaryImage.size; ++index)
			{
				numerator += backgroundImage.data[index] * (1 - binaryImage.data[index]);
				denominator += (1 - binaryImage.data[index]);
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

			const int pixelCount = windowSize * windowSize;

			// Obtain the average variance for all pixels
			double mean, variance;
			uint64_t sumVariance = 0;

			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position) {

				calculator.CalculateMeanVariance(mean, variance, window);

				sumVariance += variance;
			});

			const double avgVariance = sumVariance / pixelCount;

			// Apply Wiener Filter
			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position) {

				calculator.CalculateMeanVariance(mean, variance, window);

				outputImage.data[position] = mean + ((variance - avgVariance) * (inputImage.data[position] - mean)) / variance;
			});
		}

		// backgroundImage must be a copy of grayScaleImage.  This avoids us having to set pixels for the backround entirely
		void ExtractBackground(Image& backgroundImage, const Image& filteredImage, const Image& binaryImage, const int windowSize = 51) const
		{
			const int HALF_WINDOW = windowSize / 2;

			// Find every black pixel
			for (int x = 0; x < binaryImage.width; ++x)
			{
				for (int y = 0; y < binaryImage.height; ++y)
				{
					// This is very costly, but the alternative is to call / and % on every black pixel to convert index to coords.
					// TODO: See which is more performant.  Copy all of gSI to bgI first to avoid setting pixels on white. 
					if (binaryImage.Pixel(x, y) == Palette::Black)
					{
						const Region::Point upperLeftPoint(x - HALF_WINDOW, y - HALF_WINDOW);

						unsigned int numerator = 0;
						unsigned int denominator = 0;

						// Build a window around that black pixel and traverse it
						for (int ix = 0; ix < windowSize; ++ix)
						{
							for (int iy = 0; iy < windowSize; ++iy)
							{
								int blackMinusSauvola = (Palette::Black - binaryImage.Pixel(ix, iy));

								numerator += filteredImage.Pixel(ix, iy) * blackMinusSauvola;
								denominator += blackMinusSauvola;
							}
						}

						backgroundImage.Pixel(x, y) = numerator / denominator;
					}
				}
			}
		}
	};
}


#endif //GATOSWORKFLOW_HPP
