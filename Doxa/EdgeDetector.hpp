// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef EDGEDETECTOR_HPP
#define EDGEDETECTOR_HPP

#include "Convolution.hpp"

////////////////////////////////////////////////////////////////////////
// This code is highly experimental and has not been unit tested yet! //
////////////////////////////////////////////////////////////////////////

namespace Doxa
{
	class EdgeDetector
	{
	public:
		static void Sobel(Image& sobelImage, const Image& grayScaleImage)
		{
			// Generate Sobel Convolution Images
			Convolution::ConvolutionImage horizontalImage(grayScaleImage.size);
			Convolution::ConvolutionImage verticalImage(grayScaleImage.size);

			Convolution convolution;
			convolution.SobelHorizontal(horizontalImage, grayScaleImage);
			convolution.SobelVertical(verticalImage, grayScaleImage);

			for (int idx = 0; idx < grayScaleImage.size; ++idx)
			{
				// Calculate the Magnitude of the Gradient
				// TODO: Analyze estimation via absolute value to improve speed
				int value = std::sqrt((horizontalImage[idx] * horizontalImage[idx]) + (verticalImage[idx] * verticalImage[idx]));
				value = std::min(value, 255);

				// Invert the image
				sobelImage.data[idx] = 255 - value;
			}
		}

		static void Laplacian(Image& laplacianImage, const Image& grayScaleImage)
		{
			// Generate Laplacian
			Convolution::ConvolutionImage convolutionImage(grayScaleImage.size);
			
			Convolution convolution;
			convolution.Laplacian(convolutionImage, grayScaleImage);

			// Normalize it by cutting off values out of range
			for (int idx = 0; idx < grayScaleImage.size; ++idx)
			{
				int value = convolutionImage[idx];

				// Cut off any outliers, for which there are many, leaving only the edges.
				value = std::min(value, 255);
				value = std::max(value, 0);

				// Invert the image
				laplacianImage.data[idx] = 255 - value;
			}
		}
	};
}


#endif //EDGEDETECTOR_HPP
