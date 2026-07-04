// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef XDOG_HPP
#define XDOG_HPP

#include <cmath>
#include "Algorithm.hpp"
#include "Filter.hpp"
#include "Palette.hpp"


namespace Doxa
{
	/// <summary>
	/// The XDoG (eXtended Difference-of-Gaussians) thresholding algorithm:
	/// Holger Winnemollera, Jan Eric Kyprianidisb, Sven C. Olsen
	///
	/// Uses the sharpening (p) reparameterization from Winnemoller 2012
	/// (Eq. 7), followed by the soft threshold (Eq. 5):
	///
	///   S(x) = (1 + p) * G_sigma(x) - p * G_{k*sigma}(x)
	///   T(u) = 1                             : if u >= epsilon
	///          1 + tanh(phi * (u - epsilon)) : otherwise
	///   binary = (T < 0.5) ? Black : White
	///
	/// The paper assumes a CIE Lab colorspace with a focus on the
	/// luminance channel.
	///
	/// Parameters (via the standard Parameters key-value object):
	///   "sigma"   double  default 1.0   -- inner Gaussian sigma
	///                                      (sigma_e in the paper)
	///   "k"       double  default 1.8   -- ratio sigma_outer/sigma_inner
	///   "p"       double  default 35.0  -- edge sharpening strength
	///                                      (paper notes "p near 20"
	///                                      gives interesting results;
	///                                      larger p exaggerates edges)
	///   "epsilon" double  default 0.20  -- threshold on [0, 1] scale
	///   "phi"     double  default 10.0  -- tanh ramp steepness; larger
	///                                      values approach a step function
	///
	/// NOTES: The flow-based variant (FDoG, Section 2.6) is not implemented.
	/// </summary>
	/// <remarks>"XDoG: AneXtended difference-of-Gaussians compendium including advanced image stylization", 2012.</remarks>
	class XDoG : public Algorithm<XDoG>
	{
	public:
		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const Image& in = Algorithm::grayScaleImageIn;

			const double sigma   = parameters.Get("sigma",   1.0);
			const double k       = parameters.Get("k",       1.8);
			const double p       = parameters.Get("p",       35.0);
			const double epsilon = parameters.Get("epsilon", 0.20);
			const double phi     = parameters.Get("phi",     10.0);

			const int sizeInner = KernelSize(sigma);
			const int sizeOuter = KernelSize(k * sigma);

			Image blurInner(in.width, in.height);
			Image blurOuter(in.width, in.height);

			Filter::Gaussian(blurInner, in, sizeInner, sigma);
			Filter::Gaussian(blurOuter, in, sizeOuter, k * sigma);

			const int N = in.size;
			for (int i = 0; i < N; ++i)
			{
				// Eq. 7: S = (1 + p) * G_sigma - p * G_{k*sigma}, normalized to [0, 1]
				const double s = ((1.0 + p) * blurInner.data[i]
				                - p         * blurOuter.data[i]) / 255.0;

				// Eq. 5: soft threshold around epsilon
				const double t = (s >= epsilon)
					? 1.0
					: 1.0 + std::tanh(phi * (s - epsilon));

				binaryImageOut.data[i] = (t < 0.5) ? Palette::Black : Palette::White;
			}
		}

	private:
		// Odd kernel covering +/- 3*sigma; floor at 3 to keep the kernel
		// meaningful even when sigma is tiny.
		static int KernelSize(double sigma)
		{
			int n = static_cast<int>(std::ceil(3.0 * sigma)) * 2 + 1;
			return n < 3 ? 3 : n;
		}
	};
}


#endif // XDOG_HPP
