// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef PSEUDOWEIGHTS_HPP
#define PSEUDOWEIGHTS_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <vector>
#include "Image.hpp"
#include "Palette.hpp"
#include "ConnectedComponents.hpp"
#include "Thinning.hpp"      // ZhangSuenThinning / detail::ApplyTablePassInPlace


namespace Doxa
{
	/// <summary>
	/// Generates the two ground-truth weight maps behind the pseudo-metrics of
	/// Ntirogiannis, Gatos & Pratikakis, "Performance Evaluation Methodology for
	/// Historical Document Image Binarization," IEEE TIP 22(2), 2013:
	///
	///   GW(x,y) - the weighted ground truth, for pseudo-Recall    (Eq. 2, 3)
	///   PW(x,y) - the background weight map,  for pseudo-Precision (Eq. 10, 11)
	///
	///   Rps = sum(B . GW) / sum(GW)         Pps = sum(G . B . PW) / sum(B . PW)
	///
	/// are then trivial reductions over these maps and the binarized image B.
	/// (RWeights.dat stores GW; PWeights.dat stores PW - 1.)  The maps produced
	/// here are bit-exact with the DIBCO reference weight files.
	///
	/// The paper weights symmetrically about the ground-truth text contour:
	/// pseudo-Recall weights the FOREGROUND by its distance from the contour,
	/// normalised by the local stroke width (Fig. 10); pseudo-Precision weights the
	/// BACKGROUND by its distance from that SAME contour, normalised by the distance
	/// to the nearest neighbouring component (Fig. 15).  So both measures run one
	/// pipeline -- distance-from-contour, then a stroke-width normalisation along the
	/// line normal to the skeleton -- once on the foreground and once on the
	/// background.  Generate() runs the recall side, then reuses its contour, distance
	/// transform and component labelling for the precision side.
	///
	/// Vocabulary, following the paper's Section III:
	///   D    = Chebyshev distance map from the contour points        (Eq. 2, Fig. 10c)
	///   S    = skeleton of the ground-truth text                     (Fig. 10b)
	///   NR   = Normalization type I, so D sums to 1 along the cross  (Eq. 3, Fig. 7)
	///   GW   = D / NR                                                (Eq. 2)
	///   NP   = min(Gc_sw, Gsw_bg) background normalisation           (Eq. 11)
	///   PW   = 1 + D / NP                                            (Eq. 10)
	///
	/// The skeleton follows the paper's reference [60] = Lee, Chen, "Recognition of
	/// handwritten Chinese characters via short line segments," Pattern Recognition
	/// 25(5), 1992 (Table 1 look-up, termination points).  Self-contained but for two
	/// collaborators: ConnectedComponents (the labelling Gcc) and Thinning (Zhang-Suen
	/// + the Table-1 look-up).  Everything else lives here.
	/// </summary>
	class PseudoWeights
	{
	public:
		/// <summary>
		/// Both weight maps.  gw is GW(x,y) (Eq. 2); pw is the stored precision weight
		/// PW(x,y) - 1 = D/NP capped at 2 (Eq. 10/11), which is the value
		/// ClassifiedPerformance consumes -- the full pseudo-Precision weight is pw + 1.
		/// foreground selects the ink value (Palette::Black for DIBCO ground truth).
		/// The recall chain is computed once and reused by the precision side.
		/// </summary>
		static void Generate(
			std::vector<double>& gw,
			std::vector<double>& pw,
			const Image& groundTruth,
			const Pixel8 foreground = Palette::Black)
		{
			const RecallArtifacts recall = ComputeRecall(gw, groundTruth, foreground);
			ComputePrecision(pw, recall);
		}

		/// <summary>
		/// GW(x,y) only (Eq. 2) -- the pseudo-Recall weight map, reproducing
		/// &lt;gt&gt;_RWeights.dat.  Background pixels are 0 (the domain of GW).
		/// </summary>
		static void RecallWeights(
			std::vector<double>& gw,
			const Image& groundTruth,
			const Pixel8 foreground = Palette::Black)
		{
			ComputeRecall(gw, groundTruth, foreground);
		}

		/// <summary>
		/// PW(x,y) - 1 only -- the pseudo-Precision weight map, reproducing
		/// &lt;gt&gt;_PWeights.dat.  Precision needs the entire recall chain, so this
		/// simply runs Generate and keeps the precision map; prefer Generate for both.
		/// </summary>
		static void PrecisionWeights(
			std::vector<double>& pw,
			const Image& groundTruth,
			const Pixel8 foreground = Palette::Black)
		{
			std::vector<double> gw;
			Generate(gw, pw, groundTruth, foreground);
		}

	protected:
		/// <summary>
		/// A typed raster that carries its own dimensions, so the pipeline below speaks
		/// in fields instead of (vector, width, height) triples.  operator[] is the
		/// linear index the traversals already carry; operator() is (x, y).  Zero-cost:
		/// every access inlines to data[y * width + x], exactly as the hand-indexed code.
		/// </summary>
		template <typename T>
		struct Field
		{
			int width = 0;
			int height = 0;
			std::vector<T> data;

