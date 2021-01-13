// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef INTEGRALIMAGEMEANCALC_HPP
#define INTEGRALIMAGEMEANCALC_HPP

#include "Types.hpp"
#include "LocalWindow.hpp"
#include "Region.hpp"
#include "IntegralImage.h"


namespace Doxa
{
	/// <summary>
	/// A fast integral image based calculator for calculating the Mean.
	/// It is largely inspired by Shafait, but deviates from the reference implementation.
	/// This deviation should greatly improve the performance for Mean-only calculations.
	/// </summary>
	class IntegralImageMeanCalc
	{
	public:
		IntegralImageMeanCalc() {}

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			const int imageWidth = grayScaleImageIn.width;

			// Initialize Integral Image
			IntegralImage integralImage(grayScaleImageIn.size);
			BuildIntegralImage(integralImage, grayScaleImageIn);

			// Run our binarization algorithm
			double mean, variance;
			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window, const int& index) {
				CalculateMean(mean, imageWidth, integralImage, window);

				return algorithm(mean, index);
			});
		}

		inline void CalculateMean(double& mean, const int imageWidth, const IntegralImage& integralImage, const Region& window) const
		{
			// Note: This data type has a large impact on performance.
			double diff;
			CalculateDiff(diff, imageWidth, integralImage, window);

			// Get the Mean using our Shafait inspired algorithm
			const int area = window.Area();
			mean = diff / area;
		}

		inline void CalculateDiff(double& diff, const int imageWidth, const IntegralImage& integralImage, const Region& window) const
		{
			const int bottomRight = (window.bottomRight.y * imageWidth) + window.bottomRight.x;

			diff = integralImage[bottomRight];

			if (window.upperLeft.y)
			{
				const int upperRight = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;

				diff -= integralImage[upperRight];
			}

			if (window.upperLeft.x)
			{
				const int bottomLeft = (window.bottomRight.y * imageWidth) + (window.upperLeft.x - 1);

				diff -= integralImage[bottomLeft];

				if (window.upperLeft.y)
				{
					const int upperLeft = ((window.upperLeft.y - 1) * imageWidth) + (window.upperLeft.x - 1);

					diff += integralImage[upperLeft];
				}
			}
		}

		void BuildIntegralImage(IntegralImage& integralImage, const Image& grayScaleImage)
		{
			int row;
			int cell;

			integralImage[0] = grayScaleImage.data[0];

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				row = (y * grayScaleImage.width);
				integralImage[row] = integralImage[row - grayScaleImage.width] + grayScaleImage.data[row];
			}

			for (int x = 1; x < grayScaleImage.width; ++x)
			{
				integralImage[x] = integralImage[x - 1] + grayScaleImage.data[x];
			}

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				row = (y * grayScaleImage.width);
				int rowSum = grayScaleImage.data[row];

				for (int x = 1; x < grayScaleImage.width; ++x)
				{
					cell = row + x;
					rowSum += grayScaleImage.data[cell];

					integralImage[cell] = integralImage[cell - grayScaleImage.width] + rowSum;
				}
			}
		}
	};
}


#endif //INTEGRALIMAGEMEANCALC_HPP
