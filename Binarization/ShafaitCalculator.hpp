// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef SHAFAITCALCULATOR_HPP
#define SHAFAITCALCULATOR_HPP

#include <vector>
#include "Types.hpp"
#include "LocalWindow.hpp"
#include "Region.hpp"


namespace Binarization
{
	typedef std::vector<int64_t> IntegralImage;

	class ShafaitCalculator
	{
	public:
		ShafaitCalculator() :
			integral_image(0), 
			integral_sqimg(0), 
			imageWidth(0) 
		{}

		void Initialize(const Image& grayScaleImageIn)
		{
			integral_image.resize(grayScaleImageIn.size);
			integral_sqimg.resize(grayScaleImageIn.size);
			imageWidth = grayScaleImageIn.width;

			BuildIntegralImages(integral_image, integral_sqimg, grayScaleImageIn);
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

		virtual void BuildIntegralImages(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImageIn) = 0;

	protected:
		inline void CalculateDiffs(double& diff, double& sqdiff, const Region& window) const
		{
			const int xmax_ymax = (window.bottomRight.y * imageWidth) + window.bottomRight.x;

			if (window.upperLeft.x)
			{
				const int xmin_ymax = (window.bottomRight.y * imageWidth) + (window.upperLeft.x - 1);

				if (window.upperLeft.y)
				{
					const int xmax_ymin = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;
					const int xmin_ymin = ((window.upperLeft.y - 1) * imageWidth) + (window.upperLeft.x - 1);

					diff = (integral_image[xmax_ymax] + integral_image[xmin_ymin]) - (integral_image[xmax_ymin] + integral_image[xmin_ymax]);
					sqdiff = (integral_sqimg[xmax_ymax] + integral_sqimg[xmin_ymin]) - (integral_sqimg[xmax_ymin] + integral_sqimg[xmin_ymax]);
				}
				else
				{
					diff = integral_image[xmax_ymax] - integral_image[xmin_ymax];
					sqdiff = integral_sqimg[xmax_ymax] - integral_sqimg[xmin_ymax];
				}
			}
			else
			{
				if (window.upperLeft.y)
				{
					const int xmax_ymin = ((window.upperLeft.y - 1) * imageWidth) + window.bottomRight.x;

					diff = integral_image[xmax_ymax] - integral_image[xmax_ymin];
					sqdiff = integral_sqimg[xmax_ymax] - integral_sqimg[xmax_ymin];
				}
				else
				{
					diff = integral_image[xmax_ymax];
					sqdiff = integral_sqimg[xmax_ymax];
				}
			}
		}

		IntegralImage integral_image;
		IntegralImage integral_sqimg;
		int imageWidth;
	};

	/// <summary>
	/// This class provides an efficient way of calculating mean, variance, and standard deviation for an image.
	/// It uses an Integral Image technique which works perfectly with windowed areas.
	/// </summary>
	/// <remarks>"Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.</remarks>
	class Shafait : public ShafaitCalculator
	{
	public:
		Shafait()
			: ShafaitCalculator() {}

	protected:
		void BuildIntegralImages(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImageIn)
		{
			IntegralImage rowSumImage(grayScaleImageIn.size);
			IntegralImage rowSumSqrImage(grayScaleImageIn.size);
			int rowIdx = 0;

			for (int y = 0; y < grayScaleImageIn.height; ++y)
			{
				rowIdx = (y * grayScaleImageIn.width);
				rowSumImage[rowIdx] = grayScaleImageIn.data[rowIdx];
				rowSumSqrImage[rowIdx] = grayScaleImageIn.data[rowIdx] * grayScaleImageIn.data[rowIdx];
			}

			for (int y = 0; y < grayScaleImageIn.height; ++y)
			{
				for (int x = 1; x < grayScaleImageIn.width; ++x)
				{
					rowIdx = (y * grayScaleImageIn.width) + x;
					rowSumImage[rowIdx] = rowSumImage[rowIdx - 1] + grayScaleImageIn.data[rowIdx];
					rowSumSqrImage[rowIdx] = rowSumSqrImage[rowIdx - 1] + grayScaleImageIn.data[rowIdx] * grayScaleImageIn.data[rowIdx];
				}
			}

			for (int x = 0; x < grayScaleImageIn.width; ++x)
			{
				integralImage[x] = rowSumImage[x];
				integralSqrImage[x] = rowSumSqrImage[x];
			}

			for (int y = 1; y < grayScaleImageIn.height; ++y)
			{
				for (int x = 0; x < grayScaleImageIn.width; ++x)
				{
					rowIdx = (y * grayScaleImageIn.width) + x;
					integralImage[rowIdx] = integralImage[rowIdx - grayScaleImageIn.width] + rowSumImage[rowIdx];
					integralSqrImage[rowIdx] = integralSqrImage[rowIdx - grayScaleImageIn.width] + rowSumSqrImage[rowIdx];
				}
			}
		}
	};

	/// <summary>
	/// This is a slight variation of the algorithm Shafait had inspired which avoids the creation of two temporary Integral Images.
	/// </summary>
	class Shafait_LowMem : public ShafaitCalculator
	{
	public:
		Shafait_LowMem()
			: ShafaitCalculator() {}

	protected:
		void BuildIntegralImages(IntegralImage& integralImage, IntegralImage& integralSqrImage, const Image& grayScaleImageIn)
		{
			int rowIdx;
			int cellIdx;

			integralImage[0] = grayScaleImageIn.data[0];
			integralSqrImage[0] = integralImage[0] * integralImage[0];

			for (int y = 1; y < grayScaleImageIn.height; ++y)
			{
				rowIdx = (y * grayScaleImageIn.width);
				integralImage[rowIdx] = integralImage[rowIdx - grayScaleImageIn.width] + grayScaleImageIn.data[rowIdx];
				integralSqrImage[rowIdx] = grayScaleImageIn.data[rowIdx] * grayScaleImageIn.data[rowIdx] + integralSqrImage[rowIdx - grayScaleImageIn.width];
			}

			for (int x = 1; x < grayScaleImageIn.width; ++x)
			{
				integralImage[x] = integralImage[x - 1] + grayScaleImageIn.data[x];
				integralSqrImage[x] = grayScaleImageIn.data[x] * grayScaleImageIn.data[x] + integralSqrImage[x - 1];
			}

			for (int y = 1; y < grayScaleImageIn.height; ++y)
			{
				rowIdx = (y * grayScaleImageIn.width);
				int rowSum = grayScaleImageIn.data[rowIdx];

				for (int x = 1; x < grayScaleImageIn.width; ++x)
				{
					cellIdx = (rowIdx)+x;

					integralImage[cellIdx] = integralImage[cellIdx - grayScaleImageIn.width] + rowSum + grayScaleImageIn.data[cellIdx];

					rowSum += grayScaleImageIn.data[cellIdx];
				}
			}

			for (int x = 1; x < grayScaleImageIn.width; ++x)
			{
				int colSqrSum = grayScaleImageIn.data[x] * grayScaleImageIn.data[x];

				for (int y = 1; y < grayScaleImageIn.height; ++y) {
					rowIdx = (y * grayScaleImageIn.width) + x;

					colSqrSum += grayScaleImageIn.data[rowIdx] * grayScaleImageIn.data[rowIdx];

					integralSqrImage[rowIdx] = colSqrSum + integralSqrImage[rowIdx - 1];
				}
			}
		}
	};
}


#endif //SHAFAITCALCULATOR_HPP
