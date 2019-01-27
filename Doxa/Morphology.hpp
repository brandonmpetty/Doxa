// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef MORPHOLOGY_HPP
#define MORPHOLOGY_HPP

#include <set>
#include "Image.hpp"
#include "LocalWindow.hpp"


namespace Doxa
{
	class Morphology
	{
	public:
		/// <summary>
		/// Open is simply Erode followed by Dilate.
		/// This can help reduce background noise.
		/// </summary>
		static void Open(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Image erodedImage(grayScaleImage.width, grayScaleImage.height);
			Erode(erodedImage, grayScaleImage, windowSize);
			Dilate(morphedImage, erodedImage, windowSize);
		}

		/// <summary>
		/// Close is simply Dilate followed by Erode.
		/// This can help fill holes in the forground.
		/// </summary>
		static void Close(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Image dilatedImage(grayScaleImage.width, grayScaleImage.height);
			Dilate(dilatedImage, grayScaleImage, windowSize);
			Erode(morphedImage, dilatedImage, windowSize);
		}

		/// <summary>
		/// Iterates through the gray scale image, recording the minimum value within the window.
		/// </summary>
		static void Erode(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			// For small window sizes, manually analyzing the window is faster.
			if (windowSize < 17)
			{
				IterativelyErode(morphedImage, grayScaleImage, windowSize);
			}
			else
			{
				Morph(morphedImage, grayScaleImage, windowSize, [](const std::multiset<Pixel8>& set) {
					return *set.begin(); // Min Value
				});
			}
		}

		/// <summary>
		/// Iterates through the grayscale image, recording the maximum value within the window.
		/// </summary>
		static void Dilate(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			// For small window sizes, manually analyzing the window is faster.
			if (windowSize < 17)
			{
				IterativelyDilate(morphedImage, grayScaleImage, windowSize);
			}
			else
			{
				Morph(morphedImage, grayScaleImage, windowSize, [](const std::multiset<Pixel8>& set) {
					return *std::prev(set.end()); // Max Value
				});
			}
		}

