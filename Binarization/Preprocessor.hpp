/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include "Image.hpp"
#include "Palette.hpp"


namespace Binarization
{
	class Preprocessor
	{
	public:

		// Grey Scale Convertion
		// Note: The image is 32b color but will become 8b gray scale.  The actually image depth will not be updated.
		//		You will have to convert it to Palette::Black or White which will convert it back to 32b values.
		//		The reason is due to a lack of Pixel8 support.  It is also faster than converting it to 32b gray scale.
		static void ToGreyScale(Image& image)
		{
			const int size = image.size;

			// Convert the entire image to gray scale one pixel at a time
			for (int index = 0; index < size; ++index)
			{
				// Convert to gray scale - this will save us from having to recalculate it later.
				image.data[index] = Palette::Gray(image.data[index]);
			}
		}
	};
}


#endif // PREPROCESSOR_HPP
