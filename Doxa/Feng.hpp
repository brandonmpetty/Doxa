// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef FENG_HPP
#define FENG_HPP

#include <vector>
#include <cmath>
#include "Algorithm.hpp"
#include "GridCalc.hpp"


namespace Doxa
{
	/// <summary>
	/// The Feng Algorithm: Meng-Ling Feng, Yap-Peng Tan
	///
	/// A local-adaptive thresholding method built around maximizing local
	/// contrast.  Each pixel's threshold is computed as:
	///
	///   T = (1 - alpha1)*m + alpha2*(s/Rs)*(m - M) + alpha3*M
	///   alpha2 = k1 * (s/Rs)^gamma
	///   alpha3 = k2 * (s/Rs)^gamma
	///
	/// where m, s, M are the mean, standard deviation and minimum over a
	/// primary window centered on each grid point.  Rs is the local
	/// generalization of Christian's R: the maximum of the standard
	/// deviations s over a larger secondary window centered on the same
	/// point.  The formula relies on s/Rs being a normalized contrast
	/// indicator in [0, 1] -- "1" in the busiest text region, "0" in flat
	/// background -- so Rs >= s by construction.
	///
	/// Per the paper, thresholds are computed at the center of every
	/// primary window (a grid) and bilinearly interpolated for the
	/// remaining pixels -- the same pattern AdOtsu uses through GridCalc.
	///
	/// Two grid passes are required: phase one collects (m, s, M) per grid
	/// point, phase two reads neighboring s values to compute Rs.  The
	/// per-grid storage is small (a few thousand entries for typical
	/// document sizes) so it's separately allocated by statistic (SoA) --
	/// the inner loop in phase two reads only s, so packing it tightly
	/// keeps the access pattern cache-friendly.
	///
	/// Defaults follow the paper's empirical guidance:
	///   alpha1 in [0.1, 0.2], k1 in [0.01, 0.05], k2 in [0.15, 0.25], gamma = 2.
	/// </summary>
	/// <remarks>"Adaptive Binarization Method for Document Image Analysis", 2004.</remarks>
	class Feng : public Algorithm<Feng>, public GridCalc
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const Image& gray = Algorithm::grayScaleImageIn;

			// Read parameters, utilizing defaults
			// The primary window should be 1 to 2 times the character size
			const int primaryWindow   = parameters.Get("window", 25);

			// The paper doesn't pin a size; Fig. 1 visually shows roughly 3x the primary.
			const int secondaryWindow = parameters.Get("secondary-window", primaryWindow * 3);

			const int dist            = std::max(1, parameters.Get("distance", primaryWindow / 2));
			const double alpha1       = parameters.Get("alpha1", 0.12);
			const double k1           = parameters.Get("k1", 0.025);
			const double k2           = parameters.Get("k2", 0.2);
			const double gamma        = parameters.Get("gamma", 2.0);

			// Lower bound on Rs.  Feng's formula assumes the secondary window
			// always contains some text-bearing region whose s dominates the
			// local std-dev.  When it doesn't (wide image margins), s/Rs ~ 1
			// and the formula yanks T past 255, blackening the margin.  A
			// floor of ~10 distinguishes "real signal" from "camera noise".
			// Set to 0 for paper-faithful behavior on clean / pre-filtered
			// inputs; internally clamped to a tiny positive value so the
			// inner-loop s/Rs division is always safe.
			///
			// NOTE: Somewhat bypasses the need for the paper's recommendation of a median filter!
			// With the right sized primary window, black splotches in white areas go away.
			// However, this lets you use a much smaller window (1/3 the size) and get great results!
			const double noiseFloor   = std::max(parameters.Get("noise-floor", 10.0), 1e-9);

			// Grid dimensions match GridCalc::Iterate's stride logic
			const int gridW = static_cast<int>(std::ceil(static_cast<float>(gray.width  - 1) / dist)) + 1;
			const int gridH = static_cast<int>(std::ceil(static_cast<float>(gray.height - 1) / dist)) + 1;
			const int gridSize = gridW * gridH;

