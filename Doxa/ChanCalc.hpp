// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef CHANCALC_HPP
#define CHANCALC_HPP

#include <algorithm>
#include <cstdint>
#include <vector>
#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// Local window sum calculators based on the Chan algorithm, a family of
	/// three siblings sharing the same sliding-window skeleton:
	///
	///   ChanMeanCalc          Mean over the window.
	///
	///   ChanMeanVarianceCalc  Mean and Population Variance over the window.
	///
	///   ChanMaskedCalc        Count, sum, and optionally sum of squares over
	///                         only those window pixels selected by a binary
	///                         mask image.
	///
	/// Each keeps one vertical running sum per column, updated as the window
	/// slides down the image, so memory use is O(width) regardless of image
	/// height.  Those sums are zero padded on every side so that a single
	/// sliding-window pass, free of bounds checks, handles the image edges
	/// and interior alike.
	///
	/// The Chan Algorithm: Chungkwong Chan
	/// This algorithm is an advancement over Integral Images for extremely
	/// fast windowed statistics.  It also uses only a fraction of the memory
	/// while allowing for much larger images.
	/// </summary>
	/// <remarks>"Memory-efficient and fast implementation of local adaptive binarization methods", 2019.</remarks>
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

					const int cols = (std::min)(xBelow, width - 1) - (std::max)(xAbove, -1);
					if (cols != lastCols)
					{
						invCount = 1.0 / (rows * cols);
						lastCols = cols;
					}

					sum += colSum[xBelow] - colSum[xAbove];
					const double mean = sum * invCount;

					processor(mean, position);
				}
			}
		}
	};


	/// <summary>
	/// A version of the Chan algorithm for calculating Mean and Population Variance.
	/// Note: 32-bit sums of squares cap the window size at 33,025.
	/// </summary>
	/// <see cref="ChanMeanCalc"/>
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
			const int above = (windowSize + 1) / 2;	// Window rows above the pixel, and columns to its left
			const int below = windowSize - above;	// Window rows below the pixel, and columns to its right
			const Pixel8* input = grayScaleImageIn.data;

			// Vertical window sums, one per column, zero padded on the left and right.
			std::vector<int32_t> sums(width + windowSize, 0);
			std::vector<int32_t> squareSums(width + windowSize, 0);
			const std::vector<Pixel8> zeroRow(width, 0);
			int32_t* const colSum = sums.data() + above;
			int32_t* const colSquareSum = squareSums.data() + above;

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
					colSquareSum[x] += enter[x] * enter[x] - leave[x] * leave[x];
				}

				if (y < 0) continue;

				const int rows = (std::min)(y + below, height - 1) - (std::max)(y - above, -1);

				// Prime the sliding sums with the columns under the right half of the window.
				int64_t sum = 0;
				int64_t squareSum = 0;
				for (int x = 0; x < below; ++x)
				{
					sum += colSum[x];
					squareSum += colSquareSum[x];
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

					const int cols = (std::min)(xBelow, width - 1) - (std::max)(xAbove, -1);
					if (cols != lastCols)
					{
						invCount = 1.0 / (rows * cols);
						lastCols = cols;
					}

					sum += colSum[xBelow] - colSum[xAbove];
					const double mean = sum * invCount;

					squareSum += colSquareSum[xBelow] - colSquareSum[xAbove];
					const double variance = squareSum * invCount - mean * mean;

					processor(mean, variance, position);
				}
			}
		}
	};


	/// <summary>
	/// A version of the Chan algorithm for calculating windowed statistics over
	/// only those pixels selected by a mask.  The mask must be a binary image
	/// whose pixels are all Palette::White (0xFF) or Palette::Black (0x00);
	/// White selects a pixel.  That guarantee makes the masking branchless:
	/// value & mask gates the value and mask & 1 counts it.
	///
	/// The processor receives the count of selected pixels and the sum of their
	/// values; with WithSquares it also receives the sum of their squared values:
	///
	///   processor(int64_t count, int64_t sum, position)  WithSquares = false
	///   processor(int64_t count, int64_t sum, int64_t squareSum, position)  WithSquares = true
	///
	/// Note: With WithSquares, 32-bit sums of squares cap the window size at 33,025.
	/// </summary>
	/// <see cref="ChanMeanCalc"/>
	template<bool WithSquares = false>
	class ChanMaskedCalc
	{
	public:

		template<typename Processor>
		static void Iterate(const Image& valueImageIn, const Image& maskImageIn, const int windowSize, Processor processor)
		{
			// Setup constants
			const int width = valueImageIn.width;
			const int height = valueImageIn.height;
			const int above = (windowSize + 1) / 2;	// Window rows above the pixel, and columns to its left
			const int below = windowSize - above;	// Window rows below the pixel, and columns to its right
			const Pixel8* value = valueImageIn.data;
			const Pixel8* mask = maskImageIn.data;

			// Vertical window sums, one per column, zero padded on the left and right.
			std::vector<int32_t> counts(width + windowSize, 0);
			std::vector<int32_t> sums(width + windowSize, 0);
			std::vector<int32_t> squareSums(WithSquares ? width + windowSize : 0, 0);
			const std::vector<Pixel8> zeroRow(width, 0);
			int32_t* const colCount = counts.data() + above;
			int32_t* const colSum = sums.data() + above;
			int32_t* const colSquareSum = WithSquares ? squareSums.data() + above : nullptr;

			// Slide the window down the image one row at a time.
			// The first iterations, y < 0, prime the columns before the first window is complete.
			for (int y = -below, position = 0; y < height; ++y)
			{
				// Add the row entering the window and subtract the row leaving it.
				// Past the top and bottom of the image, an all-zero row stands in
				// for both the values and the mask.
				const bool hasEnter = y + below < height;
				const bool hasLeave = y >= above;
				const Pixel8* enterValue = hasEnter ? value + (y + below) * width : zeroRow.data();
				const Pixel8* enterMask = hasEnter ? mask + (y + below) * width : zeroRow.data();
				const Pixel8* leaveValue = hasLeave ? value + (y - above) * width : zeroRow.data();
				const Pixel8* leaveMask = hasLeave ? mask + (y - above) * width : zeroRow.data();

				for (int x = 0; x < width; ++x)
				{
					const int32_t enter = enterValue[x] & enterMask[x];
					const int32_t leave = leaveValue[x] & leaveMask[x];

					colCount[x] += (enterMask[x] & 1) - (leaveMask[x] & 1);
					colSum[x] += enter - leave;
					if constexpr (WithSquares)
					{
						colSquareSum[x] += enter * enter - leave * leave;
					}
				}

				if (y < 0) continue;

				// Prime the sliding sums with the columns under the right half of the window.
				int64_t count = 0;
				int64_t sum = 0;
				int64_t squareSum = 0;
				for (int x = 0; x < below; ++x)
				{
					count += colCount[x];
					sum += colSum[x];
					if constexpr (WithSquares)
					{
						squareSum += colSquareSum[x];
					}
				}

				// Slide the window across the row, adding the column entering it
				// and subtracting the column leaving it.
				for (int x = 0; x < width; ++x, ++position)
				{
					const int xBelow = x + below;
					const int xAbove = x - above;

					count += colCount[xBelow] - colCount[xAbove];
					sum += colSum[xBelow] - colSum[xAbove];

					if constexpr (WithSquares)
					{
						squareSum += colSquareSum[xBelow] - colSquareSum[xAbove];
						processor(count, sum, squareSum, position);
					}
					else
					{
						processor(count, sum, position);
					}
				}
			}
		}
	};
}


#endif //CHANCALC_HPP
