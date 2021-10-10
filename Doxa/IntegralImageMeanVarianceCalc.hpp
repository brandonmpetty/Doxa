// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef INTEGRALIMAGEMEANVARIANCECALC_HPP
#define INTEGRALIMAGEMEANVARIANCECALC_HPP

#include <vector>
#include "Image.hpp"
#include "Region.hpp"
#include "LocalWindow.hpp"


namespace Doxa
{
	typedef std::vector<int64_t> IntegralImage;

	/// <summary>
	/// The Shafait Algorithm: Faisal Shafait, Daniel Keysers, Thomas M. Breuel
	/// An integral image based calculator for calculating Mean, Population Variance.
	/// 
	/// Note: For extremely large images, this algorithm will fail.
	/// This algorithm has been replaced by Chan.  Chan is roughly 3x faster, consumes a fraction of the memory,
	/// and allows for large image processing.
	/// </summary>
	/// <remarks>"Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.</remarks>
	class IntegralImageMeanVarianceCalc
	{
	public:

		template<typename Algorithm>
		void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			const int imageWidth = grayScaleImageIn.width;

			// Initialize Integral Images
			IntegralImage integralImage(grayScaleImageIn.size), integralSqrImage(grayScaleImageIn.size);
			BuildIntegralImages(integralImage, integralSqrImage, grayScaleImageIn);
			//BuildIntegralImagesLowMem(integralImage, integralSqrImage, grayScaleImageIn); // This can significantly reduce the memory used, but may be slower

			// Run our binarization algorithm
			double mean, variance;
			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window, const int& index) {
				CalculateMeanVariance(mean, variance, imageWidth, integralImage, integralSqrImage, window);

				return algorithm(mean, variance, index);
			});
		}

		template<typename Processor>
		void Iterate(const Image& grayScaleImageIn, const int windowSize, Processor processor)
		{
			const int imageWidth = grayScaleImageIn.width;

			// Initialize Integral Images
			IntegralImage integralImage(grayScaleImageIn.size), integralSqrImage(grayScaleImageIn.size);
			BuildIntegralImages(integralImage, integralSqrImage, grayScaleImageIn);
			//BuildIntegralImagesLowMem(integralImage, integralSqrImage, grayScaleImageIn); // This can significantly reduce the memory used, but may be slower

			// Run our binarization algorithm
			double mean, variance;
			LocalWindow::Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& index) {
				CalculateMeanVariance(mean, variance, imageWidth, integralImage, integralSqrImage, window);

				return processor(mean, variance, index);
			});
		}

		inline void CalculateMeanVariance(double& mean, double& variance, const int imageWidth, const IntegralImage& integralImage, const IntegralImage& integralSqrImage, const Region& window) const
		{
			// Note: This data type has a large impact on performance.
			double diff, sqdiff;
			CalculateDiffs(diff, sqdiff, imageWidth, integralImage, integralSqrImage, window);

			// Get the Mean and Variance using our Shafait inspired algorithm
			const int area = window.Area();
			mean = diff / area;
			
			// Sample Variance
			//variance = (sqdiff - diff*diff / area) / (area - 1);

			// Population Variance
			variance = (sqdiff / area) - (mean * mean);
		}

		inline void CalculateDiffs(double& diff, double& sqdiff, const int imageWidth, const IntegralImage& integralImage, const IntegralImage& integralSqrImage, const Region& window) const
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

					diff = (integralImage[bottomRight] + integralImage[upperLeft]) - (integralImage[upperRight] + integralImage[bottomLeft]);
					sqdiff = (integralSqrImage[bottomRight] + integralSqrImage[upperLeft]) - (integralSqrImage[upperRight] + integralSqrImage[bottomLeft]);
				}
				else
				{
					diff = integralImage[bottomRight] - integralImage[bottomLeft];
					sqdiff = integralSqrImage[bottomRight] - integralSqrImage[bottomLeft];
				}
			}
			else
			{
				if (window.upperLeft.y)
				{
					const int upperRight = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;

					diff = integralImage[bottomRight] - integralImage[upperRight];
					sqdiff = integralSqrImage[bottomRight] - integralSqrImage[upperRight];
				}
				else
				{
					diff = integralImage[bottomRight];
					sqdiff = integralSqrImage[bottomRight];
				}
			}
		}

		void BuildIntegralImages(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImage)
		{
			// This algorithm uses two temporary images.  See BuildIntegralImagesLowMem for an alternative.
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
	};
}


#endif //INTEGRALIMAGEMEANVARIANCECALC_HPP
