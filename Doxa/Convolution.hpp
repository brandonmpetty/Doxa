// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include <algorithm>
#include <vector>
#include "Types.hpp"
#include "Image.hpp"
#include "Region.hpp"


namespace Doxa
{
	class Convolution
	{
	public:
		typedef std::vector<int> ConvolutionImage;

		/// <summary>
		/// This method is used primarily for detecting veritcal edges in an image
		/// </summary>
		void SobelVertical(ConvolutionImage& convolutionImage, const Image& grayScaleImage)
		{
			const int kernelSize = 3;
			const int kernelArraySize = kernelSize * kernelSize;
			const int kernel[kernelArraySize] = {
				-1, 0, 1,
				-2, 0, 2,
				-1, 0, 1
			};

			Convolve(convolutionImage, grayScaleImage, kernelSize, kernel);
		}

		/// <summary>
		/// This method is used primarily for detecting horizontal edges in an image
		/// </summary>
		void SobelHorizontal(ConvolutionImage& convolutionImage, const Image& grayScaleImage)
		{
			const int kernelSize = 3;
			const int kernelArraySize = kernelSize * kernelSize;
			const int kernel[kernelArraySize] = {
				-1, -2, -1,
				 0,  0,  0,
				 1,  2,  1
			};

			Convolve(convolutionImage, grayScaleImage, kernelSize, kernel);
		}

		/// <summary>
		/// This method is used primarily for detecting edges in an image
		/// </summary>
		void Laplacian(ConvolutionImage& convolutionImage, const Image& grayScaleImage)
		{
			const int kernelSize = 3;
			const int kernelArraySize = kernelSize * kernelSize;
			const int kernel[kernelArraySize] = {
				-1, -1, -1,
				-1,  8, -1,
				-1, -1, -1
			};

			Convolve(convolutionImage, grayScaleImage, kernelSize, kernel);
		}

		/// <summary>
		/// Convolve allows you to generate a convolution image from a kernel.
		/// This algorithm can generically calculate varying sized kernels with very little performance tradeoff.
		/// When part of a window is outside of the image, the closest pixel's value will be used for those cells.
		/// </summary>
		/// <param name="convolutionImage">Can contain negative numbers and numbers larger than 255</param>
		/// <param name="grayScaleImage">Gray Scale input image</param>
		/// <param name="windowSize">The size of the kernel.  Must be odd.</param>
		/// <param name="kernel">A kernel of any size</param>
		void Convolve(ConvolutionImage& convolutionImage, const Image& grayScaleImage, const int windowSize, const int kernel[])
		{
			const int widthMinusOne = grayScaleImage.width - 1;
			const int heightMinusOne = grayScaleImage.height - 1;
			const int HALF_WINDOW = windowSize / 2;
			Region window;

			for (int yImageIdx = 0; yImageIdx < grayScaleImage.height; ++yImageIdx)
			{
				// Set Y Window Coordinates
				window.upperLeft.y = yImageIdx - HALF_WINDOW;
				window.bottomRight.y = yImageIdx + HALF_WINDOW;

				for (int xImageIdx = 0; xImageIdx < grayScaleImage.width; ++xImageIdx)
				{
					// Set X Window Coordinates
					window.upperLeft.x = xImageIdx - HALF_WINDOW;
					window.bottomRight.x = xImageIdx + HALF_WINDOW;

					const int rowImageIdx = yImageIdx * grayScaleImage.width;
					int kernelIdx = 0;
					int sum = 0;

					// Iterate the Window
					for (int yWindowIdx = window.upperLeft.y; yWindowIdx <= window.bottomRight.y; ++yWindowIdx)
					{
						// Ensure that if our window is outside the image, adjust where to get the right value.
						int yWindowAdjustedIdx = std::min(heightMinusOne, yWindowIdx);
						yWindowAdjustedIdx = std::max(0, yWindowAdjustedIdx);

						const int rowWindowAdjustedIdx = yWindowAdjustedIdx * grayScaleImage.width;

						for (int xWindowIdx = window.upperLeft.x; xWindowIdx <= window.bottomRight.x; ++xWindowIdx)
						{
							// Ensure that if our window is outside the image, adjust where to get the right value.
							int xWindowAdjustedIdx = std::min(widthMinusOne, xWindowIdx);
							xWindowAdjustedIdx = std::max(0, xWindowAdjustedIdx);

							// Multiply the Kernel Cell by the Image Cell and add to Sum
							sum += grayScaleImage.data[rowWindowAdjustedIdx + xWindowAdjustedIdx] * kernel[kernelIdx];

							// We iterate our Window using X/Y coordinates, but the Kernel is simply incremented
							kernelIdx++;
						}
					}

					convolutionImage[rowImageIdx + xImageIdx] = sum;
				}
			}
		}
	};
}

#endif // CONVOLUTION_HPP
