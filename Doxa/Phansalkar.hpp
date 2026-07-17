// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef PHANSALKAR_HPP
#define PHANSALKAR_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The Phansalkar Algorithm: Neerad Phansalkar, Sumit More, Ashish Sabale, Madhuri Joshi 
	///
	/// This papers calls for the logical OR of the thresholding algorithm ran on:
	///    RGB Grayscale - BT601
	///    L* a* b* Grayscale - sqr_root(L*^2 + a*^2 + b*^2)
	/// 
	/// This algorithm is unique in its use of LAB to take into account Color!
	/// NOTE: Run this twice with different grayscale algorithms and then OR the images together.
	///
	///	Optimization Approach (from paper):
	///   "Such a global threshold should not reject a single pixel that corresponds to a nucleus..."
	///   "Such a threshold is obtained using Otsu’s method."
	/// This is not true of document glyphs.  Because of this, the Otsu speed optimization is not implemented.
	/// </summary>
	/// <remarks>"Adaptive Local Thresholding for Detection of Nuclei in Diversely Stained Cytology Images", 2011.</remarks>
	class Phansalkar : public Algorithm<Phansalkar>, public ChanMeanVarianceCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);
			const double p = parameters.Get("p", 3.0);
			const double q = parameters.Get("q", 10.0) / 255; // Normalized to 0 to 255, not 0 to 1.

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int&) {
				const double stddev = std::sqrt(variance);

				return mean * (1 + p * exp(-q * (mean)) + k * ((stddev / 128) - 1));
			});
		}
	};
}


#endif //PHANSALKAR_HPP
