// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef NIBLACK_HPP
#define NIBLACK_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanMeanVarianceCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The Niblack Algorithm: Wayne Niblack
	/// </summary>
	/// <remarks>"An Introduction to Digital Image Processing", 1986.</remarks>
	template<typename Calculator>
	class NiblackBase : public Algorithm<NiblackBase<Calculator>>, public Calculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int&) {
				const double stddev = std::sqrt(variance);

				return (mean + (k * stddev));
			});
		}
	};

	/// <summary>
	/// The Niblack binarization algorithm using the Chan algorithm for quick statistical calculations.
	/// </summary>
	typedef NiblackBase<ChanMeanVarianceCalc> Niblack;
}


#endif //NIBLACK_HPP
