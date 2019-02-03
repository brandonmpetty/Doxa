// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WIENERFILTER_HPP
#define WIENERFILTER_HPP

#include "Types.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "Image.hpp"
#include "MeanVarianceCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// Wiener Filter - Implementation based on the wiener2 MathWorks algorithm.
	/// 
	/// TODO: This is slow because I not estimating the local variance, but calculating it.
	/// This needs to be resolved in order to speed this up.
	/// </summary>
	/// <remarks>Resource: https://www.mathworks.com/help/images/ref/wiener2.html </remarks>
	class WienerFilter
	{
	public:
		static void Filter(Image& outputImage, const Image& inputImage, const int windowSize = 3)
		{
			MeanVarianceCalculator calculator;
			calculator.Initialize(inputImage);

			// Obtain the average variance for all pixels
			double mean, variance;
			double sumVariance = 0;

			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position)
			{
				calculator.CalculateMeanVariance(mean, variance, window);

				sumVariance += variance;
			});

			const double avgVariance = sumVariance / inputImage.size;

			// Apply Wiener Filter
			LocalWindow::Iterate(inputImage, windowSize, [&](const Region& window, const int& position)
			{
				calculator.CalculateMeanVariance(mean, variance, window);

				// The avgVariance is simulating noise-variance.  It should always be greater than variance.
				outputImage.data[position] = variance < avgVariance ?
					mean : // Variance can be 0, so avoid the divide by 0 issue by using mean value.
					mean + ((variance - avgVariance) * (double)(inputImage.data[position] - mean)) / variance;
			});
		}
	};
}


#endif //WIENERFILTER_HPP
