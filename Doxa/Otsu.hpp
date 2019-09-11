// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef OTSU_HPP
#define OTSU_HPP

#include "Types.hpp"
#include "Algorithm.hpp"
#include "Image.hpp"
#include "Palette.hpp"


namespace Doxa
{
	/// <summary>
	/// The Otsu Algorithm: Nobuyuki Otsu
	/// 
	/// This implementation was actually inspired by:
	/// "A C++ Implementation of Otsu’s Image Segmentation Method", 2016.
	/// Thank you, Juan Pablo Balarini & Sergio Nesmachnow
	/// </summary>
	/// <remarks>"A threshold selection method from gray-level histograms", 1979.</remarks>
	class Otsu : public GlobalThreshold<Otsu>
	{
	public:
		static const int HISTOGRAM_SIZE = 256;

		Pixel8 Threshold(const Image& grayScaleImage, const Parameters& parameters = Parameters())
		{
			// Compute number of pixels
			long int N = grayScaleImage.size;
			Pixel8 threshold = 0;

			// Compute threshold
			// Init variables
			int sum = 0;
			int sumB = 0;
			int q1 = 0;
			double max = 0;

			// Create Histogram
			unsigned int histogram[HISTOGRAM_SIZE]; // Placed on stack for performance.  This shouldn't be too large.
			memset(histogram, 0, (HISTOGRAM_SIZE) * sizeof(unsigned int));
			for (int idx = 0; idx < grayScaleImage.size; ++idx)
			{
				++histogram[grayScaleImage.data[idx]];
			}

			// Calculate sum
			for (int idx = 0; idx < HISTOGRAM_SIZE; ++idx) 
			{
				sum += idx * histogram[idx];
			}

			for (int idx = 0; idx < HISTOGRAM_SIZE; ++idx) 
			{
				// q1 = Weighted Background
				q1 += histogram[idx];
				if (q1 == 0)
					continue;

				// q2 = Weighted Forground
				const int q2 = N - q1;
				if (q2 == 0)
					break;

				sumB += (idx * histogram[idx]);

				const double m1m2 = 
					(double)sumB / q1 -			// Mean Background
					(double)(sum - sumB) / q2;	// Mean Forground

				// Note - There is an insidious casting situation going on here.
				// If one were to multiple by q1 or q2 first, an explicit cast would be required!
				const double between = m1m2 * m1m2 * q1 * q2;

				if (between > max) 
				{
					threshold = idx;
					max = between;
				}
			}

			return threshold;
		}
	};
}


#endif //OTSU_HPP
