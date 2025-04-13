// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#ifndef GRIDCALC_HPP
#define GRIDCALC_HPP

#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// A Grid based calculation algorithm designed originally for Sauvola and the original AdOtsu.
	/// It calculates a limited number of thresholds in a grid pattern throughout the image and then uses those
	/// values to interpolate the thresholds of the remaining pixels.
	/// 
	/// By setting the Distance parameter to "windowSize / 2", you get overlapping windows as called for by
	/// the AdOtsu paper.  If you set the Distance to windowSize, you get no overlap, like what is written about
	/// by Feng.
	/// 
	/// Note: While statistic based algorithms have the luxury of leveraging optimizations like Chan or Integral
	/// Images, function based algorithms like AdOtsu do not.  This is intended for un-optimized algorithms only!
	/// This algorithm is not a free lunch.  It is semi-expensive to run and it only *estimates* thresholds.
	/// </summary>
	/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010.</remarks>
	class GridCalc
	{
	public:

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, const int dist, Algorithm algorithm)
		{
			// Calculate thresholds at specific intervals throughout the image
			Iterate(grayScaleImageIn, windowSize, dist, [&](const Region& window, const int& position) 
			{
				binaryImageOut.data[position] = algorithm(window, position);
			});

			// Estimate the remaining thresholds using Bilinear Interpolation
			Interpolate(binaryImageOut, dist, [&](const int& position, const int& threshold)
			{
				binaryImageOut.data[position] = threshold;
			});
		}

		/// <summary>
		/// Iterates the image, calculating the corners of the window.
		/// Window Size and how far windows are apart from each other are somewhat indepenent.
		/// Distances between 2 and Window Size are possible.
		/// </summary>
		template<typename Processor>
		static void Iterate(const Image& imageIn, const int windowSize, const int dist, Processor processor)
		{
			const int HALF_WINDOW = windowSize / 2; // Note: Compiler rounding -  3 / 2 = 1

			const int imageWidthSub = imageIn.width - 1;
			const int imageHeightSub = imageIn.height - 1;

			const int xCount = (std::ceil((float)(imageWidthSub) / dist) + 1) * dist;
			const int yCount = (std::ceil((float)(imageHeightSub) / dist) + 1) * dist;

			Region window;

			for (int y = 0; y < yCount; y += dist)
			{
				const int yCoord = std::min(y, imageHeightSub);
				const int rowIdx = imageIn.width * yCoord;

				window.upperLeft.y = (std::max)(0, yCoord - HALF_WINDOW);
				window.bottomRight.y = (std::min)(imageHeightSub, yCoord + HALF_WINDOW);

				for (int x = 0; x < xCount; x += dist)
				{
					const int xCoord = std::min(x, imageWidthSub);
					const int idx = rowIdx + xCoord;

					window.upperLeft.x = (std::max)(0, xCoord - HALF_WINDOW);
					window.bottomRight.x = (std::min)(imageWidthSub, xCoord + HALF_WINDOW);

					processor(window, idx);
				}
			}
		}

		/// <summary>
		/// Interpolates an image that has already been Iterated.
		/// This algorithm attempts to iterate the image in a memory efficient way.
		/// It is very... verbose, but it is well optimized.
		/// </summary>
		template <typename Processor>
		static void Interpolate(const Image& imageIn, const int dist, Processor processor)
		{
			const int regularColCount = (imageIn.width - 1) / dist;
			const int regularRowCount = (imageIn.height - 1) / dist;
			const int remainingX = (imageIn.width - regularColCount * dist) - 1;
			const int remainingY = (imageIn.height - regularRowCount * dist) - 1;

			// An optimized algorithm for rows that pre-calculated values in them
			auto processRowOptimized = [&imageIn](int& idx, const int colCount, const int dist, const int remainingDist, Processor processor)
			{
				// Seed our Left-most value
				Pixel8 q00Val = imageIn.data[idx];

				// Iterate through all standard distance cells
				for (int colIdx = 0; colIdx <= colCount; ++colIdx)
				{
					// Make sure we stay within the bounds of the row
					const int interval = (colIdx != colCount) ? dist : remainingDist;

					// Set our Right-most value
					const Pixel8 q01Val = imageIn.data[idx + interval];

					idx++; // Skip - Already processed

					// Process standard spaced nodes
					for (int x = 1; x < interval; ++x, ++idx)
					{
						// Pre-calculated for optimization
						const float xDivInt = (float)x / interval;

						const Pixel8 threshold =
							0.5f +
							(1.0f - xDivInt) * q00Val +
							xDivInt * q01Val;

						processor(idx, threshold);
					}

					// What was once our Right-most value, is now our Left-most
					q00Val = q01Val;
				}

				if (remainingDist > 0)
				{
					idx++; // Skip - Processed
				}
			};

			// Process all of the rows for a block of rows
			auto processRows = [&imageIn, &processRowOptimized](int& idx, const int rowGap, const int rowCount, const int colCount, const int dist, const int remainingDist, Processor processor)
			{
				const int yIdx00 = idx;
				const int yIdx10 = yIdx00 + rowGap;

				// Process first row
				processRowOptimized(idx, colCount, dist, remainingDist, processor);

				// Iterate through every row
				for (int rowIdx = 1; rowIdx < rowCount; ++rowIdx)
				{
					// Seed our Left-most values
					Pixel8 q00Val = imageIn.data[yIdx00];
					Pixel8 q10Val = imageIn.data[yIdx10];

					int yIdx01 = yIdx00;
					int yIdx11 = yIdx10;

					// Pre-calculated for optimization
					const float rowIdxDivRowCount = (float)rowIdx / rowCount;

					// Iterate through all standard distance cells
					for (int colIdx = 0; colIdx <= colCount; ++colIdx)
					{
						// Make sure we stay within the bounds of the row
						const int interval = (colIdx != colCount) ? dist : remainingDist;
						yIdx01 += interval;
						yIdx11 += interval;

						// Set our Right-most values
						const Pixel8 q01Val = imageIn.data[yIdx01];
						const Pixel8 q11Val = imageIn.data[yIdx11];

						// Column optimized equation
						const Pixel8 threshold =
							0.5f +
							(1.0 - rowIdxDivRowCount) * q00Val +
							rowIdxDivRowCount * q10Val;
						processor(idx, threshold);

						idx++;

						// Process standard spaced nodes
						for (int x = 1; x < interval; ++x, ++idx)
						{
							// Pre-calculated for optimization
							const float xDivInt = (float)x / interval;

							const float top =
								(1.0f - xDivInt) * q00Val +
								xDivInt * q01Val;

							const float bottom =
								(1.0f - xDivInt) * q10Val +
								xDivInt * q11Val;

							const Pixel8 threshold =
								0.5f +
								(1.0f - rowIdxDivRowCount) * top +
								rowIdxDivRowCount * bottom;

							processor(idx, threshold);
						}

						// What was once our Right-most values, is now our Left-most
						q00Val = q01Val;
						q10Val = q11Val;
					}

					// Column optimized equation
					if (remainingDist > 0)
					{
						const Pixel8 threshold =
							0.5f +
							(1.0f - rowIdxDivRowCount) * q00Val +
							rowIdxDivRowCount * q10Val;

						processor(idx, threshold);

						idx++;
					}
				}
			};

			// The Interpolation Algorithm
			int idx = 0;
			const int rowGap = dist * imageIn.width;

			for (int y = 0; y < regularRowCount; ++y)
			{
				processRows(idx, rowGap, dist, regularColCount, dist, remainingX, processor);
			}

			if (remainingY)
			{
				processRows(idx, remainingY * imageIn.width, remainingY, regularColCount, dist, remainingX, processor);
			}

			processRowOptimized(idx, regularColCount, dist, remainingX, processor);
		}
	};
}


#endif //GRIDCALC_HPP
