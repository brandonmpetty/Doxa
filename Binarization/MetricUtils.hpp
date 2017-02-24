/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef METRICUTILS_HPP
#define METRICUTILS_HPP

#include <chrono>
#include <functional>
#include "Types.hpp"
#include "Performance.hpp"


namespace Binarization
{
	class MetricUtils
	{
	public:
		struct Score
		{
			double total = 0.0;
			double accuracy = 0.0;
			double fmeasure = 0.0;
			double psnr = 0.0;

			int windowSize = 0;
			double k = 0.0;
		};

		static double Time(std::function<void()> predicate)
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

			predicate();

			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			return time_span.count(); // In Seconds
		}

		static Score Accuracy(
			const Image& groundTruthImage,
			const Image& grayScaleImage,
			const int windowSizeStart,
			const int windowSizeStop,
			const double kStart,
			const double kStop,
			std::function<void(Image&, const Image&, const int, const double)> predicate)
		{
			// Computers cannot correctly store double data, and incrementing it in a loop makes it worse.
			// Adding a relatively high number here so as to not miss out on a potential K value.
			const double kStopCorrection = kStop + 0.001;

			Score score;

			for (int ws = windowSizeStart; ws <= windowSizeStop; ++ws)
			{
				for (double k = kStart; k <= kStopCorrection; k += 0.01)
				{
					Image image(grayScaleImage.width, grayScaleImage.height);

					predicate(image, grayScaleImage, ws, k);

					Performance::Classifications classifications;
					Performance::CompareImages(classifications, groundTruthImage, image);

					double scoreAccuracy = Performance::CalculateAccuracy(classifications);
					double scoreFM = Performance::CalculateFMeasure(classifications);
					double scorePSNR = Performance::CalculatePSNR(classifications);

					double scoreTotal = (scoreAccuracy + scoreFM + scorePSNR) / 3;

					if (scoreTotal > score.total)
					{
						score.accuracy = scoreAccuracy;
						score.fmeasure = scoreFM;
						score.psnr = scorePSNR;
						score.total = scoreTotal;
						score.k = k;
						score.windowSize = ws;
					}
				}
			}

			return score;
		}
	};
}


#endif // METRICUTILS_HPP
