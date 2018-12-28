// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef SU_HPP
#define SU_HPP

#include "Types.hpp"
#include "Otsu.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "MinMaxCalculator.hpp"

#include "PNM.hpp"

////////////////////////////////////////////////////////////////
// This code is not working and has not been unit tested yet! //
////////////////////////////////////////////////////////////////

namespace Doxa
{
	/// <summary>
	/// The Su binarization workflow.
	/// This is a 3 step workflow consisting of Contrast Image generation, Otsu binarization, and a local thresholding algorithm.
	/// </summary>
	/// <remarks>"Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.</remarks>
	class Su : public Algorithm<Su>
	{
	public:
		void ToBinary(Image& binaryImageOut, const Parameters& parameters)
		{
			std::string projFolder = R"(C:\Users\Brandon M. Petty\Source\GitHub\Doxa\Binarization\UnitTests\Resources\)";

			// Step 1 - Contrast Image Construction
			Image contrastImage = GenerateContrastImage(Algorithm::grayScaleImageIn);

			PNM::Write(contrastImage, projFolder + "2JohnCV13-Su-Contrast.ppm");

			// Step 2 - High Contrast Pixel Detection
			Otsu::UpdateToBinary(contrastImage, parameters);

			PNM::Write(contrastImage, projFolder + "2JohnCV13-Su-OtsuContrast.ppm");

			// Step 3 - Historical Document Thresholding
			Threshold(binaryImageOut, contrastImage, Algorithm::grayScaleImageIn);
		}

	protected:
		// TODO: Read article on vHGW: A fast algorithm for local minimum and maximum filters on rectangular and octagonal kernels
		Image GenerateContrastImage(const Image& grayScaleImage) const
		{
			Image contrastImageOut(grayScaleImage.width, grayScaleImage.height);

			Pixel8 min, max;
			MinMaxCalculator minMaxCalculator;
			minMaxCalculator.Initialize(grayScaleImage);

			const int windowSize = 3;
			LocalWindow::Iterate(grayScaleImage, windowSize, [&](const Region& window, const int& position) {

				minMaxCalculator.CalculateMinMax(min, max, window);

				// The paper says to add E, a "positive but infinitely small number" incase the denominator is 0.
				// This effectively makes the number very larger, yet our max is 255.
				//contrastImageOut.data[position] = (max + min > 0) ? (max - min) / (max + min) : 255;

				const int value = (max - min) / (max + min + std::numeric_limits<double>::lowest());
				contrastImageOut.data[position] = (std::min)(255, value);
			});

			return contrastImageOut;
		}

		/// <summary>
		/// Calculates Ne, meanE, and stdE in one iteration
		/// </summary>
		void SuCalculations(int& Ne, double& meanE, double& stdE, const Image& contrastImage, const Image& grayScaleImage, const Region& window) const
		{
			int sumGrayScale = 0;
			Ne = 0;

			LocalWindow::Iterate(grayScaleImage.width, window, [&](const int& position)
			{
				if (contrastImage.data[position] == Palette::Black)
				{
					sumGrayScale += grayScaleImage.data[position];
					++Ne;
				}
			});

			meanE = (double)sumGrayScale / Ne;
			stdE = std::sqrt(((double)sumGrayScale - (Ne * meanE)) / 2);
		};

		void Threshold(Image& binaryImageOut, const Image& contrastImageIn, const Image& grayScaleImageIn, int windowSize = 3, int Nmin = 3) const
		{
			LocalWindow::Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {

				int Ne;
				double meanE, stdE;

				SuCalculations(Ne, meanE, stdE, contrastImageIn, grayScaleImageIn, window);

				binaryImageOut.data[position] =
					(Ne >= Nmin && grayScaleImageIn.data[position] <= meanE + (stdE / 2)) ?
					Palette::Black : Palette::White;
			});
		}
	};
}


#endif //SU_HPP
