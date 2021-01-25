// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef DRDM_HPP
#define DRDM_HPP

#include <algorithm>
#include "Image.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "LocalWindow.hpp"


namespace Doxa
{
	/// <summary>
	/// The Distance-Reciprocal Distortion Measure (DRDM) Algorithm: Haiping Lu, Jian Wang, A.C. Kot, Y.Q. Shi
	/// </summary>
	/// <remarks>"An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.</remarks>
	class DRDM
	{
	public:
		static double CalculateDRDM(const Image& controlImage, const Image& expirementImage)
		{
			const uint64_t sumDRDk = SumDRDkForMismatchedPixels(controlImage, expirementImage);

			// To avoid rounding issues we are using ints instead of doubles, which we accomplished by using a 1000000 multiplier.
			return sumDRDk / (double)(NUBN(controlImage) * 1000000);
		}

	protected:

		static unsigned int DRDk(const Region::Point& point, const Image& controlImage, const Pixel32& g)
		{
			const int N = 5; // Hard coded for now.
			const int NPadding = N / 2; // Ammount of padding around the pixel based on an NxN matrix with that pixel in the center.

			// Normalized Weighted Matrix
			// Values have been multiplied by 1000000 in order to avoid slight rounding errors with doubles.
			// These values are more granular than the example matrix given in the research paper.
			// If you use those values, you will hit rounding problems with their sample data because they are actually using more 
			// precise Normalized Matrix values when calculating DRD than what is provided in that example.
			const unsigned int Wm[N][N] = {
				{ 25582, 32359, 36179, 32359, 25582 },
				{ 32359, 51164, 72357, 51164, 32359 },
				{ 36179, 72357,     0, 72357, 36179 },
				{ 32359, 51164, 72357, 51164, 32359 },
				{ 25582, 32359, 36179, 32359, 25582 }
			};

			unsigned int sumDRDkBlock = 0;

			// Create a point in the upper left of our window.  We will traverse it differently below.
			Region::Point upperLeftPoint(point.x - NPadding, point.y - NPadding);

			// Move from the upper left to the bottom right of our window, pixel by pixel
			for (int x = 0; x < N; ++x)
			{
				for (int y = 0; y < N; ++y)
				{
					// If we are out of bounds, defaulting to g will essentially void the cell
					// The original paper *assumed* the data was literally binary, 1 or 0.
					// This is really just a fancy mathematical trick to say this: 
					//     For all of the cells in your control block (B) that do not match the different pixel (g), 
					//     take the values at those cooridates in the Weighted Matrix (Wm) and sum them up.  You're welcome.
					const unsigned int Dk = (controlImage.Pixel(upperLeftPoint.x + x, upperLeftPoint.y + y, g) - g) == 0 ? 0 : 1;
					sumDRDkBlock +=  Dk * Wm[x][y];
				}
			}

			return sumDRDkBlock;
		}

		static uint64_t SumDRDkForMismatchedPixels(const Image& controlImage, const Image& expirementImage)
		{
			uint64_t sumDRDk = 0;

			// S - Get a list of all points that differ between the two images
			for (int y = 0; y < controlImage.height; ++y)
			{
				for (int x = 0; x < controlImage.width; ++x)
				{
					if (controlImage.Pixel(x, y) != expirementImage.Pixel(x, y))
					{
						// DRDk - For every difference, get its DRDk value and sum them all
						const Region::Point point(x, y);
						sumDRDk += DRDk(point, controlImage, expirementImage.Pixel(x, y));
					}
				}
			}

			return sumDRDk;
		}

		// The number of blocks in the image that are not uniform.  This means blocks that have both white and black pixels.
		static unsigned int NUBN(const Image& controlImage, const int M = 8)
		{
			unsigned int nubn = 0;

			const int columns = ceil(controlImage.width / M);
			const int rows = ceil(controlImage.height / M);

			// Get a specific block
			for (int column = 0; column < columns; ++column)
			{
				for (int row = 0; row < rows; ++row)
				{
					const Region window(column * M, row * M, M);
					nubn += NonUniformBlock(controlImage, window);
				}
			}

			return nubn;
		}

		// Determines if a block is uniform (0) or not (1).
		static unsigned int NonUniformBlock(const Image& controlImage, const Region& window)
		{
			// Process all of the pixels in said block
			const Pixel8 pixel = controlImage.Pixel(window.upperLeft.x, window.upperLeft.y);

			for (int y = window.upperLeft.y; y < window.bottomRight.y; ++y)
			{
				for (int x = window.upperLeft.x; x < window.bottomRight.x; ++x)
				{
					// If all of the pixels are not the same, count the block
					if (pixel != controlImage.Pixel(x, y, pixel))
					{
						return 1; // Non Uniform
					}
				}
			}

			return 0; // Uniform
		}
	};
}


#endif //DRDM_HPP
