// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef MEANVARIANCECALCULATOR_HPP
#define MEANVARIANCECALCULATOR_HPP

#include "MeanCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Shafait Algorithm: Faisal Shafait, Daniel Keysers, Thomas M. Breuel
	/// An integral image based calculator for calculating Mean, Variance, and Std. Deviation.
	/// </summary>
	/// <remarks>"Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.</remarks>
	class MeanVarianceCalculator
		: public MeanCalculator
	{
	public:
		MeanVarianceCalculator()
			: MeanCalculator(),
			integral_sqimg(0) {}

		void Initialize(const Image& grayScaleImage)
		{
			integral_image.resize(grayScaleImage.size);
			imageWidth = grayScaleImage.width;
			integral_sqimg.resize(grayScaleImage.size);

			BuildIntegralImages(integral_image, integral_sqimg, grayScaleImage);
		}

		inline void CalculateMeanStdDev(double& mean, double& stddev, const Region& window) const
		{
			CalculateMeanVariance(mean, stddev, window);

			stddev = sqrt(stddev);
		}

		inline void CalculateMeanVariance(double& mean, double& variance, const Region& window) const
		{
			// Note: This data type has a large impact on performance.
			double diff, sqdiff;
			CalculateDiffs(diff, sqdiff, window);

			// Get the Mean and Variance using our Shafait inspired algorithm
			const int area = window.Area();
			mean = diff / area;
			variance = (sqdiff - diff*diff / area) / (area - 1);
		}

	protected:
		inline void CalculateDiffs(double& diff, double& sqdiff, const Region& window) const
		{
			// Optimization Note: With MSVC, simplifying this to match MeanCalculator::CalculateDiffs incurred a small performance hit.

			const int bottomRight = (window.bottomRight.y * imageWidth) + window.bottomRight.x;

			if (window.upperLeft.x)
			{
				const int bottomLeft = (window.bottomRight.y * imageWidth) + (window.upperLeft.x - 1);

				if (window.upperLeft.y)
				{
					const int upperRight = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;
					const int upperLeft = ((window.upperLeft.y - 1) * imageWidth) + (window.upperLeft.x - 1);

					diff = (integral_image[bottomRight] + integral_image[upperLeft]) - (integral_image[upperRight] + integral_image[bottomLeft]);
					sqdiff = (integral_sqimg[bottomRight] + integral_sqimg[upperLeft]) - (integral_sqimg[upperRight] + integral_sqimg[bottomLeft]);
				}
				else
				{
					diff = integral_image[bottomRight] - integral_image[bottomLeft];
					sqdiff = integral_sqimg[bottomRight] - integral_sqimg[bottomLeft];
				}
			}
			else
			{
				if (window.upperLeft.y)
				{
					const int upperRight = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;

					diff = integral_image[bottomRight] - integral_image[upperRight];
					sqdiff = integral_sqimg[bottomRight] - integral_sqimg[upperRight];
				}
				else
				{
					diff = integral_image[bottomRight];
					sqdiff = integral_sqimg[bottomRight];
				}
			}
		}

		void BuildIntegralImages(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImage)
		{
			IntegralImage rowSumImage(grayScaleImage.size);
			IntegralImage rowSumSqrImage(grayScaleImage.size);
			int rowIdx = 0;

			for (int y = 0; y < grayScaleImage.height; ++y)
			{
				rowIdx = (y * grayScaleImage.width);
				rowSumImage[rowIdx] = grayScaleImage.data[rowIdx];
				rowSumSqrImage[rowIdx] = grayScaleImage.data[rowIdx] * grayScaleImage.data[rowIdx];
			}

			for (int y = 0; y < grayScaleImage.height; ++y)
			{
				for (int x = 1; x < grayScaleImage.width; ++x)
				{
					rowIdx = (y * grayScaleImage.width) + x;
					rowSumImage[rowIdx] = rowSumImage[rowIdx - 1] + grayScaleImage.data[rowIdx];
					rowSumSqrImage[rowIdx] = rowSumSqrImage[rowIdx - 1] + grayScaleImage.data[rowIdx] * grayScaleImage.data[rowIdx];
				}
			}

			for (int x = 0; x < grayScaleImage.width; ++x)
			{
				integralImage[x] = rowSumImage[x];
				integralSqrImage[x] = rowSumSqrImage[x];
			}

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				for (int x = 0; x < grayScaleImage.width; ++x)
				{
					rowIdx = (y * grayScaleImage.width) + x;
					integralImage[rowIdx] = integralImage[rowIdx - grayScaleImage.width] + rowSumImage[rowIdx];
					integralSqrImage[rowIdx] = integralSqrImage[rowIdx - grayScaleImage.width] + rowSumSqrImage[rowIdx];
				}
			}
		}

		/// <summary>
		/// This is "low memory" version of BuildIntralImages(...).
		/// It achieves this by removing the need for two temporary integral images.
		/// Warning: The speed performance compared to the reference may be slower depending on image size.
		/// </summary>
		void BuildIntegralImagesLowMem(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImage)
		{
			int row;
			int cell;

			integralImage[0] = grayScaleImage.data[0];
			integralSqrImage[0] = integralImage[0] * integralImage[0];

			for (int y = 1; y < grayScaleImage.height; ++y)
			{
				row = (y * grayScaleImage.width);
				integralImage[row] = integralImage[row - grayScaleImage.width] + grayScaleImage.data[row];
				integralSqrImage[row] = grayScaleImage.data[row] * grayScaleImage.data[row] + integralSqrImage[row - grayScaleImage.width];
			}

			for (int x = 1; x < grayScaleImage.width; ++x)
			{
				integralImage[x] = integralImage[x - 1] + grayScaleImage.data[x];
				integralSqrImage[x] = grayScaleImage.data[x] * grayScaleImage.data[x] + integralSqrImage[x - 1];
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

			for (int x = 1; x < grayScaleImage.width; ++x)
			{
				int colSqrSum = grayScaleImage.data[x] * grayScaleImage.data[x];

				for (int y = 1; y < grayScaleImage.height; ++y) {
					row = (y * grayScaleImage.width) + x;

					colSqrSum += grayScaleImage.data[row] * grayScaleImage.data[row];

					integralSqrImage[row] = colSqrSum + integralSqrImage[row - 1];
				}
			}
		}

		IntegralImage integral_sqimg;
	};
}


#endif //MEANVARIANCECALCULATOR_HPP
