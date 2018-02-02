// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef LOCALWINDOW_HPP
#define LOCALWINDOW_HPP

#include <vector>
#include <algorithm>
#include "Image.hpp"
#include "Palette.hpp"


namespace Binarization
{
	class LocalWindow
	{
	public:
		template<typename Algorithm>
		static void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, Algorithm algorithm)
		{
			Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				binaryImageOut.data[position] =
					grayScaleImageIn.data[position] <= algorithm(window) ?
					Palette::Black : Palette::White;
			});
		}

		template<typename Algorithm>
		static void Process(Image& image, const int windowSize, Algorithm algorithm)
		{
			Iterate(image, windowSize, [&](const Region& window, const int& position) {
				image.data[position] = //TODO Change Alpha to hold binary value?
					image.data[position] <= algorithm(window) ?
					Palette::Black : Palette::White;
			});
		}

		template<typename Processor>
		static void Iterate(const Image& grayScaleImageIn, const int windowSize, Processor processor)
		{
			const int HALF_WINDOW = windowSize / 2;
			Region window;

			for (int y = 0; y < grayScaleImageIn.height; ++y)
			{
				// Set Y Window Coordinates
				window.upperLeft.y = (std::max)(0, y - HALF_WINDOW);
				window.bottomRight.y = (std::min)(grayScaleImageIn.height - 1, y + HALF_WINDOW);

				for (int x = 0; x < grayScaleImageIn.width; ++x)
				{
					// Set X Window Coordinates
					window.upperLeft.x = (std::max)(0, x - HALF_WINDOW);
					window.bottomRight.x = (std::min)(grayScaleImageIn.width - 1, x + HALF_WINDOW);

					const int position = (y * grayScaleImageIn.width) + x;

					processor(window, position);
				}
			}
		}
	};
}


#endif //LOCALWINDOW_HPP