	protected:
		/// <summary>
		/// Author: Brandon M. Petty
		/// Date: Jan 19, 2019
		/// 
		/// This routine allows one to Erode or Dilate a grayscale image efficiently for medium to large window sizes.
		/// Many binarization algorithms require the min/max value within a local window.  Iterating through each window
		/// can be extremely slow with larger window sizes.  The goal of this algorithm is to greatly improve the
		/// performance characteristics for varying window sizes.
		/// 
		/// This algorithm was born out of necessity because I could not, for the life of me, understand vHGW.
		/// The vHGW algorithm, as referenced in many papers, can apparently do this very efficiently.
		/// But like most papers I've read, something supposedly so simple is completely undermined by an overly complex
		/// description with absolutely no example of how it works with real data.
		/// 
		/// Algorithm:
		/// 1. For each row, iterate pixel by pixel to the end of the row, creating a 1-D horizontal window around each pixel.
		/// 2. For each window, take the min value (for Erode), or max value (for Dilate), and store it in a temp image
		///    at the same coordinates as the targeted pixel.
		/// 3. Using the temp image, repeat steps 1 and 2 except now you will be going down column by column using a 1-D
		///    vertical window to capture min / max values for your final morphed image.
		/// 
		/// The algorithm's performance hinges on its ability to find the min/max of a given window.  By using an ordered
		/// set, when sliding the window over by one pixel, we simply need to add the next pixel to the set and remove
		/// the single pixel no longer in the window from the set.  Because the set is ordered, the first item in the
		/// set is the min value, and the last item is the max value.  In the end, it comes down to how fast you can add
		/// and remove items from an ordered set.
		/// 
		/// Anecdotal Evidence:
		/// Base on an AMD Phenom II 1090T Processor running Windows 10, compiled with MSBuild using /O2 /Ot
		/// The follow are: Window Size, Speed of Wan's algorithm using Morph, Speed of Wan simply searching each window.
		/// 3   | 0.091808 | 0.028856		* Using the Morph implementation is slower for small windows
		/// 17  | 0.127909 | 0.134349		* This is the window size which breaks in favor of Morph
		/// 25  | 0.130928 | 0.238442		* 1.8x faster
		/// 75  | 0.143578 | 1.652775		* 11.5x faster
		/// 125 | 0.146470 | 4.218453		* 28.8x faster
		/// 255 | 0.149844 | 15.32876		* 102.3x faster
		/// </summary>
		/// <remarks>If this is a known algorithm, please provide a source and I will attribute it here.</remarks>
		template<typename MorphRoutine>
		static inline void Morph(Image& morphedImage, const Image& grayScaleImage, const int& windowSize, MorphRoutine routine)
		{
			const int windowHalfWidth = ((windowSize - 1) / 2);
			const int windowHalfWidthPlusOne = windowHalfWidth + 1;

			// Store the minimum values, by row
			Image tempImage(grayScaleImage.width, grayScaleImage.height);

			// For each row (y) in grayScaleImage, calculate the min/max value within the 1-D window for that row
			for (int y = 0; y < grayScaleImage.height; ++y)
			{
				// Instead of paying the cost of calling Pixel(x,y), roll our own to save a few cpu cycles
				const int row = y * grayScaleImage.width;

				// Set is used because it automatically orders everything we add into it
				std::multiset<Pixel8> set;

				// Initialize set with first half of our 1-D window
				// This sets pixel 0,0 with the max of the half window.
				for (int w = 0; w <= windowHalfWidth; ++w)
				{
					set.insert(grayScaleImage.data[row + w]);
				}
				tempImage.data[row] = routine(set);

				// Fill it up until we hit the full width of the 1-D window
				// This allows us to set the next few pixels as we iterate to that point
				int x = 1;
				for (; x <= windowHalfWidth; ++x)
				{
					set.insert(grayScaleImage.data[row + x + windowHalfWidth]);
					tempImage.data[row + x] = routine(set);
				}

				// Now that we have a full window set, simply add the next item and remove the last time.
				// This will take use almost to the end of the row, finding the min/max value for that point within a 1-D window
				for (; x < grayScaleImage.width - windowHalfWidth; ++x)
				{
					// Optimization: Calculate position since we are calling this 3 times
					const int position = row + x;

					//set.erase(grayScaleImage.data[position - windowHalfWidthPlusOne]);
					const std::multiset<Pixel8>::iterator hit(set.find(grayScaleImage.data[position - windowHalfWidthPlusOne]));
					if (hit != set.end()) set.erase(hit);

					set.insert(grayScaleImage.data[position + windowHalfWidth]);
					tempImage.data[position] = routine(set);
				}

				// Because there is nothing left to add, simply remove items from out set until we reach the end
				// This will wrap up the calculation for the row
				for (; x < grayScaleImage.width; ++x)
				{
					//set.erase(grayScaleImage.data[row + x - windowHalfWidthPlusOne]);
					const std::multiset<Pixel8>::iterator hit(set.find(grayScaleImage.data[row + x - windowHalfWidthPlusOne]));
					if (hit != set.end()) set.erase(hit);

					tempImage.data[row + x] = routine(set);
				}
			}

			// For each column (x) in erodedImage, calculate the min/max value within the 1-D window for that column
			// After this routine, erodedImage will contain an array of all min/max values
			for (int x = 0; x < tempImage.width; ++x)
			{
				std::multiset<Pixel8> set;

				// Note: We are calling Pixel(x,y) here because we are traversing columns

				// Initialize set with first half of our 1-D window
				// This sets pixel 0,0 with the max of the half window.
				for (int w = 0; w <= windowHalfWidth; ++w)
				{
					set.insert(tempImage.Pixel(x, w));
				}
				morphedImage.Pixel(x, 0) = routine(set);

				// Fill it up until we hit the full height of the 1-D window
				// This allows us to set the next few pixels as we iterate to that point
				int y = 1;
				for (; y <= windowHalfWidth; ++y)
				{
					set.insert(tempImage.Pixel(x, windowHalfWidth + y));
					morphedImage.Pixel(x, y) = routine(set);
				}

				// Now that we have a full window set, simply add the next item and remove the last time.
				// This will take use almost to the end of the column, finding the min/max value for that point within a 1-D window
				for (; y < tempImage.height - windowHalfWidth; ++y)
				{
					//set.erase(tempImage.Pixel(x, y - windowHalfWidthPlusOne));
					const std::multiset<Pixel8>::iterator hit(set.find(tempImage.Pixel(x, y - windowHalfWidthPlusOne)));
					if (hit != set.end()) set.erase(hit);

					set.insert(tempImage.Pixel(x, y + windowHalfWidth));
					morphedImage.Pixel(x, y) = routine(set);
				}

				// Because there is nothing left to add, simply remove items from out set until we reach the end
				// This will wrap up the calculation for the column
				for (; y < tempImage.height; ++y)
				{
					//set.erase(tempImage.Pixel(x, y - windowHalfWidthPlusOne));
					const std::multiset<Pixel8>::iterator hit(set.find(tempImage.Pixel(x, y - windowHalfWidthPlusOne)));
					if (hit != set.end()) set.erase(hit);

					morphedImage.Pixel(x, y) = routine(set);
				}
			}
		}

		static inline void IterativelyErode(Image& morphedImage, const Image& grayScaleImage, const int& windowSize)
		{
			// Iterate entire image creating a window around each pixel
			LocalWindow::Iterate(grayScaleImage, windowSize, [&](const Region& window, const int& target)
			{
				int min = 255;

				// Iterate each window, finding the max value
				LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& position) {
					const int value = grayScaleImage.data[position];
					if (value < min)
					{
						min = value;
					}
				});

				morphedImage.data[target] = min;
			});
		}

		static inline void IterativelyDilate(Image& morphedImage, const Image& grayScaleImage, const int& windowSize)
		{
			// Iterate entire image creating a window around each pixel
			LocalWindow::Iterate(grayScaleImage, windowSize, [&](const Region& window, const int& target)
			{
				int max = 0;

				// Iterate each window, finding the max value
				LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& position) {
					const int value = grayScaleImage.data[position];
					if (value > max)
					{
						max = value;
					}
				});

				morphedImage.data[target] = max;
			});
		}
	};
}


#endif //MORPHOLOGY_HPP
