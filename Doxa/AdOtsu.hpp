// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#ifndef ADOTSU_HPP
#define ADOTSU_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "Otsu.hpp"
#include "MultiScale.hpp"
#include "GridCalc.hpp"
#include <algorithm>
#include <cmath>

/////////////////////////////////////////////////////////////////////////
// Experemintal - This algorithm is under review for paper correctness.
// NOTE: Default parameters are likely correct, but k <> 1 could be off.
/////////////////////////////////////////////////////////////////////////


namespace Doxa
{
	/// <summary>
	/// The AdOtsu Algorithm, v2010: Reza Farrahi Moghaddam, Mohamed Cheriet
	///
	/// This is the core, non-multi-scale, AdOtsu algorithm referenced in (5) of their paper.
	/// It should be noted that the paper uses a special color to grayscale algorithm in order to create a
	/// "non-sensitive gray-value image."  This would be "GrayscaleAlgorithms::MINAVG".
	///
	/// The second iteration of this algorithm was introduced a year later in their work:
	/// "AdOtsu: An adaptive and parameterless generalization of Otsu’s method for document image binarization"
	///
	/// This later work builds on top of their earlier work.  Our implementation features their earlier work
	/// which will act as a base for future improvements.
	/// </summary>
	/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010.</remarks>
	class AdOtsu : public Algorithm<AdOtsu>
	{
	public:
		static const int HISTOGRAM_SIZE = 256;

		void Initialize(const Image& grayScaleImageIn) override
		{
			Algorithm::Initialize(grayScaleImageIn);

			// Calculate once when ran through Muli-Scale iterations
			Otsu otsu;
			globalThreshold = otsu.Threshold(Algorithm::grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 1.0);
			const double R = parameters.Get("R", 0.1);

			// Grid distances beyond the window size would leave gaps between sampling windows
			const int distance = (std::min)(parameters.Get("distance", (int)(windowSize / 2)), windowSize);

			// Pre-compute the unit step result for every possible raw local Otsu threshold,
			// avoiding per-pixel double arithmetic in the inner loops below
			int lut[HISTOGRAM_SIZE];
			for (int t = 0; t < HISTOGRAM_SIZE; ++t)
			{
				const double localThreshold = k * t;
				const double u = std::abs((double)globalThreshold - localThreshold) / R;
				lut[t] = (u < 255) ? (int)localThreshold : -1;
			}

			Otsu otsu;

			// Bypass the "Grid" optimization.  There is nothing to interpolate.
			if (distance < 2)
			{
				LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {

					return lut[LocalThreshold(otsu, Algorithm::grayScaleImageIn, window)];
				});
			}
			else // Use the "Grid" optimization
			{
				GridCalc gridCalc;

				// Calculate all thresholds through interpolation
				gridCalc.Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, distance, [&](const Region& window, const int&) {

					return LocalThreshold(otsu, Algorithm::grayScaleImageIn, window);
				});

				// Turn the image into a binary image using the Unit Step Function
				for (int idx = 0; idx < binaryImageOut.size; ++idx)
				{
					binaryImageOut.data[idx] =
						Algorithm::grayScaleImageIn.data[idx] <= lut[binaryImageOut.data[idx]] ?
							Palette::Black : Palette::White;
				}
			} // Use grid interpolation?
		}

		Pixel8 LocalThreshold(const Otsu& otsu, const Image& grayScaleImage, const Region& window)
		{
			// Create Local Histogram
			unsigned int histogram[HISTOGRAM_SIZE]; // Placed on stack for performance.  This shouldn't be too large.
			memset(histogram, 0, (HISTOGRAM_SIZE) * sizeof(unsigned int));

			// Initialize Histogram from Local Window
			LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& windowPosition)
			{
				++histogram[grayScaleImage.data[windowPosition]];
			});

			return otsu.Algorithm(histogram, window.Area());
		}

	protected:
		Pixel8 globalThreshold = 0;
	};

	/// <summary>
	/// A multi-scale local adaptive Otsu varient
	/// </summary>
	typedef MultiScale<AdOtsu> AdOtsuMS;
}


#endif //ADOTSU_HPP
