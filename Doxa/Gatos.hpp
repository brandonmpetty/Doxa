// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef GATOS_HPP
#define GATOS_HPP

#include "Types.hpp"
#include "Sauvola.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "Image.hpp"
#include "WienerFilter.hpp"

////////////////////////////////////////////////////////////////////////
// This code is highly experimental and has not been unit tested yet! //
////////////////////////////////////////////////////////////////////////

namespace Doxa
{
	/// <summary>
	/// The Gatos binarization workflow: B. Gatos, I. Pratikakis, S.J. Perantonis
	/// This is a 5 step workflow consisting of:
	///		Wiener Filter
	///		Sauvola binarization algorithm
	///		A background estimation based thresholding algorithm
	///		Upsampling and other post-processing meassures
	/// 
	/// The optional Upsampling on the fourth step is not currently performed, nor the Post-processing for the fifth step.
	/// </summary>
	/// <remarks>"Adaptive degraded document image binarization", 2005.</remarks>
	class Gatos : public Algorithm<Gatos>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int glyphSize = parameters.Get("glyph", 60);

			// Step 1 - Pre-processing: Run greyscale through Wiener Filter
			Image filteredImage(Algorithm::grayScaleImageIn);
			WienerFilter::Filter(filteredImage, Algorithm::grayScaleImageIn, 3);

			// Step 2 - Rough estimation of foreground regions: Apply Sauvola binarization
			Sauvola algorithm;  // TODO - Allow this algorithm to be swapped with any in the library
			algorithm.Initialize(filteredImage);
			algorithm.ToBinary(binaryImageOut, parameters);

			// Step 3 - Background surface estimation
			Image backgroundImage(filteredImage);
			ExtractBackground(backgroundImage, filteredImage, binaryImageOut, (glyphSize * 2) + 1);

			// Step 4 - Final thresholding
			double d, b;
			GatosCalculations(d, b, backgroundImage, filteredImage, binaryImageOut);

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
		/// <summary>
		/// Calculates Average Forground / Background Distance, and Averate Background Text Value.
		/// </summary>
		void GatosCalculations(double& averageFgBgDistance, double& averageBgTextValue, const Image& backgroundImage, const Image& filteredImage, const Image& binaryImage) const
		{
			int backgroundCounter = 0;
			int numeratorAverageFgBgDistance = 0; // Calculate Average Forground / Background Distance
			int numeratorAverageBgTextValue = 0; // Calculate Average Background Text Value

			for (int index = 0; index < binaryImage.size; ++index)
			{
				numeratorAverageFgBgDistance += backgroundImage.data[index] - filteredImage.data[index];

				if (Palette::White == binaryImage.data[index])
				{
					numeratorAverageBgTextValue += backgroundImage.data[index];
					++backgroundCounter;
				}
			}

			averageFgBgDistance = (double)numeratorAverageFgBgDistance / (backgroundImage.size - backgroundCounter);
			averageBgTextValue = (double)numeratorAverageBgTextValue / backgroundCounter;
		}

		double Threshold(const int backgroundValue, const double d, const double b, const double q = 0.6, const double p1 = 0.5, const double p2 = 0.8) const
		{
			const double expVal = exp(((-4 * backgroundValue) / (b * (1 - p1))) + ((2 * (1 + p1)) / (1 - p1)));
			return q * d * (((1 - p2) / (1 + expVal)) + p2);
		}

		// Note: backgroundImage must be a copy of grayScaleImage.  This avoids us having to set pixels for the backround entirely
		void ExtractBackground(Image& backgroundImage, const Image& filteredImage, const Image& binaryImage, const int windowSize = 51) const
		{
			LocalWindow::Iterate(filteredImage, windowSize, [&](const Region& window, const int& position)
			{	
				if (binaryImage.data[position] == Palette::Black)
				{
					unsigned int numerator = 0;
					unsigned int denominator = 0;

					// Build a window around our black pixel and traverse it
					LocalWindow::Iterate(filteredImage.width, window, [&](const int& windowPosition)
					{
						// This is usually mathematically described as:
						//     Numerator += B(x, y) * (1 − S(x, y))
						//     Denominator += (1 − S(x, y))
						// This assumes that your binary image's black value is 1, and white 0.
						// Blindly following this mathematical formula also impacts performance!
						if (binaryImage.data[windowPosition] == Palette::White)
						{
							numerator += filteredImage.data[windowPosition];
							++denominator;
						}
					});

					backgroundImage.data[position] = numerator / denominator;
				}
			});
		}
	};
}


#endif //GATOS_HPP