			// Store mean (m), standard deviation (s), and minimum (M) values
			std::vector<double> grid_m(gridSize);
			std::vector<double> grid_s(gridSize);
			std::vector<double> grid_M(gridSize);

			// Phase 1: walk the grid, compute (m, s, M) per grid point.
			int idx = 0;
			Iterate(gray, primaryWindow, dist, [&](const Region& window, const int&)
			{
				long sum = 0;
				long sumSq = 0;
				int minVal = 255;
				int count = 0;

				for (int yy = window.upperLeft.y; yy <= window.bottomRight.y; ++yy)
				{
					const int row = yy * gray.width;
					for (int xx = window.upperLeft.x; xx <= window.bottomRight.x; ++xx)
					{
						const int p = gray.data[row + xx];

						sum += p;
						sumSq += static_cast<long>(p) * p;
						if (p < minVal) minVal = p;

						++count;
					}
				}

				const double mean = static_cast<double>(sum) / count;
				const double variance = static_cast<double>(sumSq) / count - mean * mean;
				
				grid_m[idx] = mean;
				grid_s[idx] = std::sqrt(variance > 0.0 ? variance : 0.0);
				grid_M[idx] = static_cast<double>(minVal);

				++idx;
			});

			// Phase 2: write the per-grid-point threshold at the grid center pixel.
			// Rs is max(s) over a secondary window centered on the grid point; in
			// grid coordinates its half-extent is ceil(secondaryWindow / (2*dist)).
			const int secondaryRadius = std::max(1, (secondaryWindow + 2 * dist - 1) / (2 * dist));

			int gx = 0, gy = 0;
			Iterate(gray, primaryWindow, dist, [&](const Region&, const int& position)
			{
				const int gIdx = gy * gridW + gx;

				const int gx0 = std::max(0, gx - secondaryRadius);
				const int gx1 = std::min(gridW - 1, gx + secondaryRadius);
				const int gy0 = std::max(0, gy - secondaryRadius);
				const int gy1 = std::min(gridH - 1, gy + secondaryRadius);

				// Rs = max of s over neighboring grid points
				double Rs = 0.0;
				for (int yy = gy0; yy <= gy1; ++yy)
				{
					const int rowOffset = yy * gridW;

					for (int xx = gx0; xx <= gx1; ++xx)
					{
						const double ss = grid_s[rowOffset + xx];
						if (ss > Rs) Rs = ss;
					}
				}

				// Clamp Rs from below to disqualify noise-only neighborhoods.
				// noiseFloor is guaranteed positive, so Rs is now > 0 and the
				// division below is always safe.
				if (Rs < noiseFloor) Rs = noiseFloor;

				// Feng's threshold formula
				const double m = grid_m[gIdx];
				const double s = grid_s[gIdx];
				const double M = grid_M[gIdx];

				const double sRatio = s / Rs;
				const double sRatioGamma = std::pow(sRatio, gamma);
				const double alpha2 = k1 * sRatioGamma;
				const double alpha3 = k2 * sRatioGamma;

				double T = (1.0 - alpha1) * m + alpha2 * sRatio * (m - M) + alpha3 * M;
				if (T < 0.0) T = 0.0;
				else if (T > 255.0) T = 255.0;

				binaryImageOut.data[position] = static_cast<Pixel8>(T + 0.5);

				// Advance grid coords for next call (Iterate is row-major).
				if (++gx >= gridW) { gx = 0; ++gy; }
			});

			// Phase 3: bilinearly interpolate the threshold for every non-grid
			// pixel and apply it on the spot -- this is the only full-image
			// pass through the data.
			Interpolate(binaryImageOut, dist, [&](const int& position, const int& threshold)
			{
				binaryImageOut.data[position] =
					(gray.data[position] <= threshold) ? Palette::Black : Palette::White;
			});

			// Phase 4: apply thresholds at the grid centers themselves.  Sparse
			// (only `gridW * gridH` pixels), so it doesn't add a full pass.
			Iterate(gray, primaryWindow, dist, [&](const Region&, const int& position)
			{
				binaryImageOut.data[position] =
					(gray.data[position] <= binaryImageOut.data[position]) ? Palette::Black : Palette::White;
			});
		}
	};
}


#endif //FENG_HPP
