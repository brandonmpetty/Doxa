// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef WAN_HPP
#define WAN_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "KitchenSinkCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The WAN Algorithm
	/// </summary>
	/// <remarks>"Binarization of Document Image Using Optimum Threshold Modification", 2018.</remarks>
	class Wan : public Algorithm<Wan>, public KitchenSinkCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			KitchenSinkCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters)
		{
			Pixel8 max;
			double mean, stddev;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {
				CalculateMeanStdDev(mean, stddev, window);
				CalculateMax(max, window);

				return (((double)max - mean) / 2) * (1 + k * ((stddev / 128) - 1));
			});
		}
	};
}


#endif //WAN_HPP