			Field() = default;
			Field(const int w, const int h, const T init = T()) : width(w), height(h), data(static_cast<size_t>(w) * h, init) {}

			void Resize(const int w, const int h, const T init = T()) { width = w; height = h; data.assign(static_cast<size_t>(w) * h, init); }
			int  Size() const { return width * height; }

			T&       operator[](const size_t i)       { return data[i]; }
			const T& operator[](const size_t i) const { return data[i]; }
			T&       operator()(const int x, const int y)       { return data[static_cast<size_t>(y) * width + x]; }
			const T& operator()(const int x, const int y) const { return data[static_cast<size_t>(y) * width + x]; }
		};

		using Mask  = Field<uint8_t>;    // 0/1 maps: fg, contour, skeleton, region
		using Bytes = Field<uint8_t>;    // small-valued byte maps: D, factor, stroke widths, NP work
		using Words = Field<uint16_t>;   // values that can exceed 255: distance transforms, NR/NP

		// "Not yet reached" in a chessboard sweep; no real distance approaches it, so
		// the +1 relaxation never overflows.
		static constexpr uint16_t kUnreached = 0xFFFF;

		// 250: a background pixel beyond every component's stroke reach -- outside the
		// Gsw_bg region, where the paper sets PW = 1 (Eq. 10), i.e. the stored weight is
		// 0.  Real strokes never reach this far, so it doubles as an out-of-domain marker.
		static constexpr uint8_t kOutsideRegion = 0xFA;

		// A pixel carries a usable distance when D is in [1, 249]: nonzero (in the weight
		// domain) and below the out-of-region marker.
		static bool HasDistance(const uint8_t d) { return d != 0 && d < kOutsideRegion; }

		/// <summary>
		/// The recall-side products the precision side reuses: the contour, its distance
		/// transform, the component labelling and the medial factor (the precision
		/// contour IS the recall contour -- the single ground-truth text boundary).
		/// </summary>
		struct RecallArtifacts
		{
			Mask       fg;                // foreground mask (1 = ink)
			Components components;        // Gcc labelling (Eq. 4-5, 12-17)
			Mask       skeleton;          // S(x,y) (Fig. 10b)
			Mask       contour;           // contour points (Fig. 10b)
			Words      contourDistance;   // chessboard transform of the contour, reused for the background D
			Bytes      medialFactor;      // the per-skeleton factor whose product with D realises NR
		};

		// ---- the two measures --------------------------------------------------------

		/// <summary>
		/// Pseudo-Recall pipeline (Eq. 2-3).  D = distance from the contour; the medial
		/// normalisation NR along the line normal to the skeleton; GW = D/NR.  Fills gw
		/// and returns the artifacts the precision side reuses.
		/// </summary>
		static RecallArtifacts ComputeRecall(
			std::vector<double>& gw,
			const Image& groundTruth,
			const Pixel8 foreground)
		{
			const int width = groundTruth.width, height = groundTruth.height, size = width * height;

			RecallArtifacts recall;
			recall.fg.Resize(width, height, 0);
			for (int i = 0; i < size; ++i) recall.fg[i] = (groundTruth.data[i] == foreground) ? 1 : 0;

			recall.components = ConnectedComponents::Generate(groundTruth, foreground, /*8-conn*/ true);

			Skeletonize(recall.skeleton, recall.fg);
			EnsureComponentSeeds(recall.skeleton, recall.components);

			Contour(recall.contour, recall.fg);
			ChebyshevDistance(recall.contourDistance, recall.contour);

			Bytes D;
			ForegroundDistanceMap(D, recall.fg, recall.contour, recall.contourDistance, recall.skeleton, recall.components);

			Words NR;
			MedialNormalization(recall.medialFactor, NR, D, recall.contour, recall.skeleton, recall.components);

			// GW = D / NR (Eq. 2).  EnsureComponentSeeds guarantees a skeleton per
			// component, so NR > 0 at every ink pixel; the guard is defense-in-depth.
			gw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
				if (D[i] != 0 && NR[i] != 0) gw[i] = static_cast<double>(D[i]) / static_cast<double>(NR[i]);

			return recall;
		}

