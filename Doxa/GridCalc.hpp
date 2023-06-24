// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef GRIDCALC_HPP
#define GRIDCALC_HPP

#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// A Grid based calculation algorithm designed originally for Sauvola and the original AdOtsu.
	/// It calculates a limited number of thresholds in a grid pattern throughout the image and then uses those
	/// values to interpolate the thresholds of the surrounding pixels.
	/// 
	/// Note: While statistic based algorithms have the luxury of leveraging Chan or Integral Images, function based
	/// algorithms like AdOtsu do not.  The resulting "image" for AdOtsu would be a Threshold Array, while the
	/// resulting images for Saulova would be Mean and Std Deviation Arrays.
	/// </summary>
	/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010.</remarks>
	class GridCalc
	{
	public:

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			// Build a sample image comprized of calculation samples taken in a grid pattern
			// This sample image size is based on the number of samples taken, which is based on the window size.
			// ...
			Image sampleImage(grayScaleImageIn.width / windowSize, grayScaleImageIn.height / windowSize);

			// Create a full interpolated image based on our sample image
			// ...
		}

		template<typename Processor>
		void Iterate(const Image& grayScaleImageIn, const int windowSize, Processor processor)
		{

		}
	};
}


#endif //GRIDCALC_HPP
