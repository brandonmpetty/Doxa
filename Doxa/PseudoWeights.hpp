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


namespace Doxa
{
	// Bespoke Zhang-Suen 1984 deletion rule + the two sub-iteration look-up tables for
	// PseudoWeights' skeleton -- minimal and special-purpose, so the header carries its own
	// thinning.  Delete (0x00) iff B(P1) in [2,6], exactly one 0->1 transition around the
	// 8-ring, and the sub-iteration's two corner triples are clear; else keep (0xFF).  Bit
	// order matches PseudoWeights::Neighbors.  (Free functions, pre-class, so the static
	// constexpr tables can be initialized from them -- MSVC won't call an in-class constexpr
	// member from a sibling data-member initializer.)
	namespace skel
	{
		constexpr uint8_t Rule(const uint8_t a, const int subIter)
		{
			const int p2 = a & 1;
			const int p3 = (a >> 1) & 1;
			const int p4 = (a >> 2) & 1;
			const int p5 = (a >> 3) & 1;
			const int p6 = (a >> 4) & 1;
			const int p7 = (a >> 5) & 1;
			const int p8 = (a >> 6) & 1;
			const int p9 = (a >> 7) & 1;

			const int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
			if (B < 2 || B > 6) return 0xFF;

			int A = 0;
			if (!p2 && p3) ++A;
			if (!p3 && p4) ++A;
			if (!p4 && p5) ++A;
			if (!p5 && p6) ++A;
			if (!p6 && p7) ++A;
			if (!p7 && p8) ++A;
			if (!p8 && p9) ++A;
			if (!p9 && p2) ++A;
			if (A != 1) return 0xFF;

			if (subIter == 1) { if (p2 && p4 && p6) return 0xFF;  if (p4 && p6 && p8) return 0xFF; }
			else              { if (p2 && p4 && p8) return 0xFF;  if (p2 && p6 && p8) return 0xFF; }
			
			return 0x00;
		}

		constexpr std::array<uint8_t, 256> Table(const int subIter)
		{
			std::array<uint8_t, 256> t{};
			for (int i = 0; i < 256; ++i) t[i] = Rule(static_cast<uint8_t>(i), subIter);
			
			return t;
		}
	}

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
	/// (RWeights.dat stores GW; PWeights.dat stores PW - 1.)  The maps produced here are
	/// bit-exact with the DIBCO reference weight files.
	///
	/// THE PIPELINE.  Both measures run ONE machinery -- distance-from-contour, then a
	/// stroke-width normalization along the line normal to the skeleton -- once on the
	/// FOREGROUND (recall) and once on the BACKGROUND (precision), about the SAME contour:
	///
	///   ground-truth G  --ConnectedComponents + one setup sweep-->
	///   overlay { kInk, kContour, kSkeleton }              (Fig. 11a,b; Thin erodes kSkeleton)
	///        |
	///        +-- D  = Chebyshev distance from the contour     ForegroundDistanceMap  (Eq. 2, Fig. 11c)
	///        +-- NR = stroke-width cross-section normalizer    MedialNormalization    (Eq. 3)
	///        v
	///   GW = D / NR  -- pseudo-Recall weight                   ComputeRecall          (Eq. 2)
	///
	///   Precision runs the same D and normalizer on the BACKGROUND skeleton, the normalizer
	///   capped by the distance to neighboring components:
	///   PW - 1 = Dp / NP,  NP = min(Gc_sw, Gsw_bg)             ComputePrecision       (Eq. 10-11, Fig. 15)
	///
	/// Generate() runs recall, then reuses its contour, distance transform, component
	/// labeling and medial factor for precision.
	///
	/// Vocabulary, following the paper's Section III:
	///   D    = Chebyshev distance map from the contour points        (Eq. 2, Fig. 10c)
	///   S    = skeleton of the ground-truth text                     (Fig. 10b)
	///   NR   = Normalization type I, so D sums to 1 along the cross  (Eq. 3, Fig. 7)
	///   GW   = D / NR                                                (Eq. 2)
	///   NP   = min(Gc_sw, Gsw_bg) background normalization           (Eq. 11)
	///   PW   = 1 + D / NP                                            (Eq. 10)
	///
	/// The skeleton follows the paper's reference [60] = Lee, Chen, "Recognition of
	/// handwritten Chinese characters via short line segments," Pattern Recognition 25(5),
	/// 1992 (Table 1 look-up, termination points).  The thinning is a bespoke, minimal,
	/// in-place kernel carried here (see skel:: and Thin), so the only collaborator is
	/// ConnectedComponents (the labeling Gcc).  Everything else lives here.
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
		/// &lt;gt&gt;_PWeights.dat.  Precision needs the entire recall chain, so this simply
		/// runs Generate and keeps the precision map; prefer Generate for both.
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
		// ============================================================================
		//  Data model
		// ============================================================================

		/// <summary>
		/// A typed raster that carries its own dimensions, so the pipeline below speaks in
		/// fields instead of (vector, width, height) triples.  operator[] is the linear index
		/// the traversals already carry; operator() is (x, y).  Zero-cost: every access
		/// inlines to data[y * width + x], exactly as the hand-indexed code.
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

		using Mask  = Field<uint8_t>;    // the flag overlay (kInk/kContour/kSkeleton) or a 0/1 map
		using Bytes = Field<uint8_t>;    // small-valued byte maps: D, factor, stroke widths, NP work
		using Words = Field<uint16_t>;   // values that can exceed 255: distance transforms, NR/NP

		// The overlay raster -- Figure 11(a)+(b) in one byte per pixel.  A pixel is ink iff it
		// carries any flag, so the background is simply overlay == 0 (no separate mask) and the
		// component labeller reads it directly; "removed" interior ink is kInk without kSkeleton.
		static constexpr uint8_t kInk      = 0x01;  // original ink: the GW domain (Eq. 2)
		static constexpr uint8_t kContour  = 0x02;  // contour point (Fig. 10b)
		static constexpr uint8_t kSkeleton = 0x04;  // skeleton S(x,y), eroded in place from kInk

