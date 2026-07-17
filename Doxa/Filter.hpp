// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef FILTER_HPP
#define FILTER_HPP

#include <cmath>
#include <vector>
#include "Image.hpp"
#include "Convolution.hpp"
#include "ChanCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// Spatial-domain image filters.
	///
	///   Gaussian -- Variable-size separable Gaussian blur.  Kernel size must
	///               be odd.  If sigma is 0, it is derived from the kernel
	///               size via the OpenCV convention:
	///                 sigma = 0.3 * ((size - 1) * 0.5 - 1) + 0.8
	///               The kernel is normalized to sum to 1.0 so the output
	///               has the same mean intensity as the input.
	///
	///   Wiener   -- Adaptive noise-reduction filter based on MathWorks'
	///               wiener2 algorithm.  Estimates the noise variance as
	///               the mean of local variances and dampens each pixel
	///               toward its local mean when local variance is low.
	///               Resource: https://www.mathworks.com/help/images/ref/wiener2.html
	/// </summary>
	class Filter
	{
	public:
		static void Gaussian(Image& out, const Image& in, int kernelSize, double sigma = 0.0)
		{
			std::vector<double> kernel(kernelSize);
			MakeGaussianKernel1D(kernel.data(), kernelSize, sigma);
			Convolution::ApplySeparable<double>(out, in, kernelSize, kernel.data());
		}

		static void Wiener(Image& out, const Image& in, const int windowSize = 3)
		{
			ChanMeanVarianceCalc calculator;

			// Obtain the average variance for all pixels
			double sumVariance = 0;

			calculator.Iterate(in, windowSize, [&](const double&, const double& variance, const int&)
			{
				sumVariance += variance;
			});

			const double avgVariance = sumVariance / in.size;

			// Apply Wiener Filter
			calculator.Iterate(in, windowSize, [&](const double& mean, const double& variance, const int& position)
			{
				// The avgVariance is simulating noise-variance.  It should always be greater than variance.
				out.data[position] = variance < avgVariance ?
					mean : // Variance can be 0, so avoid the divide by 0 issue by using mean value.
					mean + ((variance - avgVariance) * (double)(in.data[position] - mean)) / variance;
			});
		}

	private:
		static void MakeGaussianKernel1D(double* kernel, int size, double sigma)
		{
			if (sigma <= 0.0)
				sigma = 0.3 * ((size - 1) * 0.5 - 1) + 0.8;

			const int half = size / 2;
			const double inv2s2 = 1.0 / (2.0 * sigma * sigma);

			double sum = 0.0;
			for (int i = 0; i < size; ++i)
			{
				const double x = i - half;
				kernel[i] = std::exp(-x * x * inv2s2);
				sum += kernel[i];
			}

			const double invSum = 1.0 / sum;
			for (int i = 0; i < size; ++i)
				kernel[i] *= invSum;
		}
	};
}


#endif // FILTER_HPP
