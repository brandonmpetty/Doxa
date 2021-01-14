// Δoxa Binarization Framework
// License: CC0 2020, "Freely you have received; freely give." - Matt 10:8
#ifndef CHANMEANCALC_HPP
#define CHANMEANCALC_HPP

#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// A version of the Chan algorithm for calculating just the Mean.
	/// </summary>
	/// <see cref="ChanMeanVarianceCalc"/>
	class ChanMeanCalc
	{
	public:

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			Iterate(grayScaleImageIn, windowSize, [&](const double& mean, const int position) {
				binaryImageOut.data[position] =
					grayScaleImageIn.data[position] <= algorithm(mean, position) ?
					Palette::Black : Palette::White;
			});
		}

		template<typename Processor>
		void Iterate(const Image& grayScaleImageIn, const int windowSize, Processor processor)
		{
			// Setup constants
			const int width = grayScaleImageIn.width;
			const int height = grayScaleImageIn.height;
			const int leftWindow = (windowSize + 1) / 2;
			const int rightWindow = windowSize - leftWindow;
			const int dr1 = rightWindow;
			const int dr2 = width - rightWindow + 1;

			// Initialize structure
			uint16_t* integral = new uint16_t[width + 1];
			memset(integral, 0, (width + 1) * sizeof(uint16_t));

			// Starting at the top of the image, sum the columns to half our window height.
			// Note that Left and Right Window names are synonymous with Top and Bottom since this is a square window.
			// Our structures have now been primed.
			for (int y = 0, ind = 0; y < rightWindow; ++y)
			{
				for (int x = 1; x <= width; x++, ind++)
				{
					integral[x] += grayScaleImageIn.data[ind];
				}
			}

			for (int y = 0, ind = 0; y < height; ++y)
			{
				const int winTop = std::max(y - leftWindow, -1);
				const int winBottom = std::min(height - 1, y + rightWindow);

				// As our windows slides down, these two blocks will remove the top row from our structure and add on the bottom row.
				if (y >= leftWindow) {
					for (int x = 1, index = winTop * width; x <= width; ++x, ++index)
					{ 
						integral[x] -= grayScaleImageIn.data[index];
					}
				}

				if (y + rightWindow < height)
				{
					for (int x = 1, index = winBottom * width; x <= width; ++x, ++index)
					{
						integral[x] += grayScaleImageIn.data[index];
					}
				}

				// At this point we slide our window from left to right.
				// We calculate the sums for the first half of our window.
				int sum = 0;
				for (int x = 1; x <= dr1; x++)
				{
					sum += integral[x];
				}

				// As our window moves across, we are now able to use our sums to calcuate mean, variance, etc.
				// This happens until the right most edge of our windows hits the end of the image.
				for (int x = 1; x < dr2; ++x, ++ind)
				{
					const int winLeft = std::max(x - leftWindow, 0);
					const int winRight = x + rightWindow;
					const int area = (winBottom - winTop)*(winRight - winLeft);
					sum += integral[winRight] - integral[winLeft];

					const double mean = ((double)sum) / area;

					processor(mean, ind);
				}

				// Now that our windows is sliding through the right side of the image, we have to remove the left most colum.
				// As we do that, we are able to continue with our calcuation.
				for (int x = dr2; x <= width; ++x, ++ind)
				{
					const int winLeft = std::max(x - leftWindow, 0);
					const int winRight = width;
					const int area = (winBottom - winTop)*(winRight - winLeft);
					sum -= integral[winLeft];

					const double mean = ((double)sum) / area;

					processor(mean, ind);
				}
			}

			// Free up our dynamically allocated structures
			delete[] integral;
		}
	};
}


#endif //CHANMEANCALC_HPP
