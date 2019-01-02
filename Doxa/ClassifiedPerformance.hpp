// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef CLASSIFIEDPERFORMANCE_HPP
#define CLASSIFIEDPERFORMANCE_HPP

#include "Image.hpp"
#include "Palette.hpp"


namespace Doxa
{
	/// <summary>
	/// A performance calculator for the family of classification metrics.
	/// Implemenations: Accuracy, F-Measure, PSNR, and NMR
	/// </summary>
	class ClassifiedPerformance
	{
	public:
		struct Classifications
		{
			int truePositive = 0;	// A correctly chosen black pixel
			int trueNegative = 0;	// A correctly chosen white pixel
			int falsePositive = 0;	// An incorrectly chosen black pixel
			int falseNegative = 0;	// An incorrectly chosen white pixel

			int Total() const
			{
				return truePositive + trueNegative + falsePositive + falseNegative;
			}

			void Clear()
			{
				truePositive = trueNegative = falsePositive = falseNegative = 0;
			}
		};

		static bool CompareImages(Classifications& classifications, const Image& controlImage, const Image& expirementImage)
		{
			// Initialize
			classifications.Clear();

			// Verify Input
			if (controlImage.width != expirementImage.width || controlImage.height != expirementImage.height)
				return false;

			// Analyze
			for (int i = 0; i < controlImage.size; ++i)
			{
				if (controlImage.data[i] == expirementImage.data[i])
					if (expirementImage.data[i] == Palette::Black)
						classifications.truePositive++;
					else
						classifications.trueNegative++;
				else // Not a match
					if (expirementImage.data[i] == Palette::Black)
						classifications.falsePositive++;
					else
						classifications.falseNegative++;
			}

			return true;
		}

		static double CalculateAccuracy(const Classifications& classifications)
		{
			return ((double)(classifications.truePositive + classifications.trueNegative) / classifications.Total()) * 100;
		}

		static double CalculateFMeasure(const Classifications& classifications)
		{
			const double recall = (double)classifications.truePositive / (classifications.truePositive + classifications.falseNegative);
			const double precision = (double)classifications.truePositive / (classifications.truePositive + classifications.falsePositive);

			return ((2 * recall * precision) / (recall + precision)) * 100;
		}

		static double CalculatePSNR(const Classifications& classifications)
		{
			// Calculate MSE
			const double mse = (double)(classifications.falsePositive + classifications.falseNegative) / classifications.Total();

			// Calculate Peak Signal to Noise Ratio
			return 10 * log10(1 / mse);
		}

		static double CalculateNRM(const Classifications& classifications)
		{
			const double nrfn = (double)classifications.falseNegative / (classifications.falseNegative + classifications.truePositive);
			const double nrfp = (double)classifications.falsePositive / (classifications.falsePositive + classifications.trueNegative);

			// Calculate Negative Rate Metric
			return (nrfn + nrfp) / 2;
		}

		// 
		// Convenience Method
		template<typename CalcFunc>
		static double Calculate(const Image& controlImage, const Image& expirementImage, CalcFunc calcFunc)
		{
			Classifications classifications;
			return CompareImages(classifications, controlImage, expirementImage) ? calcFunc(classifications) : 0.0;
		}
	};
}


#endif //CLASSIFIEDPERFORMANCE_HPP