		// "Not yet reached" in a chessboard sweep; no real distance approaches it, so the +1
		// relaxation never overflows.
		static constexpr uint16_t kUnreached = 0xFFFF;

		// 250: a background pixel beyond every component's stroke reach -- outside the Gsw_bg
		// region, where the paper sets PW = 1 (Eq. 10), i.e. the stored weight is 0.  Real
		// strokes never reach this far, so it doubles as an out-of-domain marker.
		static constexpr uint8_t kOutsideRegion = 0xFA;

		// A pixel carries a usable distance when D is in [1, 249]: nonzero (in the weight
		// domain) and below the out-of-region marker.
		static bool HasDistance(const uint8_t d) { return d != 0 && d < kOutsideRegion; }

		/// <summary>
		/// The recall-side products the precision side reuses: the contour, its distance
		/// transform, the component labeling and the medial factor (the precision contour IS
		/// the recall contour -- the single ground-truth text boundary).
		/// </summary>
		struct RecallArtifacts
		{
			Mask       overlay;           // kInk | kContour | kSkeleton -- Figure 11(a)+(b) on one raster
			Components components;        // Gcc labeling (Eq. 4-5, 12-17)
			Words      contourDistance;   // chessboard transform of the contour, reused for the background D
			Bytes      medialFactor;      // the per-skeleton factor whose product with D realises NR
		};

		// ============================================================================
		//  The two measures (orchestration -- the Figure 11 / Figure 15 cascades)
		// ============================================================================

		/// <summary>
		/// Pseudo-Recall pipeline (Eq. 2-3).  D = distance from the contour; the medial
		/// normalization NR along the line normal to the skeleton; GW = D/NR.  Fills gw and
		/// returns the artifacts the precision side reuses.
		/// </summary>
		static RecallArtifacts ComputeRecall(
			std::vector<double>& gw,
			const Image& groundTruth,
			const Pixel8 foreground)
		{
			const int width = groundTruth.width;
			const int height = groundTruth.height;
			const int size = width * height;

			RecallArtifacts recall;
			recall.components = ConnectedComponents::Generate(groundTruth, foreground, /*8-conn*/ true);

			// One setup sweep builds Figure 11(a)+(b): kInk and the kSkeleton thinning seed on
			// every ink pixel, and kContour where an ink pixel has a 4-neighbor outside it (the
			// frame is background).  Contour is found here, with the thinning seed, in one pass.
			Mask& ov = recall.overlay;
			ov.Resize(width, height, 0);
			const auto ink = [&](const int x, const int y)
				{ return x >= 0 && x < width && y >= 0 && y < height && groundTruth.data[y * width + x] == foreground; };
			
			for (int y = 0; y < height; ++y)
			{
				const int row = y * width;

				for (int x = 0; x < width; ++x)
				{
					const int i = row + x;
					if (groundTruth.data[i] != foreground) continue;
					ov[i] = kInk | kSkeleton;
					if (!ink(x, y - 1) || !ink(x, y + 1) || !ink(x - 1, y) || !ink(x + 1, y)) ov[i] |= kContour;
				}
			}

			// Thin the kSkeleton layer in place to S(x,y); seed any component thinned to nothing.
			Thin(ov, kSkeleton);
			EnsureComponentSeeds(ov, kSkeleton, recall.components);

			ChebyshevDistance(recall.contourDistance, ov, kContour);

			Bytes D;
			ForegroundDistanceMap(D, ov, recall.contourDistance, recall.components);

			Words NR;
			MedialNormalization(recall.medialFactor, NR, D, ov, recall.components);

			// Gsw_fg per component (Fig. 15a), stored on each Component for the precision pass.
			AssignStrokeWidths(recall.components, recall.medialFactor, ov);

			// GW = D / NR (Eq. 2).  EnsureComponentSeeds guarantees a skeleton per component, so
			// NR > 0 at every ink pixel; the guard is defense-in-depth.
			gw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
				if (D[i] != 0 && NR[i] != 0) gw[i] = static_cast<double>(D[i]) / static_cast<double>(NR[i]);

			return recall;
		}

