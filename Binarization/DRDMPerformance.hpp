/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef DRDMPERFORMANCE_HPP
#define DRDMPERFORMANCE_HPP

#include <algorithm>
#include <list>
#include "Image.hpp"
#include "Palette.hpp"
#include "Region.hpp"


namespace Binarization
{
	class DRDMPerformance
	{
	public:
		static double CalculateDRDM(const Image& controlImage, const Image& expirementImage)
		{
			// S - Get a list of all points that differ between the two images
			std::list<Region::Point> s;
			PixelDifferences(s, controlImage, expirementImage);

			// DRDk - For every difference, get its DRDk value and sum them all
			uint64_t sumDRDk = 0;
			for (Region::Point point : s)
			{
				sumDRDk += DRDk(point, controlImage, expirementImage.Pixel(point.x, point.y));
			}

			// To avoid rounding issues we are using ints instead of doubles, which we accomplished by using a 1000000 multiplier.
			return sumDRDk / (double)(NUBN(controlImage) * 1000000);
		}

	protected:

		static int DRDk(const Region::Point& point, const Image& controlImage, const Pixel32& g)
		{
			const int N = 5; // Hard coded for now.
			const int NPadding = N / 2; // Ammount of padding around the pixel based on an NxN matrix with that pixel in the center.

			// Normalized Weighted Matrix
			// Values have been multiplied by 1000000 in order to avoid slight rounding errors with doubles.
			// These values are more granular than the example matrix given in the research paper.
			// If you use those values, you will hit rounding problems with their sample data because they are actually using more 
			// precise Normalized Matrix values when calculating DRD than what is provided in that example.
			const int Wm[N][N] = {
				{ 25582, 32359, 36179, 32359, 25582 },
				{ 32359, 51164, 72357, 51164, 32359 },
				{ 36179, 72357,     0, 72357, 36179 },
				{ 32359, 51164, 72357, 51164, 32359 },
				{ 25582, 32359, 36179, 32359, 25582 }
			};

			long sumDRDkBlock = 0;

			// Create a window around a point
			Region window(
				point.x - NPadding,
				point.y - NPadding,
				point.x + NPadding,
				point.y + NPadding
			);

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
					const int Dk = (controlImage.Pixel(window.upperLeft.x + x, window.upperLeft.y + y, g) - g) == 0 ? 0 : 1;
					sumDRDkBlock +=  Dk * Wm[x][y];
				}
			}

			return sumDRDkBlock;
		}

		// Returns a list of points that differ between the two images
		static void PixelDifferences(std::list<Region::Point>& points, const Image& controlImage, const Image& expirementImage)
		{
			for (int x = 0; x < controlImage.width; ++x)
			{
				for (int y = 0; y < controlImage.height; ++y)
				{
					if (controlImage.Pixel(x, y) != expirementImage.Pixel(x, y))
					{
						points.push_back(Region::Point(x, y));
					}
				}
			}
		}

		// The number of blocks in the image that are not uniform.  This means blocks that have both white and black pixels.
		static int NUBN(const Image& controlImage, const int M = 8)
		{
			int nubn = 0;

			const int columns = ceil(controlImage.width / M);
			const int rows = ceil(controlImage.height / M);

			// Get a specific block
			for (int column = 0; column < columns; ++column)
			{
				for (int row = 0; row < rows; ++row)
				{
					nubn += NonUniformBlock(controlImage, column, row, M);
				}
			}

			return nubn;
		}

		// Determines if a block is uniform (0) or not (1).
		static int NonUniformBlock(const Image& controlImage, const int column, const int row, const int M = 8)
		{
			// Process all of the pixels in said block
			const int startX = column * M;
			const int startY = row * M;

			const int stopX = startX + M;
			const int stopY = startY + M;

			Pixel32 pixel = controlImage.Pixel(startX, startY);

			for (int x = startX; x < stopX; ++x)
			{
				for (int y = startY; y < stopY; ++y)
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


#endif //DRDMPERFORMANCE_HPP
