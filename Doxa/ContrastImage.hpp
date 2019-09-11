// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef CONTRASTIMAGE_HPP
#define CONTRASTIMAGE_HPP

#include "Types.hpp"
#include "Otsu.hpp"
#include "Palette.hpp"
#include "Region.hpp"
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

			Pixel8 min, max;

			Image minImage(grayScaleImage.width, grayScaleImage.height);
			Image maxImage(grayScaleImage.width, grayScaleImage.height);

			Morphology::Erode(minImage, grayScaleImage, windowSize);
			Morphology::Dilate(maxImage, grayScaleImage, windowSize);

			LocalWindow::Iterate(grayScaleImage, windowSize, [&](const Region& window, const int& position) {

				min = minImage.data[position];
				max = maxImage.data[position];

				const double contrastMultiplier = (double)(max - min) / (max + min + 0.0001);

				// Note: The paper leaves out the fact that the Contrast Image actually has to be normalized.
				// To normalize it back into an 8bit gray scale image, simply multiply by 255.
				contrastImage.data[position] = 255 * contrastMultiplier;
			});
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
