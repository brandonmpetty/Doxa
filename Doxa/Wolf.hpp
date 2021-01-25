// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef WOLF_HPP
#define WOLF_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "ChanMeanVarianceCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The Wolf Algorithm: Christian Wolf, Jean-Michel Jolion
	/// </summary>
	/// <remarks>"Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.</remarks>
	class Wolf : public Algorithm<Wolf>, public ChanMeanVarianceCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			double min = std::numeric_limits<double>::max();
			double maxVariance = std::numeric_limits<double>::min();

			// Find global min value and max standard deviation value
			Iterate(Algorithm::grayScaleImageIn, windowSize, [&](const double&, const double& variance, const int& position) {
				
				if (variance > maxVariance) maxVariance = variance;

				const double tmpMin = Algorithm::grayScaleImageIn.data[position];
				if (tmpMin < min) min = tmpMin;
			});

			const double maxStdDev = std::sqrt(maxVariance);

			Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const double& mean, const double& variance, const int& position) {
				const double stddev = std::sqrt(variance);

				return mean - k * (1 - (stddev / maxStdDev)) * (mean - min);
			});
		}
	};
}


#endif //WOLF_HPP
