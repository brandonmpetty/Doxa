// Δoxa Binarization Framework
// License: CC0 2020, "Freely you have received; freely give." - Matt 10:8
#ifndef CHANMEANVARIANCECALC_HPP
#define CHANMEANVARIANCECALC_HPP

#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// The Chan Algorithm: Chungkwong Chan
	/// This algorithm is an advancement over Integral Images for extremely fast Mean / Variance calculation.
	/// It also uses only a fraction of the memory while allowing for much larger images.
	/// </summary>
	/// <remarks>"Memory-efficient and fast implementation of local adaptive binarization methods", 2019.</remarks>
	class ChanMeanVarianceCalc
	{
	public:

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			Iterate(grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int position) {
				binaryImageOut.data[position] =
					grayScaleImageIn.data[position] <= algorithm(mean, variance, position) ?
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

			// Initialize structures
			uint16_t* integral = new uint16_t[width + 1];
			int32_t* integralSquare = new int32_t[width + 1];
			memset(integral, 0, (width + 1) * sizeof(uint16_t));
			memset(integralSquare, 0, (width + 1) * sizeof(int32_t));

			// Starting at the top of the image, sum the columns to half our window height.
			// Note that Left and Right Window names are synonymous with Top and Bottom since this is a square window.
			// Our structures have now been primed.
			for (int y = 0, ind = 0; y < rightWindow; ++y)
			{
				for (int x = 1; x <= width; x++, ind++)
				{
					const int pixel = grayScaleImageIn.data[ind];
					integral[x] += pixel;
					integralSquare[x] += pixel * pixel;
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
						const int pixel = grayScaleImageIn.data[index];
						integral[x] -= pixel;
						integralSquare[x] -= pixel * pixel;
					}
				}

				if (y + rightWindow < height)
				{
					for (int x = 1, index = winBottom * width; x <= width; ++x, ++index)
					{
						const int pixel = grayScaleImageIn.data[index];
						integral[x] += pixel;
						integralSquare[x] += pixel * pixel;
					}
				}

				// At this point we slide our window from left to right.
				// We calculate the sums for the first half of our window.
				int sum = 0;
				int squareSum = 0;
				for (int x = 1; x <= dr1; x++)
				{
					sum += integral[x];
					squareSum += integralSquare[x];
				}

				// As our window moves across, we are now able to use our sums to calcuate mean, variance, etc.
				// This happens until the right most edge of our windows hits the end of the image.
				for (int x = 1; x < dr2; ++x, ++ind)
				{
					const int winLeft = std::max(x - leftWindow, 0);
					const int winRight = x + rightWindow;
					const int count = (winBottom - winTop)*(winRight - winLeft);
					sum += integral[winRight] - integral[winLeft];
					squareSum += integralSquare[winRight] - integralSquare[winLeft];

					const double mean = ((double)sum) / count;
					const double variance = ((double)squareSum) / count - mean * mean;

					processor(mean, variance, ind);
				}

				// Now that our windows is sliding through the right side of the image, we have to remove the left most colum.
				// As we do that, we are able to continue with our calcuation.
				for (int x = dr2; x <= width; ++x, ++ind)
				{
					const int winLeft = std::max(x - leftWindow, 0);
					const int winRight = width;
					const int count = (winBottom - winTop)*(winRight - winLeft);
					sum -= integral[winLeft];
					squareSum -= integralSquare[winLeft];

					const double mean = ((double)sum) / count;
					const double variance = ((double)squareSum) / count - mean * mean;

					processor(mean, variance, ind);
				}
			}

			// Free up our dynamically allocated structures
			delete[] integral;
			delete[] integralSquare;
		}
	};
}


#endif //CHANMEANVARIANCECALC_HPP
