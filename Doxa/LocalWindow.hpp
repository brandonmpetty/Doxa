// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef LOCALWINDOW_HPP
#define LOCALWINDOW_HPP

#include <vector>
#include <algorithm>
#include "Image.hpp"
#include "Palette.hpp"
#include "Region.hpp"


namespace Doxa
{
	class LocalWindow
	{
	public:

		/// <summary>
		/// Converts a Gray Scale image into a Binary image given a specific algorithm.
		/// The algorithm should return a threshold under which a gray pixel will become black and
		/// over which it will become white.
		/// </summary>
		template<typename WindowCalculator>
		static void Process(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize, WindowCalculator calculator)
		{
			Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				binaryImageOut.data[position] =
					grayScaleImageIn.data[position] <= calculator(window, position) ?
						Palette::Black : Palette::White;
			});
		}

		/// <summary>
		/// Iterate an Image, providing the current position and a window.
		/// A Window is a region of the image surrounding a specific pixel that needs to be processed.
		/// </summary>
		template<typename Processor>
		static void Iterate(const Image& imageIn, const int windowSize, Processor processor)
		{
			const int HALF_WINDOW = windowSize / 2;
			Region window;

			for (int y = 0, ind = 0; y < imageIn.height; ++y)
			{
				// Set Y Window Coordinates
				window.upperLeft.y = (std::max)(0, y - HALF_WINDOW);
				window.bottomRight.y = (std::min)(imageIn.height - 1, y + HALF_WINDOW);

				for (int x = 0; x < imageIn.width; ++x, ++ind)
				{
					// Set X Window Coordinates
					window.upperLeft.x = (std::max)(0, x - HALF_WINDOW);
					window.bottomRight.x = (std::min)(imageIn.width - 1, x + HALF_WINDOW);

					processor(window, ind);
				}
			}
		}

		/// <summary>
		/// Iterate a Window, providing the current position within the window.
		/// </summary>
		template<typename Processor>
		static void Iterate(const int width, const Region& window, Processor processor)
		{
			for (int y = window.upperLeft.y; y <= window.bottomRight.y; ++y)
			{
				const int row = y * width;

				for (int x = window.upperLeft.x; x <= window.bottomRight.x; ++x)
				{
					processor(row + x);
				}
			}
		}
	};
}


#endif //LOCALWINDOW_HPP