		/// <summary>
		/// Pseudo-Precision pipeline (Eq. 9-11).  The background is weighted by its distance
		/// from the ground-truth contour, normalized so the weight grows toward the midline
		/// between neighboring components and is capped where a component's stroke no longer
		/// reaches (Eq. 10).  Runs the same distance/normalization machinery as recall, on the
		/// background, then combines it with the recall-side stroke widths.
		/// </summary>
		static void ComputePrecision(
			std::vector<double>& pw,
			const RecallArtifacts& recall)
		{
			const int width = recall.overlay.width;
			const int height = recall.overlay.height;
			const int size = width * height;
			const Mask& ov = recall.overlay;

			// The Gsw_bg region the foreground strokes reach into the background (Fig. 15a-b).  The
			// per-component Gsw_fg the precision ring needs is read straight off each Component
			// (strokeWidth) via its label, so no separate stroke-width image is materialized.
			Mask region;                               // Gsw_bg region (Eq. 10, Fig. 15b)
			BackgroundStrokeRegion(region, ov, recall.components);

			// Label the background straight off the overlay (background == overlay 0), no
			// inverted image materialized.
			Components invComponents = ConnectedComponents::Generate(ov.data, /*background*/ 0, width, height, /*8-conn*/ true);

			// Background skeleton, thinned in place on its own raster: the kSkeleton seed on every
			// background pixel except the frame (which the thinner treats as background), then
			// thinned -- no inverted-image, invFrame or padding copy.
			Mask bg(width, height, 0);
			for (int i = 0; i < size; ++i) if (ov[i] == 0) bg[i] = kSkeleton;
			for (int x = 0; x < width; ++x) { bg[x] = 0; bg[static_cast<size_t>(height - 1) * width + x] = 0; }
			for (int y = 0; y < height; ++y) { bg[static_cast<size_t>(y) * width] = 0; bg[static_cast<size_t>(y) * width + width - 1] = 0; }
			Thin(bg, kSkeleton);
			EnsureComponentSeeds(bg, kSkeleton, invComponents);

			// D for the background, measured from the SAME ground-truth contour (Eq. 10), gated
			// to the Gsw_bg region (beyond it the sentinel marks PW = 1).  The contour distance
			// transform is reused from the recall pass.
			Bytes Dp;
			BackgroundDistanceMap(Dp, ov, bg, region, recall.contourDistance, invComponents);

			// The background medial normalization, same routine as recall.  It accumulates an
			// area (~R^2); NP per Eq. 11 is a stroke width, so take the square root back to a
			// radius at every in-region background pixel.
			Bytes invMedialFactor;
			Words NP;
			MedialNormalization(invMedialFactor, NP, Dp, bg, invComponents);
			invComponents.ForEachPixel([&](const Component&, int, int, int i)
			{
				if (HasDistance(Dp[i])) NP[i] = static_cast<uint16_t>(std::floor(std::sqrt(static_cast<double>(NP[i])) + 0.5));
			});

			// NP = min(Gc_sw, Gsw_bg) (Eq. 11), via two component-local ring passes over the
			// background: the first marks where adjacent components meet (the merging case,
			// Fig. 14d), the second uses the inter-component gap there and the stroke reach else.
			Bytes mergeMarker(width, height, 0);
			Bytes NPfinal(width, height, 0);
			Words reachCache(width, height, kUnreached);  // MarkMerges records reach; Normalize reuses it
			const PrecisionRing ringInputs{ ov, recall.components, Dp, NP, mergeMarker, recall.contourDistance };
			PrecisionNormalizationPass(mergeMarker, reachCache, PrecisionPass::MarkMerges, ringInputs, invComponents);
			PrecisionNormalizationPass(NPfinal, reachCache, PrecisionPass::Normalize, ringInputs, invComponents);

			// Stored precision weight = PW - 1 = D/NP, capped at 2 (Eq. 10).
			pw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
			{
				if (NPfinal[i] == 0) continue;
				const double v = static_cast<double>(Dp[i]) / NPfinal[i];
				pw[i] = (v > 2.0) ? 2.0 : v;
			}
		}

		// ============================================================================
		//  Generic raster toolkit (reusable primitives, not paper-specific)
		// ============================================================================

