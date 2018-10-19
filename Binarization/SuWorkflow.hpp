// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef SUWORKFLOW_HPP
#define SUWORKFLOW_HPP

#include "Types.hpp"
#include "Algorithms.hpp"
#include "Palette.hpp"
#include "Region.hpp"

////////////////////////////////////////////////////////////////////////
// This code is highly experimental and has not been unit tested yet! //
////////////////////////////////////////////////////////////////////////

namespace Binarization
{
	/// <summary>
	/// The Su binarization workflow.
	/// This is a 3 step workflow consisting of Contrast Image generation, Otsu binarization, and a local thresholding algorithm.
	/// </summary>
	/// <remarks>"Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.</remarks>
	class SuWorkflow
	{
	public:

		template<typename Calculator>
		void ToBinary(Image& binaryImageOut, const Image& grayScaleImageIn) const
		{
			// Step 1 - Contrast Image Construction
			Image contrastImage(grayScaleImageIn.width, grayScaleImageIn.height);
			GenerateContrastImage(contrastImage, grayScaleImageIn);

			// Step 2 - High Contrast Pixel Detection
			Otsu(contrastImage, contrastImage);

			// Step 3 - Historical Document Thresholding
			Threshold<Calculator>(binaryImageOut, contrastImage, grayScaleImageIn);
		}

		// TODO: Read article: A fast algorithm for local minimum and maximum filters on rectangular and octagonal kernels
		void GenerateContrastImage(Image& contrastImageOut, const Image& grayScaleImageIn) const
		{
			const int windowSize = 3;
			LocalWindow::Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {

				int min = 255;
				int max = 0;

				// Build a window around our target pixel and calculate the local min and max
				for (int ix = window.upperLeft.x; ix < window.bottomRight.x; ++ix)
				{
					for (int iy = window.upperLeft.y; iy < window.bottomRight.y; ++iy)
					{
						const int value = grayScaleImageIn.Pixel(ix, iy);
						if (value < min)
						{
							min = value;
						}

						if (value > max)
						{
							max = value;
						}
					}
				}

				// The paper says to add E, a "positive but infinitely small number" incase the denominator is 0.
				// This effectively makes the number very larger, yet our max is 255.
				contrastImageOut.data[position] = (max + min > 0) ? (max - min) / (max + min) : 255;
			});
		}

		// Look at: A C++ Implementation of Otsu’s Image Segmentation Method
		void Otsu(Imag8e& binaryImageOut, const Image& grayScaleImageIn) const
		{
		}

		template<Calculator>
		void Threshold(Image& binaryImageOut, const Image& contrastImageOut, const Image& grayScaleImageIn) const
		{
			const int windowSize = 3; // Paper doesn't really say
			double mean, stddev;

			Calculator calculator;
			calculator.initialize(grayScaleImageIn);

			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window) {
				calculator.CalculateMeanStdDev(mean, stddev, window);

				//TODO - Also depends on Ne and Nmin
				// Ne - Refers to the number of high contrast image pixels that lie within the local neighborhood window
				// Nmin - Refers to the minimum value in that window?

				return mean + (stddev / 2);
			});
		}
	};
}


#endif //SUWORKFLOW_HPP
