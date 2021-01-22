// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef ISAUVOLA_HPP
#define ISAUVOLA_HPP

#include <unordered_set>
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
		/// This algorithm leverages a high contrast image to find where the forground might be.
		/// Once a forground pixel is found, all connected pixels are associated with it as part of the
		/// final binary image.
		/// </summary>
		/// <param name="binaryImageOut">Final image</param>
		/// <param name="highContrastImageIn">A high contrast image of the grayscale image</param>
		/// <param name="binaryImageIn">A high detail, but probably noisey, binary image</param>
		void Combine(Image& binaryImageOut, const Image& highContrastImageIn, const Image& binaryImageIn)
		{
			// Ensure that everything is white to start off with
			binaryImageOut.Fill(Palette::White);

			// Iterate every pixel of our high contrast image
			for (int idx = 0; idx < highContrastImageIn.size; ++idx)
			{
				// Detect a high contrast region that contains a forground pixel
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
		/// Spider is a fairly crafty algorithm that tracks down all connected forground pixels given a 
		/// starting point.  It does this non-recursively by searching a 3x3 area around the target pixel.
		/// 
		/// This takes advantage of the fact that many Niblack based binarization algorithms create a
		/// small background buffer around the forground that is free from noise.
		/// </summary>
		/// <param name="binaryImageOut">Image containing the traced forground.</param>
		/// <param name="binaryImageIn">Image containing the forground to trace.</param>
		/// <param name="startIdx">A forground pixel location to start the trace.</param>
		void Spider(Image& binaryImageOut, const Image& binaryImageIn, const int startIdx)
		{
			std::unordered_set<int> pixelPositions = { startIdx };

			// Initialize our Start Index
			binaryImageOut.data[startIdx] = Palette::Black;

			// If we find an attached cell that hasn't been analyzed, mark it and add it to our list
			auto processCell = [&](const int position)
			{
				if (Palette::Black == binaryImageIn.data[position] &&
					Palette::White == binaryImageOut.data[position])
				{
					binaryImageOut.data[position] = Palette::Black;
					pixelPositions.insert(position);
				}
			};

			// Process a Row of our 3x3 window from Left to Right
			auto processRow = [&](int position, const bool checkLeft, const bool checkCenter, bool const checkRight) 
			{
				// Start on the Left
				if (checkLeft)
					processCell(position);

				// Move to Center
				++position;
				if (checkCenter)
					processCell(position);

				// Move to Right
				if (checkRight)
					processCell(++position); // Note: Position is incremented
			};

			// Iterate through all of the black pixels, forming a 3x3 search window.
			// This loop may keep adding to that list when a black neighbor is found.
			while (!pixelPositions.empty())
			{
				// Pop target position index
				const int idx = *pixelPositions.begin();
				pixelPositions.erase(pixelPositions.begin());

				// Build Coordinates and detect if we are on the far left or right
				const int top = idx - binaryImageIn.width;
				const int bottom = idx + binaryImageIn.width;
				const bool checkLeft = idx % binaryImageIn.width;
				const bool checkRight = (idx + 1) % binaryImageIn.width;;

				// Process Top Row
				if (top > 0)
					processRow(top - 1, checkLeft, true, checkRight);

				// Process Center Row
				processRow(idx - 1, checkLeft, false, checkRight);

				// Process Bottom Row
				if (bottom < binaryImageIn.size)
					processRow(bottom - 1, checkLeft, true, checkRight);
			}
		}
	};

	/// <summary>
	/// A convenience name for backwards compatibility with this library.
	/// </summary>
	typedef Improved<Sauvola> ISauvola;
}


#endif //ISAUVOLA_HPP
