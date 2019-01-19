// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef MINMAXCALCULATOR_HPP
#define MINMAXCALCULATOR_HPP

#include "Types.hpp"
#include "LocalWindow.hpp"
#include "Region.hpp"

////////////////////////////////////////////////////////////////////////
// This code is being depricated in favor of Morphology.hpp           //
////////////////////////////////////////////////////////////////////////

namespace Doxa
{
	/// <summary>
	/// Calculates the Min and/or Max values of a local window.
	/// A copy of the gray scale image should be made when using this calculator.
	/// 
	/// TODO: Read article on vHGW: A fast algorithm for local minimum and maximum filters on rectangular and octagonal kernels
	/// </summary>
	class MinMaxCalculator
	{
	public:
		void Initialize(const Image& grayScaleImage)
		{
			image = grayScaleImage.Reference();
		}

		inline void CalculateMax(Pixel8& max, const Region& window) const
		{
			max = 0;

			LocalWindow::Iterate(image.width, window, [&](const int& position) {
				const int value = image.data[position];
				if (value > max)
				{
					max = value;
				}
			});
		}

		inline void CalculateMinMax(Pixel8& min, Pixel8& max, const Region& window) const
		{
			min = 255;
			max = 0;

			LocalWindow::Iterate(image.width, window, [&](const int& position) {
				const int value = image.data[position];
				if (value < min)
				{
					min = value;
				}
				else if (value > max)
				{
					max = value;
				}
			});
		}

	protected:
		Image image;
	};
}


#endif //MINMAXCALCULATOR_HPP
