// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WAN_HPP
#define WAN_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanMeanVarianceCalc.hpp"
#include "Morphology.hpp"


namespace Doxa
{
	/// <summary>
	/// The WAN Algorithm: Wan Azani Mustafa, Mohamed Mydin M. Abdul Kader
	/// </summary>
	/// <remarks>"Binarization of Document Image Using Optimum Threshold Modification", 2018.</remarks>
	class Wan : public Algorithm<Wan>, public ChanMeanVarianceCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			// Use Dilate to generate a Max Image for the target Window
			Image maxImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			Morphology::Dilate(maxImage, Algorithm::grayScaleImageIn, windowSize);

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int& position) {
				const double stddev = std::sqrt(variance);

				return (((double)maxImage.data[position] + mean) / 2) * (1 + k * ((stddev / 128) - 1));
			});
		}
	};
}


#endif //WAN_HPP
