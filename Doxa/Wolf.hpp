// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WOLF_HPP
#define WOLF_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MeanVarianceCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Wolf Algorithm: Christian Wolf, Jean-Michel Jolion
	/// </summary>
	/// <remarks>"Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.</remarks>
	class Wolf : public Algorithm<Wolf>, public MeanVarianceCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			MeanVarianceCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			double mean, stddev;
			double min = std::numeric_limits<double>::max();
			double maxStdDev = std::numeric_limits<double>::min();

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			// Find global min value and max standard deviation value
			LocalWindow::Iterate(Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				CalculateMeanStdDev(mean, stddev, window);
				if (stddev > maxStdDev) maxStdDev = stddev;

				const double tmpMin = Algorithm::grayScaleImageIn.data[position];
				if (tmpMin < min) min = tmpMin;
			});

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {
				CalculateMeanStdDev(mean, stddev, window);

				return mean - k * (1 - (stddev / maxStdDev)) * (mean - min);
			});
		}
	};
}


#endif //WOLF_HPP