		/// <summary>
		/// Pseudo-Precision pipeline (Eq. 9-11).  The background is weighted by its
		/// distance from the ground-truth contour, normalised so the weight grows toward
		/// the midline between neighbouring components and is capped where a component's
		/// stroke no longer reaches (Eq. 10).  Runs the same distance/normalisation
		/// machinery as recall, on the background, then combines it with the recall-side
		/// stroke widths.
		/// </summary>
		static void ComputePrecision(
			std::vector<double>& pw,
			const RecallArtifacts& recall)
		{
			const int width = recall.fg.width;
			const int height = recall.fg.height;
			const int size = width * height;

			// Gsw_fg per component, and the Gsw_bg region it reaches into the background
			// (Fig. 15a-b).
			std::vector<int> componentStrokeWidth;     // Gsw_fg per label
			Bytes strokeWidthMap;                      // Gsw_fg carried along each component's contour
			ComponentStrokeWidths(strokeWidthMap, componentStrokeWidth, recall.medialFactor, recall.skeleton, recall.contour, recall.components);

			Mask region;                               // Gsw_bg region (Eq. 10, Fig. 15b)
			BackgroundStrokeRegion(region, recall.fg, componentStrokeWidth, recall.components);

			// Label the background straight from the foreground mask (the background is
			// where fg == 0), with no inverted image materialised.
			Components invComponents = ConnectedComponents::Generate(recall.fg.data, /*background*/ 0, width, height, /*8-conn*/ true);

			// Skeleton of the background.  The image border is treated as background (as
			// the rest of Doxa's thinning/distance code does), so the background frame is
			// zeroed before skeletonising.
			Mask invSkeleton;
			{
				Mask invFrame(width, height, 0);
				for (int i = 0; i < size; ++i) invFrame[i] = recall.fg[i] ? 0 : 1;
				for (int x = 0; x < width; ++x) { invFrame[x] = 0; invFrame[static_cast<size_t>(height - 1) * width + x] = 0; }
				for (int y = 0; y < height; ++y) { invFrame[static_cast<size_t>(y) * width] = 0; invFrame[static_cast<size_t>(y) * width + width - 1] = 0; }
				Skeletonize(invSkeleton, invFrame);
			}
			EnsureComponentSeeds(invSkeleton, invComponents);

			// D for the background, measured from the SAME ground-truth contour (Eq. 10),
			// gated to the Gsw_bg region (beyond it the sentinel marks PW = 1).  The
			// contour distance transform is reused from the recall pass.
			Bytes Dp;
			BackgroundDistanceMap(Dp, recall.fg, region, recall.contour, recall.contourDistance, invSkeleton, invComponents);

			// The background medial normalisation, same routine as recall.  It accumulates
			// an area (~R^2); NP per Eq. 11 is a stroke width, so take the square root back
			// to a radius at every in-region background pixel.
			Bytes invMedialFactor;
			Words NP;
			MedialNormalization(invMedialFactor, NP, Dp, recall.contour, invSkeleton, invComponents);
			invComponents.ForEachPixel([&](const Component&, int, int, int i)
			{
				if (HasDistance(Dp[i])) NP[i] = static_cast<uint16_t>(std::floor(std::sqrt(static_cast<double>(NP[i])) + 0.5));
			});

			// NP = min(Gc_sw, Gsw_bg) (Eq. 11), via two component-local ring passes over
			// the background: the first marks where adjacent components meet (the merging
			// case, Fig. 14d), the second uses the inter-component gap there and the stroke
			// reach elsewhere.
			Bytes mergeMarker(width, height, 0), NPfinal(width, height, 0);
			const PrecisionRing ringInputs{ strokeWidthMap, recall.contour, recall.components.labels, Dp, NP, mergeMarker };
			PrecisionNormalizationPass(mergeMarker, PrecisionPass::MarkMerges, ringInputs, invComponents);
			PrecisionNormalizationPass(NPfinal, PrecisionPass::Normalize, ringInputs, invComponents);

			// Stored precision weight = PW - 1 = D/NP, capped at 2 (Eq. 10).
			pw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
			{
				if (NPfinal[i] == 0) continue;
				const double v = static_cast<double>(Dp[i]) / NPfinal[i];
				pw[i] = (v > 2.0) ? 2.0 : v;
			}
		}

		// ---- shared ring scan --------------------------------------------------------

		/// <summary>
		/// The one ring scan every component-local worker shares.  Grows a square window
		/// R = 0,1,2..., clamped to the component bbox, scanning only the outer ring at
		/// each R; calls visit(j) for each ring cell (j = its linear index), where visit
		/// returns true if that cell qualifies.  Stops at the first R whose ring has at
		/// least one qualifying cell (returns true), or when the full bbox has been
		/// scanned with none (returns false).  Per-cell work lives in the visitor;
		/// clamping makes a degenerate ring revisit cells, which is harmless because
		/// every visitor's accumulation is idempotent (a fixed write, a max, or a test).
		///
		/// IMPORTANT: this is NOT a nearest-feature lookup.  It aggregates over EVERY
		/// feature on the first non-empty ring (all equidistant pixels participate) and
		/// the ring is clamped to the component bbox.  Do not "optimise" it into a
		/// Voronoi / nearest-owner map: that changes the result, which must stay bit-exact
		/// with the DIBCO reference weight files.
		/// </summary>
		template <typename Visit>
		static bool FirstNonEmptyRing(const Component& c, const int ax, const int ay, const int width, Visit&& visit)
		{
			const int bxmin = c.bounds.upperLeft.x, bxmax = c.bounds.bottomRight.x;
			const int bymin = c.bounds.upperLeft.y, bymax = c.bounds.bottomRight.y;

			for (int R = 0; ; ++R)
			{
				bool found = false;
				int xlo = ax - R, xhi = ax + R, ylo = ay - R, yhi = ay + R;
				if (xlo < bxmin) xlo = bxmin;  if (xhi > bxmax) xhi = bxmax;
				if (ylo < bymin) ylo = bymin;  if (yhi > bymax) yhi = bymax;

				const auto cell = [&](const int col, const int row)
				{
					if (visit(row * width + col)) found = true;
				};

				for (int row = ylo + 1; row < yhi; ++row) cell(xlo, row);
				for (int row = ylo + 1; row < yhi; ++row) cell(xhi, row);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, ylo);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, yhi);
				cell(xlo, ylo); cell(xlo, yhi); cell(xhi, ylo); cell(xhi, yhi);

