// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef CLASSIFIEDPERFORMANCE_HPP
#define CLASSIFIEDPERFORMANCE_HPP

#include <vector>
#include "Image.hpp"
#include "Palette.hpp"
#include "SIMDOps.hpp"


namespace Doxa
{
	/// <summary>
	/// A performance calculator for the family of classification metrics.
	/// Implemenations: Accuracy, (pseudo)Recall, (pseudo)Precision, (pseudo)F-Measure, PSNR, MCC and NMR
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

			double wpTruePositive = 0.0;	// Weighted Precision
			double wpFalsePositive = 0.0;	// Weighted Precision
			double wrTruePositive = 0.0;	// Weighted Recall
			double wrFalseNegative = 0.0;	// Weighted Recall

			int Total() const noexcept
			{
				return truePositive + trueNegative + falsePositive + falseNegative;
			}

			void Clear() noexcept
			{
				truePositive = trueNegative = falsePositive = falseNegative = 0;
				wpTruePositive = wpFalsePositive = wrTruePositive = wrFalseNegative = 0.0;
			}
		};

		static bool CompareImages(
			Classifications& classifications, 
			const Image& controlImage, 
			const Image& expirementImage)
		{
			// Initialize
			classifications.Clear();

			// Verify Input
			if (controlImage.width != expirementImage.width || controlImage.height != expirementImage.height)
				return false;

			#if defined(DOXA_SIMD)
				CompareImages_SIMD(classifications, controlImage.data, expirementImage.data, controlImage.size);
			#else
				CompareImages_STD(classifications, controlImage.data, expirementImage.data, controlImage.size);
			#endif

			return true;
		}

		/// <summary>
		/// Scalar implementation of image comparison - always available
		/// </summary>
		static void CompareImages_STD(Classifications& classifications, const Pixel8* control, const Pixel8* experiment, int size)
		{
			for (int i = 0; i < size; ++i)
			{
				if (control[i] == experiment[i])
					if (experiment[i] == Palette::Black)
						classifications.truePositive++;
					else
						classifications.trueNegative++;
				else // Not a match
					if (experiment[i] == Palette::Black)
						classifications.falsePositive++;
					else
						classifications.falseNegative++;
			}
		}

#if defined(DOXA_SIMD)
		/// <summary>
		/// SIMD implementation of image comparison - only available when SIMD is enabled
		/// </summary>
		static void CompareImages_SIMD(Classifications& classifications, const Pixel8* control, const Pixel8* experiment, int size)
		{
			using namespace SIMD;

			int idx = 0;
			const int simd_end = size - (size % SIMD_WIDTH);

			vec128 black_vec = VEC_SPLAT_U8(Palette::Black);
			vec128 ones_vec = VEC_SPLAT_U8(1);

			// Accumulators for SIMD counts
			int tp_sum = 0, tn_sum = 0, fp_sum = 0, fn_sum = 0;

			for (; idx < simd_end; idx += SIMD_WIDTH) {
				vec128 ctrl = VEC_LOAD(control + idx);
				vec128 exp = VEC_LOAD(experiment + idx);

				// match_mask: 0xFF where control == experiment, 0x00 otherwise
				vec128 match_mask = VEC_CMPEQ_U8(ctrl, exp);
				// black_mask: 0xFF where experiment == black, 0x00 otherwise
				vec128 black_mask = VEC_CMPEQ_U8(exp, black_vec);

				// TP: match AND black
				vec128 tp_mask = VEC_AND(match_mask, black_mask);
				// TN: match AND NOT black
				vec128 tn_mask = VEC_ANDNOT(black_mask, match_mask);
				// FP: NOT match AND black
				vec128 fp_mask = VEC_ANDNOT(match_mask, black_mask);
				// FN: NOT match AND NOT black
				vec128 not_match = VEC_NOT(match_mask);
				vec128 not_black = VEC_NOT(black_mask);
				vec128 fn_mask = VEC_AND(not_match, not_black);

				// Count set bytes (mask has 0xFF for set, we need count of 1s)
				// AND with 1s to convert 0xFF to 0x01, then horizontal sum
				tp_sum += vec_hsum_u8(VEC_AND(tp_mask, ones_vec));
				tn_sum += vec_hsum_u8(VEC_AND(tn_mask, ones_vec));
				fp_sum += vec_hsum_u8(VEC_AND(fp_mask, ones_vec));
				fn_sum += vec_hsum_u8(VEC_AND(fn_mask, ones_vec));
			}

			classifications.truePositive = tp_sum;
			classifications.trueNegative = tn_sum;
			classifications.falsePositive = fp_sum;
			classifications.falseNegative = fn_sum;

			// Handle remaining pixels with scalar
			for (; idx < size; ++idx) {
				if (control[idx] == experiment[idx])
					if (experiment[idx] == Palette::Black)
						classifications.truePositive++;
					else
						classifications.trueNegative++;
				else
					if (experiment[idx] == Palette::Black)
						classifications.falsePositive++;
					else
						classifications.falseNegative++;
			}
		}
