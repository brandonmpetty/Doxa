// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef CONTRASTIMAGE_HPP
#define CONTRASTIMAGE_HPP

#include <vector>
#include "Types.hpp"
#include "Otsu.hpp"
#include "Palette.hpp"
#include "Morphology.hpp"


namespace Doxa
{
	/// <summary>
	/// Contrast Image generation class
	/// </summary>
	/// <remarks>"Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.</remarks>
	class ContrastImage
	{
	public:
		static inline void GenerateContrastImage(Image& contrastImage, const Image& grayScaleImage)
		{
			const int windowSize = 3;

			Image minImage(grayScaleImage.width, grayScaleImage.height);
			Image maxImage(grayScaleImage.width, grayScaleImage.height);

			Morphology::Erode(minImage, grayScaleImage, windowSize);
			Morphology::Dilate(maxImage, grayScaleImage, windowSize);

			for (int position = 0; position < grayScaleImage.size; ++position)
			{
				const Pixel8 min = minImage.data[position];
				const Pixel8 max = maxImage.data[position];

				const double contrastMultiplier = (double)(max - min) / (0.0001 + max + min);

				// Note: The paper leaves out the fact that the Contrast Image actually has to be normalized.
				// To normalize it back into an 8bit gray scale image, simply multiply by 255.
				contrastImage.data[position] = 255 * contrastMultiplier;
			}
		}

		/// <summary>
		/// Estimates the text stroke width from a contrast image by scanning each row
		/// for peak contrast pixels and building a histogram of distances between adjacent peaks.
		/// The most frequent distance corresponds to the stroke width.
		/// </summary>
		static inline int EstimateStrokeWidth(const Image& contrastImage)
		{
			std::vector<int> histogram(contrastImage.width, 0);

			for (int y = 0; y < contrastImage.height; ++y)
			{
				const int row = y * contrastImage.width;
				int lastPeakX = -1;

				for (int x = 1; x < contrastImage.width - 1; ++x)
				{
					const Pixel8 val = contrastImage.data[row + x];

					if (val > contrastImage.data[row + x - 1] && val > contrastImage.data[row + x + 1])
					{
						if (lastPeakX >= 0)
						{
							++histogram[x - lastPeakX];
						}

						lastPeakX = x;
					}
				}
			}

			// The mode is the estimated stroke width (skip distance 1 as sub-pixel noise)
			int strokeWidth = 3;
			int maxCount = 0;

			for (int d = 2; d < contrastImage.width; ++d)
			{
				if (histogram[d] > maxCount)
				{
					maxCount = histogram[d];
					strokeWidth = d;
				}
			}

			return strokeWidth;
		}

		static inline void GenerateHighContrastImage(Image& highContrastImage, const Image& grayScaleImage)
		{
			// Generate Contrast Image
			GenerateContrastImage(highContrastImage, grayScaleImage);

			// Run it through Otsu binarization to make it a high contrast image
			Otsu otsu;
			otsu.Initialize(highContrastImage);
			otsu.ToBinary(highContrastImage);
		}
	};
}


#endif //CONTRASTIMAGE_HPP
