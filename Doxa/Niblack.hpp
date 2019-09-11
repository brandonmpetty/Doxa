// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef NIBLACK_HPP
#define NIBLACK_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MeanVarianceCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Niblack Algorithm: Wayne Niblack
	/// </summary>
	/// <remarks>"An Introduction to Digital Image Processing", 1986.</remarks>
	class Niblack : public Algorithm<Niblack>, public MeanVarianceCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			MeanVarianceCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			double mean, stddev;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {
				CalculateMeanStdDev(mean, stddev, window);

				return (mean + (k * stddev));
			});
		}
	};
}


#endif //NIBLACK_HPP