#endif // DOXA_SIMD

		static bool CompareImages(
			ClassifiedPerformance::Classifications& classifications, 
			const Image& controlImage, 
			const Image& expirementImage, 
			const std::vector<double>& weightsPrecision, 
			const std::vector<double>& weightsRecall)
		{
			// Initialize
			classifications.Clear();

			// Verify Input
			if (controlImage.width != expirementImage.width || controlImage.height != expirementImage.height)
				return false;

			// Ensure that weights are properly passed
			if (!weightsPrecision.size() || !weightsRecall.size())
				return CompareImages(classifications, controlImage, expirementImage);

			// Analyze using Pseudo Weights
			for (int i = 0; i < controlImage.size; ++i)
			{
				if (controlImage.data[i] == expirementImage.data[i])
				{
					if (expirementImage.data[i] == Palette::Black)
					{
						classifications.truePositive++;
						classifications.wpTruePositive += weightsPrecision[i];
						classifications.wrTruePositive += weightsRecall[i];
					}
					else
					{
						classifications.trueNegative++;
					}
				}
				else // Not a match
				{
					if (expirementImage.data[i] == Palette::Black)
					{
						classifications.falsePositive++;
						classifications.wpFalsePositive += weightsPrecision[i];
					}
					else
					{
						classifications.falseNegative++;
						classifications.wrFalseNegative += weightsRecall[i];
					}
				}
			}

			return true;
		}

		static double CalculateAccuracy(const Classifications& classifications)
		{
			return (((double)classifications.truePositive + classifications.trueNegative) / classifications.Total()) * 100;
		}

		static double CalculateRecall(const Classifications& classifications)
		{
			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (classifications.truePositive == 0) return 0.0;

			const double recall = (double)classifications.truePositive / (classifications.truePositive + classifications.falseNegative);

			return recall * 100;
		}

		static double CalculatePrecision(const Classifications& classifications)
		{
			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (classifications.truePositive == 0) return 0.0;

			const double precision = (double)classifications.truePositive / (classifications.truePositive + classifications.falsePositive);

			return precision * 100;
		}

		static double CalculateFMeasure(const Classifications& classifications)
		{
			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (classifications.truePositive == 0) return 0.0;

			const double recall = (double)classifications.truePositive / (classifications.truePositive + classifications.falseNegative);
			const double precision = (double)classifications.truePositive / (classifications.truePositive + classifications.falsePositive);

			return ((2 * recall * precision) / (recall + precision)) * 100;
		}

		static double CalculatePseudoRecall(const Classifications& classifications)
		{
			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (classifications.wrTruePositive == 0) return 0.0;

			const double pseudoRecall = classifications.wrTruePositive / (classifications.wrTruePositive + classifications.wrFalseNegative);

			return pseudoRecall * 100;
		}

		static double CalculatePseudoPrecision(const Classifications& classifications)
		{
			const double pseudoTruePositive = classifications.wpTruePositive + classifications.truePositive;
			const double pseudoFalsePositive = classifications.wpFalsePositive + classifications.falsePositive;

			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (pseudoTruePositive == 0) return 0.0;

			const double pseudoPrecision = pseudoTruePositive / (pseudoTruePositive + pseudoFalsePositive);

			return pseudoPrecision * 100;
		}

		/// <summary>
		/// Pseudo F-Measure
		/// </summary>
		/// <remarks>"Performance Evaluation Methodology for Historical Document Image Binarization", 2013.</remarks>
		static double CalculatePseudoFMeasure(const Classifications& classifications)
		{
			const double pseudoTruePositivePrecision = classifications.wpTruePositive + classifications.truePositive;
			const double pseudoFalsePositivePrecision = classifications.wpFalsePositive + classifications.falsePositive;
			const double pseudoTruePositiveRecall = classifications.wrTruePositive;
			const double pseudoFalseNegativeRecall = classifications.wrFalseNegative;

			// Prevent divide by zero.  Range is 0.0 to 1.0
			if (pseudoTruePositivePrecision == 0 || pseudoTruePositiveRecall == 0) return 0.0;

			const double pseudoPrecision = pseudoTruePositivePrecision / (pseudoTruePositivePrecision + pseudoFalsePositivePrecision);
			const double pseudoRecall = pseudoTruePositiveRecall / (pseudoTruePositiveRecall + pseudoFalseNegativeRecall);

			const double pseudoFMeasure = ((2 * pseudoRecall * pseudoPrecision) / (pseudoRecall + pseudoPrecision)) * 100;

			return pseudoFMeasure;
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
