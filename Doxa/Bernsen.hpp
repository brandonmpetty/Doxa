// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef BERNSEN_HPP
#define BERNSEN_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MinMaxCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Bernsen Algorithm
	/// </summary>
	/// <remarks>"Dynamic thresholding of gray-level images", 1986.</remarks>
	class Bernsen : public Algorithm<Bernsen>, public MinMaxCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			MinMaxCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters)
		{
			Pixel8 min, max;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const int GT = parameters.Get("threshold", 100);
			const int L = parameters.Get("contrast-limit", 25);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {
				CalculateMinMax(min, max, window);

				return (max - min) > L ? (max + min) / 2 : GT;
			});
		}
	};
}


#endif //BERNSEN_HPP
