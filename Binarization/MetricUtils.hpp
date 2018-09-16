// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef METRICUTILS_HPP
#define METRICUTILS_HPP

#include <chrono>
#include <functional>
#include <vector>
#include "Types.hpp"
#include "Performance.hpp"
#include "DRDMPerformance.hpp"


namespace Binarization
{
	class MetricUtils
	{
	public:
		struct Score
		{
			// Identifiers
			std::string ID;
			int windowSize = 0;
			double k = 0;

			// Performance Measures
			double accuracy = 0.0;
			double fmeasure = 0.0;
			double psnr = 0.0;
			double drdm = 0.0;
			double time = 0.0;

			// Performance Metric
			double score = 0.0;
		};

		typedef std::vector<MetricUtils::Score> Scores;

		static double Time(std::function<void()> predicate)
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

			predicate();

			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			return time_span.count(); // In Seconds
		}

		/// <summary>
		/// Obtains performance stats for a specific binaraization algorithm, using ever window size and k value permutation possible.
		/// Window Sizes are incremented by 1, while K-Values are incremented by 0.01.
		/// Note that time is also being recorded.  Multithreading or other computer operations could affect that value.
		/// </summary>
		/// <param name="predicate">The binarization algorithm you want to analyze.</param>
		static void DeathBy1000PaperCuts(
			Scores& scores,
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

			Image image(grayScaleImage.width, grayScaleImage.height);

			for (int ws = windowSizeStart; ws <= windowSizeStop; ++ws)
			{
				for (double k = kStart; k <= kStopCorrection; k += 0.01)
				{
					Score score;
					score.windowSize = ws;
					score.k = k;

					score.time = MetricUtils::Time([&]() {
						predicate(image, grayScaleImage, ws, k);
					});

					Performance::Classifications classifications;
					Performance::CompareImages(classifications, groundTruthImage, image);

					score.accuracy = Performance::CalculateAccuracy(classifications);
					score.fmeasure = Performance::CalculateFMeasure(classifications);
					score.psnr = Performance::CalculatePSNR(classifications);
					score.drdm = DRDMPerformance::CalculateDRDM(groundTruthImage, image);

					scores.push_back(score);
				}
			}
		}

		static bool rankAccuracy(const Score& lhs, const Score& rhs) { return lhs.accuracy > rhs.accuracy; }
		static bool rankFMeasure(const Score& lhs, const Score& rhs) { return lhs.fmeasure > rhs.fmeasure; }
		static bool rankPSNR(const Score& lhs, const Score& rhs) { return lhs.psnr > rhs.psnr; }
		static bool rankDRDM(const Score& lhs, const Score& rhs) { return lhs.drdm < rhs.drdm; }
		static bool rankTime(const Score& lhs, const Score& rhs) { return lhs.time < rhs.time; }
		static void CalculateMeasureRank(Scores& scores, std::function<bool(const Score& lhs, const Score& rhs)> predicate)
		{
			int rank = 1;

			std::sort(scores.begin(), scores.end(), predicate);

			scores[0].score += rank;

			const int size = scores.size();
			for (int index = 1; index < size; ++index)
			{
				// Allow for ties
				if (predicate(scores[index - 1], scores[index]))
				{
					++rank;
				}

				scores[index].score += rank;
			}
		}

		/// <summary>
		/// Generates ranking metrics using all alloted performance measures except for time.
		/// The scores will be sorted and the lowest score is the winner.  There can be ties.
		/// </summary>
		static void CalculateTopRank(Scores& scores)
		{
			// Reset
			for (auto& score : scores)  score.score = 0;

			// The score will accumlate as it is judged by more Measures
			CalculateMeasureRank(scores, rankAccuracy);
			CalculateMeasureRank(scores, rankFMeasure);
			CalculateMeasureRank(scores, rankPSNR);
			CalculateMeasureRank(scores, rankDRDM);

			// This exposes the limitations of using a ranking system.
			// The #1 Rank may not actually have the best numbers holistically.
			std::sort(scores.begin(), scores.end(), [](const Score& lhs, const Score& rhs) { 
				return lhs.score < rhs.score; 
			});
		}
	};
}


#endif // METRICUTILS_HPP
