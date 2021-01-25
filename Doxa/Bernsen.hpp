// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef BERNSEN_HPP
#define BERNSEN_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "Morphology.hpp"


namespace Doxa
{
	/// <summary>
	/// The Bernsen Algorithm: John Bernsen
	/// </summary>
	/// <remarks>"Dynamic thresholding of gray-level images", 1986.</remarks>
	class Bernsen : public Algorithm<Bernsen>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			Pixel8 min, max;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const int GT = parameters.Get("threshold", 100);
			const int L = parameters.Get("contrast-limit", 25);

			// Build Min and Max images
			Image minImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			Image maxImage(Algorithm::grayScaleImageIn.width, Algorithm::grayScaleImageIn.height);
			Morphology::Erode(minImage, Algorithm::grayScaleImageIn, windowSize);
			Morphology::Dilate(maxImage, Algorithm::grayScaleImageIn, windowSize);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				min = minImage.data[position];
				max = maxImage.data[position];

				return (max - min) > L ? (max + min) / 2 : GT;
			});
		}
	};
}


#endif //BERNSEN_HPP