				if (found) return true;
				if (xlo == bxmin && xhi == bxmax && ylo == bymin && yhi == bymax) return false;
			}
		}

		// ---- geometry ----------------------------------------------------------------

		/// <summary>
		/// Exact chessboard (Chebyshev) distance to the nearest seed (seed == nonzero in
		/// feature).  A forward raster pass over the four causal neighbours then a
		/// backward pass over the four anticausal neighbours yields the exact distance in
		/// one allocation, no queue.  Distance is 0 on the seeds, rising outward.
		/// </summary>
		static void ChebyshevDistance(Words& distance, const Mask& feature)
		{
			const int width = feature.width, height = feature.height, size = feature.Size();
			distance.Resize(width, height, 0);
			for (int i = 0; i < size; ++i) distance[i] = feature[i] ? 0 : kUnreached;

			const auto relax = [&](const int idx, const int neighbor)
			{
				const uint16_t cand = distance[neighbor];
				if (cand != kUnreached && cand + 1 < distance[idx]) distance[idx] = cand + 1;
			};

			for (int y = 0; y < height; ++y)             // forward: NW, N, NE, W
			{
				const int row = y * width;
				for (int x = 0; x < width; ++x)
				{
					const int idx = row + x;
					if (distance[idx] == 0) continue;
					if (y > 0)
					{
						relax(idx, idx - width);
						if (x > 0)         relax(idx, idx - width - 1);
						if (x < width - 1) relax(idx, idx - width + 1);
					}
					if (x > 0) relax(idx, idx - 1);
				}
			}

			for (int y = height - 1; y >= 0; --y)        // backward: SE, S, SW, E
			{
				const int row = y * width;
				for (int x = width - 1; x >= 0; --x)
				{
					const int idx = row + x;
					if (distance[idx] == 0) continue;
					if (y < height - 1)
					{
						relax(idx, idx + width);
						if (x < width - 1) relax(idx, idx + width + 1);
						if (x > 0)         relax(idx, idx + width - 1);
					}
					if (x < width - 1) relax(idx, idx + 1);
				}
			}
		}

		/// <summary>
		/// contour(x,y) = 1 where an ink pixel has a 4-connected background neighbour
		/// (Fig. 10b).  The frame is treated as background, so an edge pixel touches
		/// "outside".
		/// </summary>
		static void Contour(Mask& contour, const Mask& fg)
		{
			const int width = fg.width, height = fg.height;
			contour.Resize(width, height, 0);
			for (int y = 0; y < height; ++y)
			{
				const int row = y * width;
				for (int x = 0; x < width; ++x)
				{
					const int i = row + x;
					if (!fg[i]) continue;
					const bool touchesBg =
						(y == 0          || !fg[i - width]) ||
						(y == height - 1 || !fg[i + width]) ||
						(x == 0          || !fg[i - 1])     ||
						(x == width - 1  || !fg[i + 1]);
					if (touchesBg) contour[i] = 1;
				}
			}
		}

		/// <summary>
		/// The skeleton S(x,y) per Lee-Chen 1992: Zhang-Suen thinning to a fixed point,
		/// then the Table-1 look-up that deletes 8-simple points while preserving the T-
		/// and cross-junctions a plain Zhang-Suen would erode (kLeeChenTable1, iterated to
		/// a fixed point).  No subsequent short-curve deletion (the weight files are
		/// generated from the raw skeleton).  Worked on a 1-pixel background-padded buffer
		/// so a stroke touching the real image border still thins.
		/// </summary>
		static void Skeletonize(Mask& skeleton, const Mask& fg)
		{
			const int width = fg.width, height = fg.height;
			const int pw = width + 2, ph = height + 2;
			std::vector<uint8_t> padded(static_cast<size_t>(pw) * ph, 0);
			for (int y = 0; y < height; ++y)
			{
				const int srow = y * width, prow = (y + 1) * pw;
				for (int x = 0; x < width; ++x)
					padded[prow + (x + 1)] = fg[srow + x];
			}

			std::vector<uint8_t> thinned;
			ZhangSuenThinning::Skeletonize(thinned, padded, pw, ph);
			while (detail::ApplyTablePassInPlace(thinned, kLeeChenTable1, pw, ph)) {}

			skeleton.Resize(width, height, 0);
			for (int y = 0; y < height; ++y)
			{
				const int srow = y * width, prow = (y + 1) * pw;
				for (int x = 0; x < width; ++x)
					skeleton[srow + x] = thinned[prow + (x + 1)];
			}
		}

		// Lee-Chen 1992 Table 1 (page 544): the 256-entry simple-point deletion table.
		// Index = (P9 P8 P7 P6) << 4 | (P5 P4 P3 P2); 0x00 deletes P1, 0xFF keeps it, 0x01
		// marks a point Zhang-Suen already removed (treated as keep).  This is NOT Doxa's
		// general LeeChenThinning::kPostPassTable -- they differ in four entries (0x0E,
		// 0x45, 0x54, 0xE0); this is the table that reproduces the DIBCO weight files.
		static constexpr std::array<uint8_t, 256> kLeeChenTable1 = {{
			0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x01,
			0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01,
			0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
			0x01, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			0x01, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0x00, 0xFF, 0x00, 0x01, 0xFF, 0x01, 0xFF,
			0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			0x01, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
			0x00, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			0x01, 0x01, 0xFF, 0x01, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0x01, 0xFF, 0x00, 0x01, 0xFF, 0x00, 0xFF,
		}};

		/// <summary>
		/// Guarantees every component owns at least one skeleton pixel when thinning left
		/// it empty (a small symmetric blob the look-up pass erodes to nothing).  Forces
		/// the (rounded) centroid pixel, falling back to the raster-first seed if the
		/// centroid lands off a non-convex blob.  The centroid is computed only for the
		/// (rare) skeleton-less components, over the component's own bounding box.
		/// </summary>
		static void EnsureComponentSeeds(Mask& skeleton, const Components& components)
		{
			const int width = skeleton.width, height = skeleton.height;
			const int n = static_cast<int>(components.items.size());

			std::vector<uint8_t> hasSkeleton(n, 0);
			components.ForEachPixel([&](const Component& c, int, int, int i) { if (skeleton[i]) hasSkeleton[c.label] = 1; });

			for (const Component& c : components)
			{
				if (hasSkeleton[c.label]) continue;

				long long sumX = 0, sumY = 0, count = 0;
				for (int y = c.bounds.upperLeft.y; y <= c.bounds.bottomRight.y; ++y)
					for (int x = c.bounds.upperLeft.x; x <= c.bounds.bottomRight.x; ++x)
						if (components.labels[static_cast<size_t>(y) * width + x] == c.label) { sumX += x; sumY += y; ++count; }

				const int cx = static_cast<int>(std::llround(static_cast<double>(sumX) / count));
				const int cy = static_cast<int>(std::llround(static_cast<double>(sumY) / count));
				if (cx >= 0 && cx < width && cy >= 0 && cy < height &&
					components.labels[static_cast<size_t>(cy) * width + cx] == c.label)
					skeleton[static_cast<size_t>(cy) * width + cx] = 1;
				else
					skeleton[static_cast<size_t>(c.seed.y) * width + c.seed.x] = 1;
			}
		}

		// ---- medial normalisation (shared by both measures) --------------------------

		/// <summary>
		/// From the distance map D and the skeleton, produce the per-skeleton medial
		/// factor and the normalisation NR (Eq. 3 / Normalization type I): the distance-
		/// to-skeleton driven factor, the maximal D*factor along the local cross-section,
		/// and a propagation along the stroke so each break is penalised equally.
		/// </summary>
		static void MedialNormalization(Bytes& medialFactor, Words& NR, const Bytes& D, const Mask& contour, const Mask& skeleton, const Components& components)
		{
			Bytes skeletonDistance;
			SkeletonDistance(skeletonDistance, D, contour, skeleton);
			MedialFactor(medialFactor, D, skeletonDistance, skeleton, components);
			Normalization(NR, D, medialFactor, skeleton, components);
		}

		/// <summary>
		/// The medial-ridge value of D.  The paper's D is the raw contour distance; on the
		/// skeleton ridge the true medial radius is one beyond it.  Raises a skeleton
		/// pixel's D by 1 when it equals all four border-clamped 4-neighbours (a flat
		/// ridge).  In place, in component order.
		/// </summary>
		static void MedialRidgeAdjust(Bytes& D, const Mask& skeleton, const Components& components)
		{
			const int width = D.width, height = D.height;
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				const uint8_t c = D[i];
				if (!HasDistance(c)) return;
				const int up = (y > 0)          ? i - width : i;
				const int dn = (y < height - 1) ? i + width : i;
				const int lf = (x > 0)          ? i - 1     : i;
				const int rt = (x < width - 1)  ? i + 1     : i;
				if (D[up] == c && D[dn] == c && D[lf] == c && D[rt] == c && skeleton[i])
					D[i] = static_cast<uint8_t>(c + 1);
			});
		}

		/// <summary>
		/// distance-to-skeleton: the chessboard distance from each pixel to the nearest
		/// skeleton point, with skel&amp;!contour -> 1 (skel&amp;contour stays 0 via the
		/// self-hit), masked to pixels carrying a distance.
		/// </summary>
		static void SkeletonDistance(Bytes& skeletonDistance, const Bytes& D, const Mask& contour, const Mask& skeleton)
		{
			const int width = D.width, height = D.height, size = D.Size();
			Words distance;
			ChebyshevDistance(distance, skeleton);

			skeletonDistance.Resize(width, height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!HasDistance(D[i])) continue;
				skeletonDistance[i] = (skeleton[i] && !contour[i]) ? 1 : static_cast<uint8_t>(distance[i]);
			}
		}

		/// <summary>
		/// The per-skeleton medial factor whose product with D realises NR (Eq. 3).
		/// Starts as a copy of the skeleton, then: (cross-section) every pixel with a
		/// distance writes, over the first non-empty ring of its component window,
		/// factor[q] = D[q] + (skeletonDistance[centre] >= D[q] ? 1 : 0) for each skeleton
		/// q on that ring (component -> row -> column order, last writer wins); (endpoint)
		/// every skeleton pixel that is a Lee-Chen termination point inherits that
		/// neighbour's factor + 1.
		/// </summary>
		static void MedialFactor(Bytes& factor, const Bytes& D, const Bytes& skeletonDistance, const Mask& skeleton, const Components& components)
		{
			const int width = D.width, height = D.height;
			factor = skeleton;   // skeleton pixels = 1, else 0

			// cross-section pass: each centre writes the skeleton pixels on its first non-
			// empty ring (idempotent per cell, so last-writer-wins across centres).  The
			// component -> row -> column order is part of the result -- do not convert to a
			// per-skeleton-pixel gather.
			components.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				const uint8_t d = D[i];
				if (!HasDistance(d)) return;
				const uint8_t reach = skeletonDistance[i];
				FirstNonEmptyRing(c, x, y, width, [&](const int j)
				{
					if (!skeleton[j]) return false;
					const uint8_t dq = D[j];
					factor[j] = static_cast<uint8_t>(reach >= dq ? dq + 1 : dq);
					return true;
				});
			});

			// endpoint pass
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!skeleton[i]) return;
				const int v = TerminationPointFactor(factor, skeleton, x, y, width, height);
				if (v > 0) factor[i] = static_cast<uint8_t>(v + 1);
			});
		}

		/// <summary>
		/// NR(x,y) -- Normalization type I (Eq. 3, Fig. 7).  For each pixel with a
		/// distance, the MAX of D*factor over the skeleton pixels on the first non-empty
		/// ring of its component window; then a propagation pass spreads a stroke's peak
		/// along it, so a break is penalised equally regardless of the local stroke width.
		/// </summary>
		static void Normalization(Words& NR, const Bytes& D, const Bytes& factor, const Mask& skeleton, const Components& components)
		{
			const int width = D.width, height = D.height;
			NR.Resize(D.width, D.height, 0);

			components.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				int best = -1;
				const bool found = FirstNonEmptyRing(c, x, y, width, [&](const int j)
				{
					if (!skeleton[j]) return false;
					const int v = static_cast<int>(D[j]) * static_cast<int>(factor[j]);
					if (v > best) best = v;
					return true;
				});
				NR[i] = found ? static_cast<uint16_t>(best) : 0;
			});

			// propagation: a pixel whose NR differs from all four (set) clamped neighbours
			// inherits its left neighbour's NR (which may already be updated this sweep),
			// spreading the peak cross-section along the stroke.
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				if (PropagateAlongStroke(NR, x, y, width, height)) NR[i] = NR[i - 1];
			});
		}

		// Lee-Chen termination point (Fig. 3a): count the 8 border-clamped skeleton
		// neighbours; if exactly one, return its medial factor so the endpoint can inherit
		// it (+1).  The bottom-right neighbour's factor is read at (row+D)*W + B (the +col
		// term differs from the other seven); this matches the DIBCO reference weight files
		// exactly and is kept for bit-exact .dat parity.
		static int TerminationPointFactor(const Bytes& factor, const Mask& skeleton, const int col, const int row, const int width, const int height)
		{
			const int A = (col - 1 >= 0)         ? -1 : 0;   // left
			const int B = (col + 1 <= width - 1) ?  1 : 0;   // right
			const int C = (row - 1 >= 0)         ? -1 : 0;   // up
			const int D = (row + 1 <= height - 1)?  1 : 0;   // down

			struct Check { int sr, sc, nidx; };
			const Check checks[8] = {
				{ row + C, col,     (row + C) * width + col     },   // top
				{ row + D, col,     (row + D) * width + col     },   // bottom
				{ row,     col + A,  row      * width + col + A  },   // left
				{ row,     col + B,  row      * width + col + B  },   // right
				{ row + C, col + A, (row + C) * width + col + A  },   // top-left
				{ row + D, col + B, (row + D) * width + B        },   // bottom-right (see note above)
				{ row + D, col + A, (row + D) * width + col + A  },   // bottom-left
				{ row + C, col + B, (row + C) * width + col + B  },   // top-right
			};

			int count = 0, last = -1;
			for (const Check& k : checks)
				if (skeleton[static_cast<size_t>(k.sr) * width + k.sc]) { ++count; last = factor[k.nidx]; }
			
			return (count == 1) ? last : -1;
		}

		// NR propagation predicate: true iff all four border-clamped neighbours are set
		// (NR != 0) and NR[centre] differs from every one of them.
		static bool PropagateAlongStroke(const Words& NR, const int col, const int row, const int width, const int height)
		{
			const int dxL = (col - 1 >= 0)         ? -1 : 0;
			const int dxR = (col + 1 <= width - 1) ?  1 : 0;
			const int dyU = (row - 1 >= 0)         ? -1 : 0;
			const int dyD = (row + 1 <= height - 1)?  1 : 0;

			const int up = NR[static_cast<size_t>(row + dyU) * width + col];
			const int dn = NR[static_cast<size_t>(row + dyD) * width + col];
			const int lf = NR[static_cast<size_t>(row) * width + col + dxL];
			const int rt = NR[static_cast<size_t>(row) * width + col + dxR];
			if (!up || !dn || !lf || !rt) return false;

			const int centre = NR[static_cast<size_t>(row) * width + col];
			
			return !(centre == up || centre == dn || centre == lf || centre == rt);
		}

		// ---- distance maps -----------------------------------------------------------

		/// <summary>
		/// D(x,y) for the foreground (Eq. 2, Fig. 10c): the contour distance (reused
		/// transform), with skel&amp;contour -> 1, masked to the foreground, then the
		/// medial-ridge adjustment.
		/// </summary>
		static void ForegroundDistanceMap(Bytes& D, const Mask& fg, const Mask& contour, const Words& contourDistance, const Mask& skeleton, const Components& components)
		{
			const int size = fg.Size();
			D.Resize(fg.width, fg.height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!fg[i]) continue;
				D[i] = (contour[i] && skeleton[i]) ? 1 : static_cast<uint8_t>(contourDistance[i]);
			}
			MedialRidgeAdjust(D, skeleton, components);
		}

		/// <summary>
		/// D(x,y) for the background (Eq. 10): the distance to the SAME ground-truth
		/// contour (reused transform), with invSkel&amp;contour -> 1, taken only inside the
		/// Gsw_bg region; beyond the region the out-of-region marker stands in for PW = 1;
		/// ink pixels are 0.  Then the medial-ridge adjustment on the background skeleton.
		/// </summary>
		static void BackgroundDistanceMap(Bytes& Dp, const Mask& fg, const Mask& region, const Mask& contour, const Words& contourDistance, const Mask& invSkeleton, const Components& invComponents)
		{
			const int size = fg.Size();
			Dp.Resize(fg.width, fg.height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (fg[i]) continue;                                       // ink pixel -> 0
				Dp[i] = (invSkeleton[i] && contour[i]) ? 1
				      : region[i] ? static_cast<uint8_t>(contourDistance[i]) // in-region distance (< 250)
				      : kOutsideRegion;                                      // beyond the stroke reach
			}
			MedialRidgeAdjust(Dp, invSkeleton, invComponents);
		}

		// ---- precision normalisation -------------------------------------------------

		// Gsw_fg per component (Fig. 15a) and its map: componentStrokeWidth[label] =
		// 2 * floor(mean medial factor over the component's skeleton).  strokeWidthMap
		// carries that value along the component's CONTOUR (the only place the precision
		// ring reads it), and componentStrokeWidth also sizes the Gsw_bg region.
		static void ComponentStrokeWidths(Bytes& strokeWidthMap, std::vector<int>& componentStrokeWidth, const Bytes& medialFactor, const Mask& skeleton, const Mask& contour, const Components& components)
		{
			const int n = static_cast<int>(components.items.size());
			std::vector<long long> sum(n, 0), count(n, 0);
			components.ForEachPixel([&](const Component& c, int, int, int i)
			{
				if (skeleton[i]) { sum[c.label] += medialFactor[i]; ++count[c.label]; }
			});

			componentStrokeWidth.assign(n, 0);
			for (const Component& c : components)
				componentStrokeWidth[c.label] = count[c.label]
					? static_cast<int>((sum[c.label] / count[c.label]) * 2)
					: 0;

			strokeWidthMap.Resize(components.width, components.height, 0);
			components.ForEachPixel([&](const Component& c, int, int, int i)
			{
				if (contour[i]) strokeWidthMap[i] = static_cast<uint8_t>(componentStrokeWidth[c.label] & 0xFF);
			});
		}

		// Gsw_bg region (Eq. 10, Fig. 15b): a background pixel inside SOME component's
		// bounding box dilated by 2 * componentStrokeWidth on every side (clamped to the
		// image) is "reached" by that component's stroke; outside every such box, PW = 1.
		static void BackgroundStrokeRegion(Mask& region, const Mask& fg, const std::vector<int>& componentStrokeWidth, const Components& components)
		{
			const int width = fg.width, height = fg.height;
			region.Resize(width, height, 0);
			for (const Component& c : components)
			{
				const int m = 2 * componentStrokeWidth[c.label];
				int x0 = c.bounds.upperLeft.x - m,  x1 = c.bounds.bottomRight.x + m;
				int y0 = c.bounds.upperLeft.y - m,  y1 = c.bounds.bottomRight.y + m;
				if (x0 < 0) x0 = 0;  if (x1 > width - 1)  x1 = width - 1;
				if (y0 < 0) y0 = 0;  if (y1 > height - 1) y1 = height - 1;
				for (int y = y0; y <= y1; ++y)
				{
					const int row = y * width;
					for (int x = x0; x <= x1; ++x)
						if (!fg[row + x]) region[row + x] = 1;
				}
			}
		}

		// The two precision normalisation passes (Eq. 11).  The first marks where the
		// background ring touches two distinct components (the merging case); the second
		// produces NP, using the marked inter-component gap where merging looms and the
		// stroke reach elsewhere.
		enum class PrecisionPass { MarkMerges, Normalize };

		// The rasters the precision ring reads, bundled (held by const reference) so the
		// passes and the ring don't thread a dozen parameters.  All outlive the passes.
		struct PrecisionRing
		{
			const Bytes&            strokeWidthMap;   // Gsw_fg carried along the fg contour
			const Mask&             contour;          // the ground-truth contour, rung over
			const std::vector<int>& componentLabels;  // fg labels, to spot merging
			const Bytes&            Dp;               // background distance
			const Words&            NP;               // background normalisation (sqrt-rounded)
			const Bytes&            mergeMarker;      // where adjacent components meet
		};

		// One precision pass over the background components (gate: label-owned, Dp in [1,249]).
		static void PrecisionNormalizationPass(Bytes& out, const PrecisionPass pass, const PrecisionRing& in, const Components& invComponents)
		{
			const int width = in.Dp.width, height = in.Dp.height;
			invComponents.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(in.Dp[i])) return;
				out[i] = static_cast<uint8_t>(PrecisionNormalizationRing(in, c, x, y, pass, width, height));
			});
		}

		// Rings on the ground-truth contour; for each contour pixel q on the first non-
		// empty ring collect strokeWidthMap[q] (max -> reach) and whether two distinct
		// components appear (adjacent -> merge risk).  Then, with dp = Dp[centre] and
		// np = NP[centre]:  dp > reach -> 0;  MarkMerges -> adjacent ? np : 0;  Normalize
		// -> (a merge was marked within Chebyshev radius (reach - dp) of the centre &&
		// np < reach) ? np : reach   (Eq. 11: min(Gc_sw, Gsw_bg)).  No contour in the bbox -> 0.
		static int PrecisionNormalizationRing(const PrecisionRing& in, const Component& c, const int ax, const int ay, const PrecisionPass pass, const int width, const int height)
		{
			int reach = -1, firstLabel = -1;
			bool adjacent = false;
			const bool found = FirstNonEmptyRing(c, ax, ay, width, [&](const int j)
			{
				if (!in.contour[j]) return false;
				const int v = in.strokeWidthMap[j];

				if (v > reach) reach = v;
				const int L = in.componentLabels[j];

				if (firstLabel < 0) firstLabel = L;
				else if (L != firstLabel) adjacent = true;

				return true;
			});
			if (!found) return 0;

			const int i = ay * width + ax;
			const int dp = in.Dp[i];
			const int np = in.NP[i];   // NP is integer-valued (sqrt-rounded above)
			if (dp > reach) return 0;
			if (pass == PrecisionPass::MarkMerges)
				return (adjacent ? np : 0) & 0xFF;

			const int diff = reach - dp;
			const bool merging = AnyWithin(in.mergeMarker, ax, ay, diff, width, height);
			
			return ((merging && np < reach) ? np : reach) & 0xFF;
		}

		// True iff any nonzero pixel of map lies within Chebyshev distance `radius` of
		// (col,row), over the image-clamped square window.  radius 0 -> false.
		static bool AnyWithin(const Bytes& map, const int col, const int row, const int radius, const int width, const int height)
		{
			if (radius == 0) return false;
			
			int xlo = col - radius, xhi = col + radius, ylo = row - radius, yhi = row + radius;
			
			if (xlo < 0) xlo = 0;
			if (xhi > width - 1) xhi = width - 1;
			if (ylo < 0) ylo = 0;
			if (yhi > height - 1) yhi = height - 1;
			
			for (int ry = ylo; ry <= yhi; ++ry)
			{
				const int rrow = ry * width;
				for (int rx = xlo; rx <= xhi; ++rx)
					if (map[rrow + rx]) return true;
			}

			return false;
		}
	};
}


#endif // PSEUDOWEIGHTS_HPP
