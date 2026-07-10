// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef ISAUVOLA_HPP
#define ISAUVOLA_HPP

#include <vector>
#include "Sauvola.hpp"
#include "ContrastImage.hpp"
//#include "Morphology.hpp"


namespace Doxa
{
	/// <summary>
	/// The ISauvola Algorithm: Zineb Hadjadj, Abdelkrimo Meziane, Yazid Cherfa, Mohamed Cheriet, Insaf Setitra
	/// 
	/// This algorithm has been abstracted so that any binarization algorithm can leverage this technique.
	/// Example: Improved&lt;Sauvola&gt;::ToBinaryImage(...);
	/// </summary>
	/// <remarks>"ISauvola: Improved Sauvola’s Algorithm for Document Image Binarization", 2016.</remarks>
	template<class BinarizationClass>
	class Improved : public Algorithm<Improved<BinarizationClass>>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Step 1 - Initialization Step
			Image highContrastImage(Improved::grayScaleImageIn.width, Improved::grayScaleImageIn.height);
			ContrastImage::GenerateHighContrastImage(highContrastImage, Improved::grayScaleImageIn);

			// Step 1 b - Removing Open because it removes too much detail
			//Morphology::Open(highContrastImage, highContrastImage, 3);

			// Step 2 - Binarization Step
			Image binImage = BinarizationClass::ToBinaryImage(Improved::grayScaleImageIn, parameters);

			// Step 3 - Sequential Combination
			Combine(binaryImageOut, highContrastImage, binImage);
		}

	protected:
		/// <summary>
		/// This algorithm leverages a high contrast image to find where the foreground might be.
		/// Once a foreground pixel is found, all connected pixels are associated with it as part of the
		/// final binary image.
		/// </summary>
		/// <param name="binaryImageOut">Final image</param>
		/// <param name="highContrastImageIn">A high contrast image of the grayscale image</param>
		/// <param name="binaryImageIn">A high detail, but probably noisy, binary image</param>
		void Combine(Image& binaryImageOut, const Image& highContrastImageIn, const Image& binaryImageIn)
		{
			// Ensure that everything is white to start off with
			binaryImageOut.Fill(Palette::White);

			// Iterate every pixel of our high contrast image
			for (int idx = 0; idx < highContrastImageIn.size; ++idx)
			{
				// Detect a high contrast region that contains a foreground pixel
				if (Palette::White == highContrastImageIn.data[idx] &&
					Palette::Black == binaryImageIn.data[idx])
				{
					// If we haven't already analyzed this pixel's connections, analyze them
					if (Palette::White == binaryImageOut.data[idx])
					{
						Spider(binaryImageOut, binaryImageIn, idx);
					}
				}
			}
		}

		/// <summary>
		/// Spider is a fairly crafty algorithm that tracks down all connected foreground pixels given a 
		/// starting point.  It does this non-recursively by searching a 3x3 area around the target pixel.
		/// 
		/// This takes advantage of the fact that many Niblack based binarization algorithms create a
		/// small background buffer around the foreground that is free from noise.
		/// </summary>
		/// <param name="binaryImageOut">Image containing the traced foreground.</param>
		/// <param name="binaryImageIn">Image containing the foreground to trace.</param>
		/// <param name="startIdx">A foreground pixel location to start the trace.</param>
		void Spider(Image& binaryImageOut, const Image& binaryImageIn, const int startIdx)
		{
			const int width = binaryImageIn.width;

			// The output image doubles as our visited set, so each pixel is stacked at most once
			std::vector<int> stack = { startIdx };
			binaryImageOut.data[startIdx] = Palette::Black;

			while (!stack.empty())
			{
				// Pop target position index
				const int idx = stack.back();
				stack.pop_back();

				// Clamp the 3x3 search window to the image edges
				const int x = idx % width;
				const int left = x > 0 ? -1 : 0;
				const int right = x + 1 < width ? 1 : 0;
				const int top = idx < width ? idx : idx - width;
				const int bottom = idx + width < binaryImageIn.size ? idx + width : idx;

				for (int row = top; row <= bottom; row += width)
				{
					for (int position = row + left; position <= row + right; ++position)
					{
						// If an attached cell hasn't been traced, mark it and add it to the stack
						if (Palette::Black == binaryImageIn.data[position] &&
							Palette::White == binaryImageOut.data[position])
						{
							binaryImageOut.data[position] = Palette::Black;
							stack.push_back(position);
						}
					}
				}
			}
		}
	};

	/// <summary>
	/// A convenience name for backwards compatibility with this library.
	/// </summary>
	typedef Improved<Sauvola> ISauvola;
}


#endif //ISAUVOLA_HPP
