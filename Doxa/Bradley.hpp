// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef BRADLEY_HPP
#define BRADLEY_HPP

#include "Algorithm.hpp"
#include "ChanMeanCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The Bradley Algorithm: Derek Bradley, Gerhard Roth
	///
	/// Bradley's contribution is "Wellner's threshold formula, but with a
	/// properly-centered s x s window mean instead of a 1-D direction-biased
	/// moving average."  A pixel is set to black when it is more than 't'
	/// percent darker than the mean of its surrounding window:
	///
	///   pixel <= mean * (100 - t) / 100  -> Black, otherwise White
	///
	/// The paper computes the windowed mean via integral image; we use the
	/// equivalent Chan sliding-sum.
	///
	/// Defaults match the paper: window is 1/8 the image width, t = 15.
	/// </summary>
	/// <remarks>"Adaptive Thresholding Using the Integral Image", 2007.</remarks>
	class Bradley : public Algorithm<Bradley>, public ChanMeanCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", Algorithm::grayScaleImageIn.width / 8);
			const int t = parameters.Get("t", 15);

			const double kFactor = (100 - t) / 100.0;

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize,
				[&](const double& mean, const int&) {
					return mean * kFactor;
				});
		}
	};
}


#endif //BRADLEY_HPP
