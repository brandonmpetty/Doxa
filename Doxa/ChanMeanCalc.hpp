// Δoxa Binarization Framework
// License: CC0 2020, "Freely you have received; freely give." - Matt 10:8
#ifndef CHANMEANCALC_HPP
#define CHANMEANCALC_HPP

#include <algorithm>
#include <cstdint>
#include <vector>
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
			const int above = (windowSize + 1) / 2;	// Window rows above the pixel, and columns to its left
			const int below = windowSize - above;	// Window rows below the pixel, and columns to its right
			const Pixel8* input = grayScaleImageIn.data;

			// Vertical window sums, one per column, zero padded on the left and right.
			std::vector<int32_t> sums(width + windowSize, 0);
			const std::vector<Pixel8> zeroRow(width, 0);
			int32_t* const colSum = sums.data() + above;

			// Slide the window down the image one row at a time.
			// The first iterations, y < 0, prime the columns before the first window is complete.
			for (int y = -below, position = 0; y < height; ++y)
			{
				// Add the row entering the window and subtract the row leaving it.
				// Past the top and bottom of the image, an all-zero row stands in.
				const Pixel8* enter = y + below < height ? input + (y + below) * width : zeroRow.data();
				const Pixel8* leave = y >= above ? input + (y - above) * width : zeroRow.data();

				for (int x = 0; x < width; ++x)
				{
					colSum[x] += enter[x] - leave[x];
				}

				if (y < 0) continue;

				const int rows = (std::min)(y + below, height - 1) - (std::max)(y - above, -1);

				// Prime the sliding sum with the columns under the right half of the window.
				int64_t sum = 0;
				for (int x = 0; x < below; ++x)
				{
					sum += colSum[x];
				}

				// Slide the window across the row, adding the column entering it and subtracting the
				// column leaving it.  The pixel count only changes near the left and right edges, so
				// the reciprocal is cached; the branch predictor learns the pattern instantly.
				int lastCols = 0;
				double invCount = 0.0;
				for (int x = 0; x < width; ++x, ++position)
				{
					const int xBelow = x + below;
					const int xAbove = x - above;

					sum += colSum[xBelow] - colSum[xAbove];

					const int cols = (std::min)(xBelow, width - 1) - (std::max)(xAbove, -1);
					if (cols != lastCols) { invCount = 1.0 / (rows * cols); lastCols = cols; }

					const double mean = sum * invCount;

					processor(mean, position);
				}
			}
		}
	};
}


#endif //CHANMEANCALC_HPP