		/// <summary>
		/// Exact chessboard (Chebyshev) distance to the nearest seed (seed == the `bit` flag set
		/// in feature).  A forward raster pass over the four causal neighbors then a backward
		/// pass over the four anticausal neighbors yields the exact distance in one allocation,
		/// no queue.  Distance is 0 on the seeds, rising outward.
		/// </summary>
		static void ChebyshevDistance(Words& distance, const Mask& feature, const uint8_t bit)
		{
			const int width = feature.width;
			const int height = feature.height;
			const int size = feature.Size();
			distance.Resize(width, height, 0);
			for (int i = 0; i < size; ++i) distance[i] = (feature[i] & bit) ? 0 : kUnreached;

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
		/// The one ring scan every component-local worker shares.  Grows a square window
		/// R = 0,1,2..., clamped to the component bbox, scanning only the outer ring at each R;
		/// calls visit(j) for each ring cell (j = its linear index), where visit returns true if
		/// that cell qualifies.  Stops at the first R whose ring has at least one qualifying cell
		/// (returns true), or when the full bbox has been scanned with none (returns false).
		/// Per-cell work lives in the visitor; clamping makes a degenerate ring revisit cells,
		/// which is harmless because every visitor's accumulation is idempotent (a fixed write, a
		/// max, or a test).
		///
		/// IMPORTANT: this is NOT a nearest-feature lookup.  It aggregates over EVERY feature on
		/// the first non-empty ring (all equidistant pixels participate) and the ring is clamped
		/// to the component bbox.  Do not "optimize" it into a Voronoi / nearest-owner map: that
		/// changes the result, which must stay bit-exact with the DIBCO reference weight files.
		/// </summary>
		// startR lets a caller skip an initial run of rings it can PROVE are empty -- e.g. a
		// distance transform gives the exact distance to the nearest feature, so no feature lies on
		// any ring closer than that (every clamped perimeter cell at ring R is within Chebyshev
		// distance R of the center).  Starting there is bit-exact; passing too large an startR is
		// NOT (it would skip the true first ring), so only feed a proven lower bound.
		template <typename Visit>
		static bool FirstNonEmptyRing(const Component& c, const int ax, const int ay, const int width, Visit&& visit, int* outRadius = nullptr, const int startR = 0)
		{
			const int bxmin = c.bounds.upperLeft.x;
			const int bxmax = c.bounds.bottomRight.x;
			const int bymin = c.bounds.upperLeft.y;
			const int bymax = c.bounds.bottomRight.y;

			for (int R = startR; ; ++R)
			{
				bool found = false;
				int xlo = ax - R;
				int xhi = ax + R;
				int ylo = ay - R;
				int yhi = ay + R;
				if (xlo < bxmin) xlo = bxmin;
				if (xhi > bxmax) xhi = bxmax;
				if (ylo < bymin) ylo = bymin;
				if (yhi > bymax) yhi = bymax;

				const auto cell = [&](const int col, const int row)
				{
					if (visit(row * width + col)) found = true;
				};

				for (int row = ylo + 1; row < yhi; ++row) cell(xlo, row);
				for (int row = ylo + 1; row < yhi; ++row) cell(xhi, row);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, ylo);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, yhi);
				cell(xlo, ylo); cell(xlo, yhi); cell(xhi, ylo); cell(xhi, yhi);

				if (found) { if (outRadius) *outRadius = R; return true; }
				if (xlo == bxmin && xhi == bxmax && ylo == bymin && yhi == bymax) return false;
			}
		}

		/// <summary>
		/// Re-walks EXACTLY the ring at radius R -- the same bbox-clamped perimeter (and cell order)
		/// FirstNonEmptyRing visits at that R -- calling visit(j) for each cell.  This lets a second
		/// pass re-walk a ring a prior FirstNonEmptyRing already located (its returned outRadius)
		/// without regrowing from R = 0.  The cell SET is identical, so an order-independent reducer
		/// (e.g. a max) over it stays bit-exact; do not use it where per-cell write order matters.
		/// </summary>
		template <typename Visit>
		static void ScanRingAt(const Component& c, const int ax, const int ay, const int R, const int width, Visit&& visit)
		{
			int xlo = ax - R;
			int xhi = ax + R;
			int ylo = ay - R;
			int yhi = ay + R;
			if (xlo < c.bounds.upperLeft.x)   xlo = c.bounds.upperLeft.x;
			if (xhi > c.bounds.bottomRight.x) xhi = c.bounds.bottomRight.x;
			if (ylo < c.bounds.upperLeft.y)   ylo = c.bounds.upperLeft.y;
			if (yhi > c.bounds.bottomRight.y) yhi = c.bounds.bottomRight.y;

			const auto cell = [&](const int col, const int row) { visit(row * width + col); };

			for (int row = ylo + 1; row < yhi; ++row) cell(xlo, row);
			for (int row = ylo + 1; row < yhi; ++row) cell(xhi, row);
			for (int col = xlo + 1; col < xhi; ++col) cell(col, ylo);
			for (int col = xlo + 1; col < xhi; ++col) cell(col, yhi);
			cell(xlo, ylo); cell(xlo, yhi); cell(xhi, ylo); cell(xhi, yhi);
		}

		// --- thinning kernel (bespoke, minimal, in place) -----------------------------

		// 8-neighbor packing of (x, y) on the `bit` layer: bits 0..7 = P2(N) P3(NE) P4(E)
		// P5(SE) P6(S) P7(SW) P8(W) P9(NW).  Out-of-bounds reads as background, so the kernel
		// thins in place on the real raster -- no padding buffer, the image frame is background,
		// and a border stroke still thins.
		static uint8_t Neighbors(const Mask& m, const int x, const int y, const uint8_t bit)
		{
			const int w = m.width;
			const int h = m.height;

			// Interior fast path: when none of the eight neighbors can fall off the raster, read
			// them straight off contiguous memory with no per-neighbor clamping.  Bit packing is
			// identical to the bounds-checked path below (P2 N, P3 NE, ... P9 NW).
			if (x > 0 && x < w - 1 && y > 0 && y < h - 1)
			{
				const uint8_t* d = m.data.data() + static_cast<size_t>(y) * w + x;
				return static_cast<uint8_t>(
					 ((d[-w]     & bit) ? 1 : 0)       | (((d[-w + 1] & bit) ? 1 : 0) << 1) | (((d[1]      & bit) ? 1 : 0) << 2) |
					(((d[w + 1]  & bit) ? 1 : 0) << 3) | (((d[w]      & bit) ? 1 : 0) << 4) | (((d[w - 1]  & bit) ? 1 : 0) << 5) |
					(((d[-1]     & bit) ? 1 : 0) << 6) | (((d[-w - 1] & bit) ? 1 : 0) << 7));
			}

			const auto on = [&](const int xx, const int yy) -> int
				{ return (xx >= 0 && xx < w && yy >= 0 && yy < h && (m(xx, yy) & bit)) ? 1 : 0; };
			return static_cast<uint8_t>(
				 on(x,     y - 1)        | (on(x + 1, y - 1) << 1) | (on(x + 1, y    ) << 2) |
				(on(x + 1, y + 1) << 3)  | (on(x,     y + 1) << 4) | (on(x - 1, y + 1) << 5) |
				(on(x - 1, y    ) << 6)  | (on(x - 1, y - 1) << 7));
		}

		// One sequential in-place simple-point pass: delete as we scan, so a later pixel sees the
		// hole -- the correct order for the Table-1 simple-point table.
		static bool TablePass(Mask& s, const uint8_t bit, const std::array<uint8_t, 256>& table)
		{
			bool removed = false;
			const int w = s.width;
			const int h = s.height;
			for (int y = 0; y < h; ++y)
				for (int x = 0; x < w; ++x)
				{
					const int i = y * w + x;
					if ((s[i] & bit) && table[Neighbors(s, x, y, bit)] == 0x00) { s[i] = static_cast<uint8_t>(s[i] & ~bit); removed = true; }
				}
			return removed;
		}

		/// <summary>
		/// Thin the `bit` layer of `raster` to the Lee-Chen 1992 skeleton, in place: Zhang-Suen
		/// erodes the boundary to a fixed point, then the Table-1 simple-point pass
		/// (kLeeChenTable1) tidies it to a fixed point.  Bounds-aware -- no padding, the frame is
		/// background, and 8-connected components thin independently (they never touch).
		///
		/// The Zhang-Suen sweeps run over an ACTIVE FRONTIER: only a boundary pixel can ever be
		/// deleted (an interior pixel has all eight neighbors set, so B(P1) = 8 > 6), and
		/// deleting one exposes its neighbors, which join the frontier.  Each sweep costs the
		/// shrinking boundary, not the whole page -- identical output, far less work for the
		/// large background.  (The short Table-1 cleanup stays a full in-place sweep.)
		/// </summary>
		static void Thin(Mask& raster, const uint8_t bit)
		{
			const int w = raster.width;
			const int h = raster.height;
			const auto off = [&](const int x, const int y)
				{ return x < 0 || x >= w || y < 0 || y >= h || !(raster[static_cast<size_t>(y) * w + x] & bit); };

			// A frontier cell carries its (x, y) with the linear index, so the hot sub-pass never
			// divides/mods the index back into coordinates (Neighbors and the neighbor walk both
			// need the coordinates).
			struct Cell { int i, x, y; };

			// Seed the frontier with every boundary pixel of the layer.
			std::vector<Cell> frontier;
			std::vector<Cell> dead;
			std::vector<Cell> next;
			std::vector<uint8_t> queued(raster.Size(), 0);
			for (int y = 0; y < h; ++y)
			{
				const int row = y * w;

				for (int x = 0; x < w; ++x)
				{
					const int i = row + x;

					if ((raster[i] & bit) &&
						(off(x, y - 1) || off(x + 1, y - 1) || off(x + 1, y) || off(x + 1, y + 1) ||
						 off(x, y + 1) || off(x - 1, y + 1) || off(x - 1, y) || off(x - 1, y - 1)))
						{
							frontier.push_back({ i, x, y }); queued[i] = 1;
						}
				}
			}


			// One batched Zhang-Suen sub-pass over the frontier: mark, delete together, carry
			// survivors forward, and add the neighbors a deletion newly exposed.  Deletion is
			// batched (every cell tests the pre-deletion raster), so the sub-pass is independent of
			// frontier order -- the skeleton is identical.
			const auto subpass = [&](const std::array<uint8_t, 256>& table) -> bool
			{
				dead.clear();
				for (const Cell& c : frontier)
					if ((raster[c.i] & bit) && table[Neighbors(raster, c.x, c.y, bit)] == 0x00) dead.push_back(c);

				if (dead.empty()) return false;

				for (const Cell& c : dead) { raster[c.i] = static_cast<uint8_t>(raster[c.i] & ~bit); queued[c.i] = 0; }

				next.clear();
				for (const Cell& c : frontier) if (raster[c.i] & bit) next.push_back(c);
				for (const Cell& c : dead)
				{
					for (int dy = -1; dy <= 1; ++dy)
					{
						const int ny = c.y + dy;
						if (ny < 0 || ny >= h) continue;
						const int nrow = ny * w;
						for (int dx = -1; dx <= 1; ++dx)
						{
							const int nx = c.x + dx;
							if ((dx || dy) && nx >= 0 && nx < w)
							{
								const int ni = nrow + nx;
								if ((raster[ni] & bit) && !queued[ni]) { queued[ni] = 1; next.push_back({ ni, nx, ny }); }
							}
						}
					}
				}

				frontier.swap(next);

				return true;
			};

			bool changed = true;
			while (changed) 
			{
				changed = false; 
				changed |= subpass(kZhangSuen1); 
				changed |= subpass(kZhangSuen2);
			}

			while (TablePass(raster, bit, kLeeChenTable1)) {}
		}

		// Lee-Chen 1992 Table 1 (page 544): the 256-entry simple-point deletion table.
		// Index = (P9 P8 P7 P6) << 4 | (P5 P4 P3 P2); 0x00 deletes P1, 0xFF keeps it, 0x01 marks
		// a point Zhang-Suen already removed (treated as keep).  This is the table that reproduces
		// the DIBCO weight files (it differs from a textbook Lee-Chen post-pass table in four
		// entries: 0x0E, 0x45, 0x54, 0xE0).
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

		// The two Zhang-Suen sub-iteration tables (compile-time from skel::Rule), run over the
		// frontier to a fixed point before the Table-1 pass above.
		static constexpr std::array<uint8_t, 256> kZhangSuen1 = skel::Table(1);
		static constexpr std::array<uint8_t, 256> kZhangSuen2 = skel::Table(2);

		/// <summary>
		/// Guarantees every component owns at least one skeleton pixel when thinning left it
		/// empty (a small symmetric blob the look-up pass erodes to nothing).  Forces the
		/// (rounded) centroid pixel, falling back to the raster-first seed if the centroid lands
		/// off a non-convex blob.  The centroid is computed only for the (rare) skeleton-less
		/// components, over the component's own bounding box.
		/// </summary>
		static void EnsureComponentSeeds(Mask& skeleton, const uint8_t bit, const Components& components)
		{
			const int width = skeleton.width;
			const int height = skeleton.height;
			const int n = static_cast<int>(components.items.size());

			std::vector<uint8_t> hasSkeleton(n, 0);
			components.ForEachPixel([&](const Component& c, int, int, int i) { if (skeleton[i] & bit) hasSkeleton[c.label] = 1; });

			for (const Component& c : components)
			{
				if (hasSkeleton[c.label]) continue;

				long long sumX = 0;
				long long sumY = 0;
				long long count = 0;
				for (int y = c.bounds.upperLeft.y; y <= c.bounds.bottomRight.y; ++y)
					for (int x = c.bounds.upperLeft.x; x <= c.bounds.bottomRight.x; ++x)
						if (components.labels[static_cast<size_t>(y) * width + x] == c.label) { sumX += x; sumY += y; ++count; }

				const int cx = static_cast<int>(std::llround(static_cast<double>(sumX) / count));
				const int cy = static_cast<int>(std::llround(static_cast<double>(sumY) / count));
				if (cx >= 0 && cx < width && cy >= 0 && cy < height &&
					components.labels[static_cast<size_t>(cy) * width + cx] == c.label)
					skeleton[static_cast<size_t>(cy) * width + cx] |= bit;
				else
					skeleton[static_cast<size_t>(c.seed.y) * width + c.seed.x] |= bit;
			}
		}

		// ============================================================================
		//  Pseudo-Recall cascade:  D  ->  NR  ->  Gsw_fg
		// ============================================================================

		/// <summary>
		/// D(x,y) for the foreground (Eq. 2, Fig. 10c): the contour distance (reused transform),
		/// with skel&amp;contour -> 1, masked to the foreground, then the medial-ridge adjustment.
		/// </summary>
		static void ForegroundDistanceMap(Bytes& D, const Mask& overlay, const Words& contourDistance, const Components& components)
		{
			const int size = overlay.Size();
			D.Resize(overlay.width, overlay.height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!(overlay[i] & kInk)) continue;
				D[i] = ((overlay[i] & kContour) && (overlay[i] & kSkeleton)) ? 1 : static_cast<uint8_t>(contourDistance[i]);
			}
			MedialRidgeAdjust(D, overlay, components);
		}

		/// <summary>
		/// From the distance map D and the skeleton, produce the per-skeleton medial factor and
		/// the normalization NR (Eq. 3 / Normalization type I): the distance-to-skeleton driven
		/// factor, the maximal D*factor along the local cross-section, and a propagation along the
		/// stroke so each break is penalized equally.
		/// </summary>
		static void MedialNormalization(Bytes& medialFactor, Words& NR, const Bytes& D, const Mask& overlay, const Components& components)
		{
			Bytes skeletonDistance;
			SkeletonDistance(skeletonDistance, D, overlay);

			// MedialFactor and Normalization ring the SAME skeleton over the SAME centers to the
			// SAME first-non-empty radius.  MedialFactor grows from R = 0 (its per-cell write order
			// matters) and records that radius here; Normalization (a per-cell max, order-free)
			// re-walks just that ring instead of regrowing.  kUnreached = no skeleton in the bbox.
			Words ringRadius(D.width, D.height, kUnreached);
			MedialFactor(medialFactor, D, skeletonDistance, overlay, components, ringRadius);
			Normalization(NR, D, medialFactor, overlay, components, ringRadius);
		}

		/// <summary>
		/// distance-to-skeleton: the chessboard distance from each pixel to the nearest skeleton
		/// point, with skel&amp;!contour -> 1 (skel&amp;contour stays 0 via the self-hit), masked
		/// to pixels carrying a distance.
		/// </summary>
		static void SkeletonDistance(Bytes& skeletonDistance, const Bytes& D, const Mask& overlay)
		{
			const int width = D.width;
			const int height = D.height;
			const int size = D.Size();
			Words distance;
			ChebyshevDistance(distance, overlay, kSkeleton);

			skeletonDistance.Resize(width, height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!HasDistance(D[i])) continue;
				skeletonDistance[i] = ((overlay[i] & kSkeleton) && !(overlay[i] & kContour)) ? 1 : static_cast<uint8_t>(distance[i]);
			}
		}

		/// <summary>
		/// The per-skeleton medial factor whose product with D realises NR (Eq. 3).  Starts as a
		/// copy of the skeleton, then: (cross-section) every pixel with a distance writes, over
		/// the first non-empty ring of its component window, factor[q] = D[q] +
		/// (skeletonDistance[center] >= D[q] ? 1 : 0) for each skeleton q on that ring (component
		/// -> row -> column order, last writer wins); (endpoint) every skeleton pixel that is a
		/// Lee-Chen termination point inherits that neighbor's factor + 1.
		/// </summary>
		static void MedialFactor(Bytes& factor, const Bytes& D, const Bytes& skeletonDistance, const Mask& overlay, const Components& components, Words& ringRadius)
		{
			const int width = D.width;
			const int height = D.height;
			const int size = D.Size();
			factor.Resize(width, height, 0);
			for (int i = 0; i < size; ++i) factor[i] = (overlay[i] & kSkeleton) ? 1 : 0;   // skeleton pixels = 1, else 0

			// cross-section pass: each center writes the skeleton pixels on its first non-empty
			// ring (idempotent per cell, so last-writer-wins across centers).  The component ->
			// row -> column order is part of the result -- do not convert to a per-skeleton-pixel
			// gather.  The found radius is recorded for Normalization to re-walk.
			components.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				const uint8_t d = D[i];
				if (!HasDistance(d)) return;
				const uint8_t reach = skeletonDistance[i];
				// Skip the empty inner rings: for a non-skeleton center skeletonDistance is the
				// exact distance to the nearest skeleton, a proven lower bound on the first ring; a
				// skeleton center self-hits at R=0, so start there.
				const int startR = (overlay[i] & kSkeleton) ? 0 : skeletonDistance[i];
				int foundR = -1;
				const bool found = FirstNonEmptyRing(c, x, y, width, [&](const int j)
				{
					if (!(overlay[j] & kSkeleton)) return false;
					const uint8_t dq = D[j];
					factor[j] = static_cast<uint8_t>(reach >= dq ? dq + 1 : dq);
					return true;
				}, &foundR, startR);
				ringRadius[i] = found ? static_cast<uint16_t>(foundR) : kUnreached;
			});

			// endpoint pass
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!(overlay[i] & kSkeleton)) return;
				const int v = TerminationPointFactor(factor, overlay, x, y, width, height);
				if (v > 0) factor[i] = static_cast<uint8_t>(v + 1);
			});
		}

		/// <summary>
		/// NR(x,y) -- Normalization type I (Eq. 3, Fig. 7).  For each pixel with a distance, the
		/// MAX of D*factor over the skeleton pixels on the first non-empty ring of its component
		/// window; then a propagation pass spreads a stroke's peak along it, so a break is
		/// penalized equally regardless of the local stroke width.
		/// </summary>
		static void Normalization(Words& NR, const Bytes& D, const Bytes& factor, const Mask& overlay, const Components& components, const Words& ringRadius)
		{
			const int width = D.width;
			const int height = D.height;
			NR.Resize(D.width, D.height, 0);

			components.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				const uint16_t R = ringRadius[i];
				if (R == kUnreached) { NR[i] = 0; return; }   // MedialFactor found no skeleton in the bbox
				int best = -1;
				ScanRingAt(c, x, y, static_cast<int>(R), width, [&](const int j)
				{
					if (!(overlay[j] & kSkeleton)) return;
					const int v = static_cast<int>(D[j]) * static_cast<int>(factor[j]);
					if (v > best) best = v;
				});
				NR[i] = static_cast<uint16_t>(best);
			});

			// propagation: a pixel whose NR differs from all four (set) clamped neighbors inherits
			// its left neighbor's NR (which may already be updated this sweep), spreading the peak
			// cross-section along the stroke.
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				if (PropagateAlongStroke(NR, x, y, width, height)) NR[i] = NR[i - 1];
			});
		}

		/// <summary>
		/// The medial-ridge value of D.  The paper's D is the raw contour distance; on the
		/// skeleton ridge the true medial radius is one beyond it.  Raises a skeleton pixel's D by
		/// 1 when it equals all four border-clamped 4-neighbors (a flat ridge).  In place, in
		/// component order.
		/// </summary>
		static void MedialRidgeAdjust(Bytes& D, const Mask& overlay, const Components& components)
		{
			const int width = D.width;
			const int height = D.height;

			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				const uint8_t c = D[i];
				if (!HasDistance(c)) return;

				const int up = (y > 0)          ? i - width : i;
				const int dn = (y < height - 1) ? i + width : i;
				const int lf = (x > 0)          ? i - 1     : i;
				const int rt = (x < width - 1)  ? i + 1     : i;
				if (D[up] == c && D[dn] == c && D[lf] == c && D[rt] == c && (overlay[i] & kSkeleton))
					D[i] = static_cast<uint8_t>(c + 1);
			});
		}

		// Lee-Chen termination point (Fig. 3a): count the 8 border-clamped skeleton neighbors; if
		// exactly one, return its medial factor so the endpoint can inherit it (+1).  The
		// bottom-right neighbor's factor is read at (row+D)*W + B (the +col term differs from the
		// other seven); this matches the DIBCO reference weight files exactly and is kept for
		// bit-exact .dat parity.
		static int TerminationPointFactor(const Bytes& factor, const Mask& overlay, const int col, const int row, const int width, const int height)
		{
			const int A = (col - 1 >= 0)         ? -1 : 0;   // left
			const int B = (col + 1 <= width - 1) ?  1 : 0;   // right
			const int C = (row - 1 >= 0)         ? -1 : 0;   // up
			const int D = (row + 1 <= height - 1)?  1 : 0;   // down

			const int up   = (row + C) * width;   // row bases, computed once
			const int mid  =  row      * width;
			const int down = (row + D) * width;

			int count = 0;
			int last = -1;
			const auto hit = [&](const int skelIdx, const int factorIdx)   // skeleton neighbor? inherit its factor
			{
				if (overlay[static_cast<size_t>(skelIdx)] & kSkeleton) { ++count; last = factor[factorIdx]; }
			};

			hit(up   + col,     up   + col);      // top
			hit(down + col,     down + col);      // bottom
			hit(mid  + col + A, mid  + col + A);   // left
			hit(mid  + col + B, mid  + col + B);   // right
			hit(up   + col + A, up   + col + A);   // top-left
			hit(down + col + B, down + B);        // bottom-right: factor read at +B, NOT +col+B (the asymmetry above)
			hit(down + col + A, down + col + A);   // bottom-left
			hit(up   + col + B, up   + col + B);   // top-right

			return (count == 1) ? last : -1;
		}

		// NR propagation predicate: true iff all four border-clamped neighbors are set
		// (NR != 0) and NR[center] differs from every one of them.
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

			const int center = NR[static_cast<size_t>(row) * width + col];

			return !(center == up || center == dn || center == lf || center == rt);
		}

		// Gsw_fg per component (Fig. 15a): 2*floor(mean medial factor over the component's
		// skeleton), stored on each Component (recall) for the precision pass and Gsw_bg region.
		static void AssignStrokeWidths(Components& components, const Bytes& medialFactor, const Mask& overlay)
		{
			const int n = static_cast<int>(components.items.size());
			std::vector<long long> sum(n, 0);
			std::vector<long long> count(n, 0);

			components.ForEachPixel([&](const Component& c, int, int, int i)
			{
				if (overlay[i] & kSkeleton) { sum[c.label] += medialFactor[i]; ++count[c.label]; }
			});

			for (Component& c : components)
				c.strokeWidth = count[c.label] ? static_cast<int>((sum[c.label] / count[c.label]) * 2) : 0;
		}

		// ============================================================================
		//  Pseudo-Precision cascade:  Gsw region  ->  Dp  ->  NP = min(Gc_sw, Gsw_bg)
		// ============================================================================

		// Gsw_bg region (Eq. 10, Fig. 15b): a background pixel inside SOME component's bounding
		// box dilated by 2 * its stroke width on every side (clamped to the image) is "reached"
		// by that component's stroke; outside every such box, PW = 1.
		static void BackgroundStrokeRegion(Mask& region, const Mask& overlay, const Components& components)
		{
			const int width = overlay.width;
			const int height = overlay.height;
			region.Resize(width, height, 0);

			for (const Component& c : components)
			{
				const int m = 2 * c.strokeWidth;
				int x0 = c.bounds.upperLeft.x - m;
				int x1 = c.bounds.bottomRight.x + m;
				int y0 = c.bounds.upperLeft.y - m;
				int y1 = c.bounds.bottomRight.y + m;
				if (x0 < 0) x0 = 0;
				if (x1 > width - 1) x1 = width - 1;
				if (y0 < 0) y0 = 0;
				if (y1 > height - 1) y1 = height - 1;

				for (int y = y0; y <= y1; ++y)
				{
					const int row = y * width;
					for (int x = x0; x <= x1; ++x)
						if (!(overlay[row + x] & kInk)) region[row + x] = 1;
				}
			}
		}

		/// <summary>
		/// D(x,y) for the background (Eq. 10): the distance to the SAME ground-truth contour
		/// (reused transform), with bgSkel&amp;contour -> 1, taken only inside the Gsw_bg region;
		/// beyond the region the out-of-region marker stands in for PW = 1; ink pixels are 0.
		/// Then the medial-ridge adjustment on the background skeleton.
		/// </summary>
		static void BackgroundDistanceMap(Bytes& Dp, const Mask& overlay, const Mask& bg, const Mask& region, const Words& contourDistance, const Components& invComponents)
		{
			const int size = overlay.Size();
			Dp.Resize(overlay.width, overlay.height, 0);
			for (int i = 0; i < size; ++i)
			{
				if (overlay[i] & kInk) continue;                                       // ink pixel -> 0
				Dp[i] = ((bg[i] & kSkeleton) && (overlay[i] & kContour)) ? 1            // (disjoint: never taken)
				      : region[i] ? static_cast<uint8_t>(contourDistance[i])           // in-region distance (< 250)
				      : kOutsideRegion;                                                 // beyond the stroke reach
			}
			MedialRidgeAdjust(Dp, bg, invComponents);
		}

		// The two precision normalization passes (Eq. 11).  The first marks where the background
		// ring touches two distinct components (the merging case); the second produces NP, using
		// the marked inter-component gap where merging looms and the stroke reach elsewhere.
		enum class PrecisionPass { MarkMerges, Normalize };

		// The rasters the precision ring reads, bundled (held by const reference) so the passes
		// and the ring don't thread a dozen parameters.  All outlive the passes.
		struct PrecisionRing
		{
			const Mask&       overlay;          // the recall overlay, rung over its kContour
			const Components& components;       // fg records: strokeWidth (-> reach) and label (-> merging), by labels[j]
			const Bytes&      Dp;               // background distance
			const Words&      NP;               // background normalization (sqrt-rounded)
			const Bytes&      mergeMarker;      // where adjacent components meet
			const Words&      contourDistance;  // Chebyshev distance to the contour: the ring's start radius
		};

		// One precision pass over the background components (gate: label-owned, Dp in [1,249]).
		static void PrecisionNormalizationPass(Bytes& out, Words& reachCache, const PrecisionPass pass, const PrecisionRing& in, const Components& invComponents)
		{
			const int width = in.Dp.width;
			const int height = in.Dp.height;

			invComponents.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(in.Dp[i])) return;

				out[i] = static_cast<uint8_t>(PrecisionNormalizationRing(in, reachCache, c, x, y, pass, width, height));
			});
		}

		// Rings on the ground-truth contour; for each contour pixel q on the first non-empty ring
		// collect its component's Gsw_fg (items[labels[q]].strokeWidth, max -> reach) and whether two distinct components appear
		// (adjacent -> merge risk).  Then, with dp = Dp[center] and np = NP[center]:  dp > reach
		// -> 0;  MarkMerges -> adjacent ? np : 0;  Normalize -> (a merge was marked within
		// Chebyshev radius (reach - dp) of the center && np < reach) ? np : reach   (Eq. 11:
		// min(Gc_sw, Gsw_bg)).  No contour in the bbox -> 0.
		//
		// The ring's reach (and "found") is a pure function of read-only inputs identical in both
		// passes, so MarkMerges records it in reachCache (kUnreached == "no contour found") and
		// Normalize reuses it -- the second pass does no ring search at all.
		static int PrecisionNormalizationRing(const PrecisionRing& in, Words& reachCache, const Component& c, const int ax, const int ay, const PrecisionPass pass, const int width, const int height)
		{
			const int i = ay * width + ax;

			if (pass == PrecisionPass::Normalize)
			{
				const uint16_t cached = reachCache[i];
				if (cached == kUnreached) return 0;                       // MarkMerges found no contour
				const int reach = cached;
				const int dp = in.Dp[i];
				if (dp > reach) return 0;
				const int np = in.NP[i];
				const int diff = reach - dp;
				const bool merging = AnyWithin(in.mergeMarker, ax, ay, diff, width, height);
				return ((merging && np < reach) ? np : reach) & 0xFF;
			}

			// MarkMerges: the single ring search, recording reach for Normalize.  The contour
			// distance transform is the exact distance to the nearest contour, hence a proven lower
			// bound on the first non-empty ring -- start there and skip the empty inner rings.
			int reach = -1;
			int firstLabel = -1;
			bool adjacent = false;
			const bool found = FirstNonEmptyRing(c, ax, ay, width, [&](const int j)
			{
				if (!(in.overlay[j] & kContour)) return false;
				const int L = in.components.labels[j];                            // contour pixel -> its component
				const int v = in.components.items[L].strokeWidth & 0xFF;          // its Gsw_fg (low byte, as stored)

				if (v > reach) reach = v;

				if (firstLabel < 0) firstLabel = L;
				else if (L != firstLabel) adjacent = true;

				return true;
			}, nullptr, in.contourDistance[i]);
			reachCache[i] = found ? static_cast<uint16_t>(reach) : kUnreached;
			if (!found) return 0;

			const int dp = in.Dp[i];
			const int np = in.NP[i];   // NP is integer-valued (sqrt-rounded above)
			if (dp > reach) return 0;
			return (adjacent ? np : 0) & 0xFF;
		}

		// True iff any nonzero pixel of map lies within Chebyshev distance `radius` of (col,row),
		// over the image-clamped square window.  radius 0 -> false.
		static bool AnyWithin(const Bytes& map, const int col, const int row, const int radius, const int width, const int height)
		{
			if (radius == 0) return false;

			int xlo = col - radius;
			int xhi = col + radius;
			int ylo = row - radius;
			int yhi = row + radius;
			
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
