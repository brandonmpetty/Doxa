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
	/// Implemenations: Accuracy, F-Measure, PSNR, MCC and NMR
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

			int Total() const noexcept
			{
				return truePositive + trueNegative + falsePositive + falseNegative;
			}

			void Clear() noexcept
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
			return (((double)classifications.truePositive + classifications.trueNegative) / classifications.Total()) * 100;
		}

		static double CalculateFMeasure(const Classifications& classifications)
		{
			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (classifications.truePositive == 0) return 0.0;

			const double recall = (double)classifications.truePositive / (classifications.truePositive + classifications.falseNegative);
			const double precision = (double)classifications.truePositive / (classifications.truePositive + classifications.falsePositive);

			return ((2 * recall * precision) / (recall + precision)) * 100;
		}

		static double CalculatePSNR(const Classifications& classifications)
		{
			// Calculate MSE
			const double mse = ((double)classifications.falsePositive + classifications.falseNegative) / classifications.Total();

			// Perfect match.  Prevent divide by zero error.
			if (mse == 0) return std::numeric_limits<double>::max();

			// Calculate Peak Signal to Noise Ratio
			return 10 * log10(1 / mse);
		}

		/// <summary>
		/// Matthews Correlation Coefficient
		/// This should be more reliable than F-Measure for binary classification.  See article below.
		/// </summary>
		/// <remarks>https://en.wikipedia.org/wiki/Matthews_correlation_coefficient</remarks>
		/// <returns>A number between -1 and 1, where 0 is totally random guessing.</returns>
		static double CalculateMCC(const Classifications& classifications)
		{
			const double n = (double)classifications.truePositive * classifications.trueNegative - (double)classifications.falsePositive * classifications.falseNegative;
			const double d =
				((double)classifications.truePositive + classifications.falsePositive) *
				((double)classifications.truePositive + classifications.falseNegative) *
				((double)classifications.trueNegative + classifications.falsePositive) *
				((double)classifications.trueNegative + classifications.falseNegative);

			// If undefined, return 0 to highlight the issue.
			return d == 0 ? 0 : n / std::sqrt(d);
		}

		static double CalculateNRM(const Classifications& classifications)
		{
			const int fntp = classifications.falseNegative + classifications.truePositive;
			const int fptn = classifications.falsePositive + classifications.trueNegative;

			// Prevent divide by zero error
			if (fntp == 0 || fptn == 0) return std::numeric_limits<double>::max();

			const double nrfn = (double)classifications.falseNegative / fntp;
			const double nrfp = (double)classifications.falsePositive / fptn;

			// Calculate Negative Rate Metric
			return (nrfn + nrfp) / 2;
		}

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
