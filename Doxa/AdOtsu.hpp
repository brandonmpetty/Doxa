// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef ADOTSU_HPP
#define ADOTSU_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "Otsu.hpp"
#include "MultiScale.hpp"
#include <cmath>


namespace Doxa
{
	/// <summary>
	/// The AdOtsu Algorithm, v2010: Reza Farrahi Moghaddam, Mohamed Cheriet
	/// 
	/// This is the core, non-multi-scale grid based, AdOtsu algorithm referenced in (5) of their paper.
	/// It should be noted that the paper uses a special color to grayscale algorithm in order to create a
	/// "non-sensitive gray-value image."  This would be "GrayscaleConversion::MinAvg".
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

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 1.0);
			const double R = parameters.Get("R", 0.1);

			Otsu otsu;
			const Pixel8 globalThreshold = otsu.Threshold(Algorithm::grayScaleImageIn);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {

				const double localThreshold = k * LocalThreshold(otsu, Algorithm::grayScaleImageIn, window);

				const double u = (std::abs((double)globalThreshold - localThreshold) / R);
				
				// Apply the Unit Step Function
				return (u < 255) ? localThreshold : -1;
			});	
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
	};

	/// <summary>
	/// A multi-scale local adaptive Otsu binarization algorithm
	/// 
	/// TODO: Change this so AdOtsuMSG when Grid support is available.
	/// This should greatly improve performance.
	/// </summary>
	typedef MultiScale<AdOtsu> AdOtsuMS;
}


#endif //ADOTSU_HPP
