// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WAN_HPP
#define WAN_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MeanVarianceCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The WAN Algorithm: Wan Azani Mustafa, Mohamed Mydin M. Abdul Kader
	/// </summary>
	/// <remarks>"Binarization of Document Image Using Optimum Threshold Modification", 2018.</remarks>
	class Wan : public Algorithm<Wan>, public MeanVarianceCalculator
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

			// Use Dilate to generate a Max Image for the target Window
			Image maxImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			Morphology::Dilate(maxImage, Algorithm::grayScaleImageIn, windowSize);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				CalculateMeanStdDev(mean, stddev, window);

				return (((double)maxImage.data[position] + mean) / 2) * (1 + k * ((stddev / 128) - 1));
			});
		}
	};
}


#endif //WAN_HPP
