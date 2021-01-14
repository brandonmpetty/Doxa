// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef NICK_HPP
#define NICK_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanMeanVarianceCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The NICK Algorithm: Khurram Khurshid, Imran Siddiqi, Claudie Faure, Nicole Vincent
	/// </summary>
	/// <remarks>"Comparison of Niblack inspired Binarization methods for ancient documents", 2009.</remarks>
	class Nick : public Algorithm<Nick>, public ChanMeanVarianceCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", -0.2);

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int&) {

				return mean + (k * std::sqrt(variance + (mean * mean)));
			});
		}
	};
}


#endif //NICK_HPP
