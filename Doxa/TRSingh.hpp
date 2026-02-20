// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef TRSINGH_HPP
#define TRSINGH_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanMeanCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The T.R. Singh Algorithm: T. Romen Singh, Sudipta Roy, O. Imocha Singh, Tejmani Sinam, Kh. Manglem Singh
	/// </summary>
	/// <remarks>"A New local Adaptive Thresholding Technique in Binarization", 2011.</remarks>
	class TRSingh : public Algorithm<TRSingh>, public ChanMeanCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const int& position)
			{
				// Unlike Sauvola, the Singh algorithm necessitates a value between 0 and 1, not 0 255.
				// This adapts his formula to 8bit grayscale to avoid conversion operations.
				constexpr double R = 255.0;

				// TR Singh's algorithm does not expressly mention the need for an absolute value.
				// However, I believe it is implied because we are talking about deviation
				double meandev = std::abs((double)Algorithm::grayScaleImageIn.data[position] - mean);

				// This clamping operation prevents a divide by zero situation
				// Alternative: Add std::numeric_limits<double>::epsilon() to the denominator
				meandev = std::min(meandev, R - 1.0);

				return mean * (1 + k * ((meandev / (R - meandev)) - 1));
			});
		}
	};
}


#endif //TRSINGH_HPP
