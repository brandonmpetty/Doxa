// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#ifndef MULTISCALE_HPP
#define MULTISCALE_HPP

#include "Algorithm.hpp"
#include "Morphology.hpp"


namespace Doxa
{
	/// <summary>
	/// Multi-Scale Algorithm: Reza Farrahi Moghaddam, Mohamed Cheriet
	/// 
	/// This algorithm takes in an initial scale, aka the window size, and stitches together a final binarized output
	/// based on the output for binarized images taken at different scales.  These images are eroded and any connecting
	/// pixels are assigned to the final output image.
	/// 
	/// This algorithm, in the paper, is paired with a Grid image processor.  Depending on the number of scales, a
	/// grid-based approach may be necessary in order to reduce the overall runtime of the underlying algorithm.
	/// 
	/// Note:
	/// This should not be confused with "Efficient Multiscale Sauvola’s Binarization" by Guillaume Lazzara and Thierry Géraud.
	/// 
	/// </summary>
	/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010.</remarks>
	template<class BinarizationClass>
	class MultiScale : public Algorithm<MultiScale<BinarizationClass>>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const int Slow = 9;
			const int Shigh = parameters.Get("window", 75);

			double k = parameters.Get("k", 1.0);

			// Input and Output cannot be the same
			assert(MultiScale::grayScaleImageIn.data != binaryImageOut.data);

			Image binarizedMap(MultiScale::grayScaleImageIn.width, MultiScale::grayScaleImageIn.height);
			Image binarizedMask(MultiScale::grayScaleImageIn.width, MultiScale::grayScaleImageIn.height);

			// Seed our binary output
			BinarizationClass algorithm;
			algorithm.Initialize(MultiScale::grayScaleImageIn);
			algorithm.ToBinary(binaryImageOut, parameters);

			// Create our first binarized mask
			Morphology::Erode(binarizedMask, binaryImageOut, Shigh / 4);

			// Copy parameters and only change 'windows' and 'k', keeping all others
			Parameters msParams(parameters);

			// Iterate over multiple window scales
			for (int S = Shigh / 2; S >= Slow; S = S / 2, k = k / 2)
			{
				// Get scaled map
				msParams.Set("window", S);
				msParams.Set("k", k);
				algorithm.ToBinary(binarizedMap, msParams);

				// Apply mask
				for (int idx = 0; idx < binarizedMask.size; ++idx)
				{
					if (binarizedMask.data[idx] == Palette::Black && binarizedMap.data[idx] == Palette::Black)
					{
						binaryImageOut.data[idx] = Palette::Black;
					}
				}

				// Avoid calculating the next Mask if we aren't going to use it
				if (S / 2 < Slow) break;

				// Obtain the next Mask
				Morphology::Erode(binarizedMask, binarizedMap, S / 4);
			}
		}
	};
}


#endif //MUTISCALEGRID_HPP
