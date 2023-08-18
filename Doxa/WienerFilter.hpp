// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WIENERFILTER_HPP
#define WIENERFILTER_HPP

#include "Types.hpp"
#include "Region.hpp"
#include "Image.hpp"
#include "ChanMeanVarianceCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// Wiener Filter - Implementation based on the wiener2 MathWorks algorithm.
	/// 
	/// TODO: Improve performance
	/// </summary>
	/// <remarks>Resource: https://www.mathworks.com/help/images/ref/wiener2.html </remarks>
	class WienerFilter
	{
	public:
		static void Filter(Image& outputImage, const Image& inputImage, const int windowSize = 3)
		{
			ChanMeanVarianceCalc calculator;

			// Obtain the average variance for all pixels
			double sumVariance = 0;

			calculator.Iterate(inputImage, windowSize, [&](const double&, const double& variance, const int&)
			{
				sumVariance += variance;
			});

			const double avgVariance = sumVariance / inputImage.size;

			// Apply Wiener Filter
			calculator.Iterate(inputImage, windowSize, [&](const double& mean, const double& variance, const int& position)
			{
				// The avgVariance is simulating noise-variance.  It should always be greater than variance.
				outputImage.data[position] = variance < avgVariance ?
					mean : // Variance can be 0, so avoid the divide by 0 issue by using mean value.
					mean + ((variance - avgVariance) * (double)(inputImage.data[position] - mean)) / variance;
			});
		}
	};
}


#endif //WIENERFILTER_HPP
