#include "pch.h"
#include "TestUtilities.hpp"
#include "PseudoWeights.hpp"
#include "ClassifiedPerformance.hpp"
#include "DIBCOUtils.hpp"
#include "ImageFixture.hpp"

#include <algorithm>
#include <cmath>
#include <vector>
#include <string>


namespace Doxa::UnitTests
{
	// PseudoWeights generates the pseudo-Recall weight map GW (Eq. 2) and the
	// pseudo-Precision weight map PW (Eq. 10) of Ntirogiannis, Gatos & Pratikakis,
	// IEEE TIP 22(2), 2013.  The committed *_RWeights.dat / *_PWeights.dat are the
	// DIBCO reference weight files; a bit-exact implementation reproduces them up to
	// the .dat's 6-decimal rounding (|diff| < 5e-7).  gw == RWeights.dat; pw is the
	// stored precision weight (PW - 1) == PWeights.dat.
	class PseudoWeightsTests : public ImageFixture {};

	// max |weights - reference| over the map.
	static double MaxAbsDiff(const std::vector<double>& weights, const std::vector<double>& ref)
	{
		double maxAbs = 0.0;
		const size_t n = std::min(weights.size(), ref.size());
		for (size_t i = 0; i < n; ++i) maxAbs = std::max(maxAbs, std::fabs(weights[i] - ref[i]));
		return maxAbs;
	}

	// Pixels whose weight differs from the reference by more than 1e-5 (i.e. a
	// genuine value difference, not .dat rounding).
	static int CountDiffs(const std::vector<double>& weights, const std::vector<double>& ref)
	{
		int count = 0;
		const size_t n = std::min(weights.size(), ref.size());
		for (size_t i = 0; i < n; ++i) if (std::fabs(weights[i] - ref[i]) > 1e-5) ++count;
		return count;
	}

	// --- Bit-exact reproduction of the DIBCO reference weight files ---------------

	// The full 2John page reproduces the reference bit-exactly -- skeleton, contour,
	// distance map, medial normalisation all computed from scratch, no injected inputs.
	TEST_F(PseudoWeightsTests, RecallWeights2JohnBitExact)
	{
		Image groundTruth = PNM::Read(projFolder + "2JohnC1V3-GroundTruth.pbm");

		std::vector<double> gw;
		PseudoWeights::RecallWeights(gw, groundTruth);

		const auto reference = DIBCOUtils::ReadWeightsFile(projFolder + "2JohnC1V3-GroundTruth_RWeights.dat");
		ASSERT_EQ(gw.size(), reference.size());

		EXPECT_LT(MaxAbsDiff(gw, reference), 1e-5);
		EXPECT_EQ(CountDiffs(gw, reference), 0);
	}

	// The full 2John page: the background distance, the inverted-image normalisation
	// and the two-pass precision denominator all computed from scratch on the
	// inverted image, no injected inputs.
	TEST_F(PseudoWeightsTests, PrecisionWeights2JohnBitExact)
	{
		Image groundTruth = PNM::Read(projFolder + "2JohnC1V3-GroundTruth.pbm");

		std::vector<double> pw;
		PseudoWeights::PrecisionWeights(pw, groundTruth);

		const auto reference = DIBCOUtils::ReadWeightsFile(projFolder + "2JohnC1V3-GroundTruth_PWeights.dat");
		ASSERT_EQ(pw.size(), reference.size());

		EXPECT_LT(MaxAbsDiff(pw, reference), 1e-5);
		EXPECT_EQ(CountDiffs(pw, reference), 0);
	}

	// --- End-to-end pseudo-metric pipeline ---------------------------------------

	// The generated weights drive the real ClassifiedPerformance pseudo-metric path
	// (CompareImages + the Pseudo* reductions), evaluating a Sauvola binarization
	// against the ground truth.  Expected values match the Python/MATLAB binding tests.
	TEST_F(PseudoWeightsTests, PseudoMetrics2John)
	{
		// Ground truth: ink is black, the default foreground.
		Image groundTruth = PNM::Read(projFolder + "2JohnC1V3-GroundTruth.pbm");

		// GW(x,y) for pseudo-Recall, PW(x,y) - 1 for pseudo-Precision -- exactly the
		// weights ClassifiedPerformance consumes (CalculatePseudoPrecision /
		// PseudoFMeasure add the raw pixel count back to reconstitute PW).
		std::vector<double> gw, pw;
		PseudoWeights::Generate(gw, pw, groundTruth);

		// The binarization output under evaluation.
		Image binary = PNM::Read(projFolder + "2JohnC1V3-Sauvola.pbm");

		// Weighted comparison: control = ground truth, experiment = binary.
		ClassifiedPerformance::Classifications classifications;
		ASSERT_TRUE(ClassifiedPerformance::CompareImages(
			classifications, groundTruth, binary, pw, gw));

		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoFMeasure(classifications),  93.393,  0.01);
		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoRecall(classifications),    92.7954, 0.01);
		EXPECT_NEAR(ClassifiedPerformance::CalculatePseudoPrecision(classifications), 93.9983, 0.01);
	}
}
