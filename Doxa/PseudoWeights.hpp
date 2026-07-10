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
	/// <summary>
	/// The Zhang-Suen deletion rule and its two sub-iteration look-up tables, the first stage
	/// of the PseudoWeights skeleton.  A pixel is deleted when it has two to six neighbors,
	/// exactly one background-to-ink transition around them, and the sub-iteration's corner
	/// conditions hold.  Rule returns 0x00 to delete and 0xFF to keep, with the neighbor bit
	/// order of PseudoWeights::Neighbors.  These live outside the class so its static tables
	/// can be initialized at compile time.
	/// </summary>
	/// <remarks>"A Fast Parallel Algorithm for Thinning Digital Patterns", 1984.</remarks>
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
	/// Pseudo F-Measure Weights: K. Ntirogiannis, B. Gatos, I. Pratikakis
	/// Generates the two ground-truth weight maps behind the pseudo Recall and Precision
	/// metrics, bit-exact with the DIBCO reference weight files: RWeights.dat stores GW,
	/// and PWeights.dat stores PW - 1.
	///
	/// Pseudo-Recall weighs each ink pixel by its distance from the text contour, normalized
	/// across the stroke, so that missing the core of a stroke costs more than shaving its
	/// edge: GW = D / NR (Eq. 2, 3).  Pseudo-Precision weighs the background near the text the
	/// same way, about the same contour, normalized by stroke width and capped where
	/// components approach one another, so that false ink costs the most between close
	/// strokes: PW = 1 + D / NP (Eq. 10, 11).
	///
	/// Both sides run one machinery: label the components, thin the text to its skeleton,
	/// measure the distance from the contour, then normalize along the stroke's cross section.
	/// Generate runs the recall side once and reuses its contour, distances, and labeling for
	/// the precision side.  The skeleton follows the paper's reference: Zhang-Suen thinning
	/// finished by the Lee-Chen simple-point table and termination points.
	/// </summary>
	/// <remarks>
	/// "Performance Evaluation Methodology for Historical Document Image Binarization", 2013.
	/// "Recognition of Handwritten Chinese Characters via Short Line Segments", 1992.
	/// </remarks>
	class PseudoWeights
	{
	public:
		/// <summary>
		/// Generates both weight maps.  gw receives GW (Eq. 2); pw receives the stored form
		/// PW - 1, capped at 2 (Eq. 10, 11), which is the value ClassifiedPerformance consumes.
		/// foreground selects the ink value, Palette::Black for the DIBCO ground truth.
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
		/// The pseudo-Recall weight map GW alone (Eq. 2), reproducing &lt;gt&gt;_RWeights.dat.
		/// Background pixels are 0.
		/// </summary>
		static void RecallWeights(
			std::vector<double>& gw,
			const Image& groundTruth,
			const Pixel8 foreground = Palette::Black)
		{
			ComputeRecall(gw, groundTruth, foreground);
		}

		/// <summary>
		/// The pseudo-Precision weight map PW - 1 alone, reproducing &lt;gt&gt;_PWeights.dat.
		/// Precision needs the entire recall chain, so this runs Generate and keeps the
		/// precision map; prefer Generate when both are wanted.
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
		/// A typed raster that carries its own dimensions, so the pipeline below passes fields
		/// instead of (vector, width, height) triples.  operator[] takes the linear index the
		/// traversals already carry; operator() takes (x, y).
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

		// The overlay raster, Figure 11(a) and (b) in one byte per pixel.  A pixel is ink when
		// any flag is set, so the background is simply overlay == 0 and the component labeler
		// reads the raster directly.  Ink the thinning removed keeps kInk and loses kSkeleton.
		static constexpr uint8_t kInk      = 0x01;  // original ink: the GW domain (Eq. 2)
		static constexpr uint8_t kContour  = 0x02;  // contour point (Fig. 10b)
		static constexpr uint8_t kSkeleton = 0x04;  // skeleton S(x,y), eroded in place from kInk

		// "Not yet reached" in a chessboard sweep; no real distance approaches it, so the +1
		// relaxation never overflows.
		static constexpr uint16_t kUnreached = 0xFFFF;

		// A background pixel beyond every component's stroke reach, outside the Gsw_bg region
		// where the paper sets PW = 1 (Eq. 10) and the stored weight is 0.  Real strokes never
		// reach 250 pixels, so the value doubles as an out-of-domain marker.
		static constexpr uint8_t kOutsideRegion = 0xFA;

		/// <summary>
		/// A pixel carries a usable distance when D is in [1, 249]: nonzero and in the region.
		/// </summary>
		static bool HasDistance(const uint8_t d) { return d != 0 && d < kOutsideRegion; }

		/// <summary>
		/// The recall-side products the precision side reuses: the overlay's contour and
		/// skeleton, the component labeling, and the contour's distance transform.  The
		/// precision contour is the recall contour, the one ground-truth text boundary.
		/// </summary>
		struct RecallArtifacts
		{
			Mask       overlay;           // kInk | kContour | kSkeleton, Figure 11(a) and (b) on one raster
			Components components;        // Gcc labeling (Eq. 4-5, 12-17)
			Words      contourDistance;   // chessboard transform of the contour, reused for the background D
		};

		// ============================================================================
		//  The two measures
		// ============================================================================

		/// <summary>
		/// The pseudo-Recall pipeline (Eq. 2, 3, Fig. 11): the distance from the contour, the
		/// medial normalization along the skeleton, then GW = D / NR.  Fills gw and returns
		/// the artifacts the precision side reuses.
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
			{
				return x >= 0 && x < width && y >= 0 && y < height && groundTruth.data[y * width + x] == foreground;
			};
			
			for (int y = 0; y < height; ++y)
			{
				const int row = y * width;

				for (int x = 0; x < width; ++x)
				{
					const int i = row + x;
					if (groundTruth.data[i] != foreground) continue;

					ov[i] = kInk | kSkeleton;
					if (!ink(x, y - 1) || !ink(x, y + 1) || !ink(x - 1, y) || !ink(x + 1, y))
						ov[i] |= kContour;
				}
			}

			// Thin the kSkeleton layer in place to S(x,y); seed any component thinned to nothing.
			Thin(ov, kSkeleton);
			EnsureComponentSeeds(ov, kSkeleton, recall.components);

			ChebyshevDistance(recall.contourDistance, ov, kContour);

			Bytes D;
			ForegroundDistanceMap(D, ov, recall.contourDistance, recall.components);

			Words NR;
			Bytes medialFactor;                        // recall-local: feeds AssignStrokeWidths, then dies here
			MedialNormalization(medialFactor, NR, D, ov, recall.components);

			// Gsw_fg per component (Fig. 15a), stored on each Component for the precision pass.
			AssignStrokeWidths(recall.components, medialFactor, ov);

			// GW = D / NR (Eq. 2).  EnsureComponentSeeds guarantees a skeleton per component, so
			// NR > 0 at every ink pixel; the guard is defense-in-depth.
			gw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
				if (D[i] != 0 && NR[i] != 0) gw[i] = static_cast<double>(D[i]) / static_cast<double>(NR[i]);

			return recall;
		}

		/// <summary>
		/// The pseudo-Precision pipeline (Eq. 9-11, Fig. 15).  The background near the text is
		/// weighted by its distance from the ground-truth contour, normalized so the weight
		/// grows toward the midline between components and is capped where a stroke no longer
		/// reaches.  Runs the recall machinery on the background, then folds in the recall-side
		/// stroke widths.
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

			// The background skeleton, thinned in place on its own raster: the kSkeleton seed on
			// every interior background pixel, then thinned.  The frame stays off, matching the
			// reference, which treats the image frame as background.
			Mask bg(width, height, 0);
			for (int y = 1; y < height - 1; ++y)
			{
				const int row = y * width;
				for (int x = 1; x < width - 1; ++x)
					if (ov[row + x] == 0) bg[row + x] = kSkeleton;
			}
			Thin(bg, kSkeleton);
			EnsureComponentSeeds(bg, kSkeleton, invComponents);

			// D for the background, measured from the same ground-truth contour (Eq. 10), gated
			// to the Gsw_bg region (beyond it the sentinel marks PW = 1).  The contour distance
			// transform is reused from the recall pass.
			Bytes Dp;
			BackgroundDistanceMap(Dp, ov, bg, region, recall.contourDistance, invComponents);

			// The background medial normalization, same routine as recall.  It accumulates an
			// area (~R^2); NP per Eq. 11 is a stroke width, so take the square root back to a
			// radius at every in-region background pixel.
			Bytes invMedialFactor;                     // the spine's intermediate factor; precision needs only NP
			Words NP;
			MedialNormalization(invMedialFactor, NP, Dp, bg, invComponents);
			invComponents.ForEachPixel([&](const Component&, int, int, int i)
			{
				if (HasDistance(Dp[i])) NP[i] = 
					static_cast<uint16_t>(std::floor(std::sqrt(static_cast<double>(NP[i])) + 0.5));
			});

			// NP = min(Gc_sw, Gsw_bg) (Eq. 11) in two component-local passes: MarkMerges runs
			// the one ring search, caching each pixel's stroke reach and marking where
			// components meet (the merging case, Fig. 14); NormalizeNP then combines them.
			Bytes mergeMarker(width, height, 0);
			Bytes NPfinal(width, height, 0);
			Words reachCache(width, height, kUnreached);  // MarkMerges records reach; NormalizeNP reuses it
			MarkMerges(mergeMarker, reachCache, ov, recall.components, Dp, NP, recall.contourDistance, invComponents);
			NormalizeNP(NPfinal, Dp, NP, mergeMarker, reachCache, invComponents);

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
		//  Raster toolkit
		// ============================================================================

		/// <summary>
		/// The exact chessboard (Chebyshev) distance to the nearest pixel carrying `bit`.
		/// A forward pass over the four causal neighbors and a backward pass over the four
		/// anticausal neighbors give the exact distance in two sweeps, no queue.
		/// Distance is 0 on the seeds, rising outward.
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
				if (cand != kUnreached && cand + 1 < distance[idx])
					distance[idx] = cand + 1;
			};

			// forward: NW, N, NE, W
			for (int y = 0; y < height; ++y)
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

			// backward: SE, S, SW, E
			for (int y = height - 1; y >= 0; --y)
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
		/// What one ScanRingAt walk saw: whether any cell qualified, and whether the clamped
		/// window covered the whole component bounds, so no larger ring can add cells.
		/// </summary>
		struct RingScan { bool found; bool coveredBounds; };

		/// <summary>
		/// Walks the square perimeter of radius R about (ax, ay), clamped to the component
		/// bounds: the four edges, then the four corners, in a fixed cell order.  visit(j)
		/// receives each cell's linear index and returns whether that cell qualifies.
		/// The cell set at a radius never depends on how the ring was found, so a later pass
		/// may re-walk a ring an earlier search located, as long as its reduction does not
		/// depend on cell order.  Clamping can make a degenerate ring revisit cells, which is
		/// harmless because every visitor here accumulates idempotently.
		/// </summary>
		template <typename Visit>
		static RingScan ScanRingAt(const Component& c, const int ax, const int ay, const int R, const int width, Visit&& visit)
		{
			int xlo = ax - R;
			int xhi = ax + R;
			int ylo = ay - R;
			int yhi = ay + R;
			if (xlo < c.bounds.upperLeft.x)   xlo = c.bounds.upperLeft.x;
			if (xhi > c.bounds.bottomRight.x) xhi = c.bounds.bottomRight.x;
			if (ylo < c.bounds.upperLeft.y)   ylo = c.bounds.upperLeft.y;
			if (yhi > c.bounds.bottomRight.y) yhi = c.bounds.bottomRight.y;

			bool found = false;
			const auto cell = [&](const int col, const int row)
			{
				if (visit(row * width + col)) found = true;
			};

			for (int row = ylo + 1; row < yhi; ++row) cell(xlo, row);
			for (int row = ylo + 1; row < yhi; ++row) cell(xhi, row);
			for (int col = xlo + 1; col < xhi; ++col) cell(col, ylo);
			for (int col = xlo + 1; col < xhi; ++col) cell(col, yhi);
			cell(xlo, ylo); cell(xlo, yhi); cell(xhi, ylo); cell(xhi, yhi);

			return { 
				found,
			    xlo == c.bounds.upperLeft.x && xhi == c.bounds.bottomRight.x &&
			    ylo == c.bounds.upperLeft.y && yhi == c.bounds.bottomRight.y
			};
		}

		/// <summary>
		/// The ring search every component-local pass shares.  Grows ScanRingAt's ring from
		/// startR until a ring holds at least one qualifying cell (returns true and the radius
		/// in outRadius), or until the whole bounding box was scanned empty (returns false).
		/// Every qualifying cell on the found ring is visited, not just the nearest; do not
		/// replace this with a nearest-feature lookup, which changes the result and breaks
		/// parity with the reference weight files.  startR must be a proven lower bound, such
		/// as an exact distance transform value; a larger start would skip the true first ring.
		/// </summary>
		template <typename Visit>
		static bool FirstNonEmptyRing(const Component& c, const int ax, const int ay, const int width, Visit&& visit, int* outRadius = nullptr, const int startR = 0)
		{
			for (int R = startR; ; ++R)
			{
				const RingScan ring = ScanRingAt(c, ax, ay, R, width, visit);

				if (ring.found) { if (outRadius) *outRadius = R; return true; }
				if (ring.coveredBounds) return false;
			}

			return false; // Should never hit
		}

		// --- Thinning kernel --------------------------------------------------------

		/// <summary>
		/// The 8 neighbors of (x, y) on the `bit` layer packed into one byte, bits 0-7 holding
		/// P2 (north) through P9 (northwest) clockwise.  Out of bounds reads as background, so
		/// thinning runs in place on the real raster and a stroke on the image border still
		/// thins.
		/// </summary>
		static uint8_t Neighbors(const Mask& m, const int x, const int y, const uint8_t bit)
		{
			const int w = m.width;
			const int h = m.height;

			// Interior fast path: all eight neighbors are on the raster, so read them straight
			// off contiguous memory with no per-neighbor clamping.
			if (x > 0 && x < w - 1 && y > 0 && y < h - 1)
			{
				const uint8_t* d = m.data.data() + static_cast<size_t>(y) * w + x;
				const auto at = [&](const int offset) -> int { return (d[offset] & bit) ? 1 : 0; };

				return static_cast<uint8_t>(
					(at(-w)     << 0) |   // P2 north
					(at(-w + 1) << 1) |   // P3 northeast
					(at(1)      << 2) |   // P4 east
					(at(w + 1)  << 3) |   // P5 southeast
					(at(w)      << 4) |   // P6 south
					(at(w - 1)  << 5) |   // P7 southwest
					(at(-1)     << 6) |   // P8 west
					(at(-w - 1) << 7));   // P9 northwest
			}

			// Border path: an off-raster neighbor reads as background.
			const auto on = [&](const int xx, const int yy) -> int
			{ 
				return (xx >= 0 && xx < w && yy >= 0 && yy < h && (m(xx, yy) & bit)) ? 1 : 0;
			};

			return static_cast<uint8_t>(
				(on(x,     y - 1) << 0) |   // P2 north
				(on(x + 1, y - 1) << 1) |   // P3 northeast
				(on(x + 1, y    ) << 2) |   // P4 east
				(on(x + 1, y + 1) << 3) |   // P5 southeast
				(on(x,     y + 1) << 4) |   // P6 south
				(on(x - 1, y + 1) << 5) |   // P7 southwest
				(on(x - 1, y    ) << 6) |   // P8 west
				(on(x - 1, y - 1) << 7));   // P9 northwest
		}

		/// <summary>
		/// One sequential, in-place deletion pass over the whole raster.  A deleted pixel is
		/// seen by the pixels after it, the order the Lee-Chen Table 1 expects.
		/// </summary>
		static bool TablePass(Mask& s, const uint8_t bit, const std::array<uint8_t, 256>& table)
		{
			bool removed = false;
			const int w = s.width;
			const int h = s.height;
			
			for (int y = 0; y < h; ++y)
			{
				const int row = y * w;

				for (int x = 0; x < w; ++x)
				{
					const int i = row + x;
					if ((s[i] & bit) && table[Neighbors(s, x, y, bit)] == 0x00)
					{
						s[i] = static_cast<uint8_t>(s[i] & ~bit);
						removed = true;
					}
				}
			}

			return removed;
		}

		/// <summary>
		/// Thins the `bit` layer of the raster to the Lee-Chen skeleton, in place: Zhang-Suen
		/// erodes the boundary to a fixed point, then the Table 1 pass tidies it to a fixed
		/// point.  No padding is needed; the image frame reads as background.
		/// The Zhang-Suen sweeps run over an active frontier of boundary pixels, since an
		/// interior pixel can never be deleted and a deletion only exposes its own neighbors.
		/// Each sweep costs the shrinking boundary rather than the whole page, and the result
		/// is identical to sweeping the full raster.
		/// </summary>
		static void Thin(Mask& raster, const uint8_t bit)
		{
			const int w = raster.width;
			const int h = raster.height;
			const auto off = [&](const int x, const int y)
				{ return x < 0 || x >= w || y < 0 || y >= h || !(raster[static_cast<size_t>(y) * w + x] & bit); };

			// A boundary pixel has at least one of its eight neighbors off the layer.
			const auto boundary = [&](const int x, const int y)
			{
				return off(x, y - 1) || off(x + 1, y - 1) || off(x + 1, y) || off(x + 1, y + 1) ||
				       off(x, y + 1) || off(x - 1, y + 1) || off(x - 1, y) || off(x - 1, y - 1);
			};

			// A frontier cell carries its coordinates with the linear index, so the hot pass
			// never divides an index back into (x, y).
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

					if ((raster[i] & bit) && boundary(x, y))
					{
						frontier.push_back({ i, x, y });
						queued[i] = 1;
					}
				}
			}


			// One batched Zhang-Suen sub-pass over the frontier: mark, delete together, keep the
			// survivors, and queue the neighbors a deletion exposed.  Every cell tests the raster
			// before any deletion, so the pass is independent of frontier order.
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

		// Lee-Chen Table 1: the 256-entry simple-point deletion table, indexed by the packed
		// neighborhood.  0x00 deletes the pixel, 0xFF keeps it, and 0x01 marks a configuration
		// Zhang-Suen already removed, treated as keep.  Four entries differ from the published
		// table (0x0E, 0x45, 0x54, 0xE0); these reproduce the DIBCO reference weight files.
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

		// The two Zhang-Suen sub-iteration tables, built at compile time from skel::Rule.
		static constexpr std::array<uint8_t, 256> kZhangSuen1 = skel::Table(1);
		static constexpr std::array<uint8_t, 256> kZhangSuen2 = skel::Table(2);

		/// <summary>
		/// Guarantees every component keeps at least one skeleton pixel when thinning erodes a
		/// small blob to nothing.  The seed lands one pixel down and right of the component's
		/// integer mean position when that pixel is foreground, and on the mean itself
		/// otherwise, matching the reference weight files.
		/// </summary>
		static void EnsureComponentSeeds(Mask& skeleton, const uint8_t bit, const Components& components)
		{
			const int width = skeleton.width;
			const int height = skeleton.height;

			// Find the skeleton-less components first, against the raster as thinned: a seed may
			// land outside its own component and must not suppress another component's seeding.
			std::vector<const Component*> needSeed;
			for (const Component& c : components)
			{
				bool hasSkeleton = false;
				for (int y = c.bounds.upperLeft.y; y <= c.bounds.bottomRight.y && !hasSkeleton; ++y)
				{
					for (int x = c.bounds.upperLeft.x; x <= c.bounds.bottomRight.x; ++x)
					{
						const size_t i = static_cast<size_t>(y) * width + x;
						if (components.labels[i] == c.label && (skeleton[i] & bit))
						{
							hasSkeleton = true;
							break;
						}
					}
				}

				if (!hasSkeleton) needSeed.push_back(&c);
			}

			for (const Component* seedless : needSeed)
			{
				const Component& c = *seedless;

				long long sumX = 0;
				long long sumY = 0;
				long long count = 0;

				for (int y = c.bounds.upperLeft.y; y <= c.bounds.bottomRight.y; ++y)
					for (int x = c.bounds.upperLeft.x; x <= c.bounds.bottomRight.x; ++x)
						if (components.labels[static_cast<size_t>(y) * width + x] == c.label)
						{ 
							sumX += x; sumY += y; ++count; 
						}

				const int mx = static_cast<int>(sumX / count);   // integer mean position (x)
				const int my = static_cast<int>(sumY / count);   // integer mean position (y)
				// Seed one pixel down-and-right of the mean when that pixel is foreground (the
				// DIBCO reference convention), else at the mean itself.
				const int cx = mx + 1;
				const int cy = my + 1;
				if (cx < width && cy < height && components.labels[static_cast<size_t>(cy) * width + cx] != 0)
					skeleton[static_cast<size_t>(cy) * width + cx] |= bit;
				else
					skeleton[static_cast<size_t>(my) * width + mx] |= bit;
			}
		}

		// ============================================================================
		//  The pseudo-Recall pipeline
		// ============================================================================

		/// <summary>
		/// D for the foreground (Eq. 2, Fig. 11c): the contour distance transform masked to the
		/// ink, except that a contour pixel that is also skeleton reads 1, then the medial-ridge
		/// adjustment.
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
		/// From the distance map D and the skeleton, the medial factor along the skeleton and
		/// the normalization NR (Eq. 3): the largest weighted distance across the local stroke
		/// cross section, then a propagation along the stroke so each break in it is penalized
		/// equally.
		/// </summary>
		static void MedialNormalization(Bytes& medialFactor, Words& NR, const Bytes& D, const Mask& overlay, const Components& components)
		{
			Bytes skeletonDistance;
			SkeletonDistance(skeletonDistance, D, overlay);

			// MedialFactor and Normalization ring the same skeleton about the same centers to the
			// same radius.  MedialFactor grows the ring and records the radius it found here;
			// Normalization, an order-free max, re-walks just that ring instead of regrowing.
			Words ringRadius(D.width, D.height, kUnreached);
			MedialFactor(medialFactor, D, skeletonDistance, overlay, components, ringRadius);
			Normalization(NR, D, medialFactor, overlay, components, ringRadius);
		}

		/// <summary>
		/// The chessboard distance from each pixel to the nearest skeleton point, masked to the
		/// pixels carrying a distance.  A skeleton pixel off the contour reads 1; a skeleton
		/// pixel on the contour reads 0.
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
		/// The medial factor along the skeleton, whose product with D realizes NR (Eq. 3).
		/// Skeleton pixels start at 1.  Every pixel carrying a distance then writes to each
		/// skeleton pixel on the first non-empty ring of its component window: that pixel's own
		/// distance, plus one when the writer sits at least that far from the skeleton.  Later
		/// writers win, in component, row, column order, and that order is part of the result.
		/// Finally, each termination point of the skeleton inherits its lone neighbor's factor
		/// plus one.
		/// </summary>
		static void MedialFactor(Bytes& factor, const Bytes& D, const Bytes& skeletonDistance, const Mask& overlay, const Components& components, Words& ringRadius)
		{
			const int width = D.width;
			const int height = D.height;
			const int size = D.Size();
			factor.Resize(width, height, 0);
			for (int i = 0; i < size; ++i) factor[i] = (overlay[i] & kSkeleton) ? 1 : 0;   // skeleton pixels = 1, else 0

			// Cross-section pass: each center writes the skeleton pixels on its first non-empty
			// ring.  The traversal order is part of the result; do not convert this scatter into
			// a per-skeleton gather.  The found radius is recorded for Normalization to re-walk.
			components.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				const uint8_t d = D[i];
				if (!HasDistance(d)) return;

				const uint8_t reach = skeletonDistance[i];
				// Skip the empty inner rings: for a non-skeleton center, reach is the exact
				// distance to the nearest skeleton, a proven lower bound on the first ring; a
				// skeleton center hits itself at radius 0, so start there.
				const int startR = (overlay[i] & kSkeleton) ? 0 : reach;
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

			// Endpoint pass: termination points inherit their lone neighbor's factor plus one.
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!(overlay[i] & kSkeleton)) return;

				const int v = TerminationPointFactor(factor, overlay, x, y, width, height);
				if (v > 0) factor[i] = static_cast<uint8_t>(v + 1);
			});
		}

		/// <summary>
		/// NR, Normalization type I (Eq. 3, Fig. 7): for each pixel carrying a distance, the
		/// largest weighted distance over the skeleton pixels on the first non-empty ring of
		/// its component window; then a propagation pass spreads a stroke's peak along it, so a
		/// break is penalized equally regardless of the local stroke width.
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
					if (!(overlay[j] & kSkeleton)) return false;

					const int v = static_cast<int>(D[j]) * static_cast<int>(factor[j]);
					if (v > best) best = v;

					return true;
				});

				NR[i] = static_cast<uint16_t>(best);
			});

			// Propagation: a pixel whose NR differs from all four set neighbors inherits its left
			// neighbor's NR, which may already be updated this sweep, spreading the peak cross
			// section along the stroke.
			components.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				if (PropagateAlongStroke(NR, x, y, width, height)) NR[i] = NR[i - 1];
			});
		}

		/// <summary>
		/// The medial-ridge value of D.  The paper's D is the raw contour distance; on the
		/// skeleton ridge the true medial radius is one more.  Raises a skeleton pixel's D by 1
		/// when it equals all four border-clamped neighbors, a flat ridge.  In place, in
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

		/// <summary>
		/// The Lee-Chen termination point: a skeleton pixel with exactly one skeleton neighbor
		/// among its eight, border clamped.  Returns that neighbor's medial factor, or -1 when
		/// the pixel is not a termination point.  The bottom-right neighbor's factor is read
		/// from a shifted position; the asymmetry is preserved for parity with the reference
		/// weight files.
		/// </summary>
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

			hit(up   + col,     up   + col);       // top
			hit(down + col,     down + col);       // bottom
			hit(mid  + col + A, mid  + col + A);   // left
			hit(mid  + col + B, mid  + col + B);   // right
			hit(up   + col + A, up   + col + A);   // top-left
			hit(down + col + B, down + B);         // bottom-right: the factor read omits the column, the preserved asymmetry
			hit(down + col + A, down + col + A);   // bottom-left
			hit(up   + col + B, up   + col + B);   // top-right

			return (count == 1) ? last : -1;
		}

		/// <summary>
		/// The NR propagation predicate: true when all four border-clamped neighbors carry a
		/// normalization and the center differs from every one of them.
		/// </summary>
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

		/// <summary>
		/// The foreground stroke width Gsw_fg per component (Fig. 15a): twice the floored mean
		/// medial factor over the component's skeleton, stored on each Component for the
		/// precision side.
		/// </summary>
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
		//  The pseudo-Precision pipeline
		// ============================================================================

		/// <summary>
		/// The Gsw_bg region (Eq. 10, Fig. 15b): the background inside any component's bounding
		/// box dilated by twice its stroke width on every side, clamped to the image.  Beyond
		/// every such box the strokes do not reach and PW stays 1.
		/// </summary>
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
		/// The radius at which a square window grown about (x, y), clamped to the image, first
		/// covers the whole of bounds b, or a value past any in-image distance when it never
		/// does.  An interior side is met at exactly one radius; a side on the image border is
		/// held by the clamp from some radius on.  The window fills the box only when the exact
		/// sides agree and every border side is reached.
		/// </summary>
		static int BoxFillRadius(const int x, const int y, const Region& b, const int width, const int height)
		{
			const int never = width + height;                       // beyond any in-image Chebyshev distance
			int fixed = -1, lower = 0;
			bool consistent = true;

			const auto side = [&](const bool onBorder, const int k)
			{
				if (onBorder) { if (k > lower) lower = k; }
				else if (fixed < 0) fixed = k;
				else if (fixed != k) consistent = false;
			};

			side(b.upperLeft.x   == 0,          x - b.upperLeft.x);
			side(b.bottomRight.x == width - 1,  b.bottomRight.x - x);
			side(b.upperLeft.y   == 0,          y - b.upperLeft.y);
			side(b.bottomRight.y == height - 1, b.bottomRight.y - y);

			if (!consistent) return never;

			const int r = (fixed >= 0) ? fixed : lower;
			return (r >= lower) ? r : never;
		}

		/// <summary>
		/// D for the background (Eq. 10): each background pixel's distance to the same
		/// ground-truth contour, inside the Gsw_bg region only; beyond the region the
		/// out-of-region marker stands for PW = 1, and ink stays 0.  A pixel whose window fills
		/// its whole background component before reaching a contour reads 0, as in a one-pixel
		/// hole.  Then the medial-ridge adjustment on the background skeleton.
		/// </summary>
		static void BackgroundDistanceMap(Bytes& Dp, const Mask& overlay, const Mask& bg, const Mask& region, const Words& contourDistance, const Components& invComponents)
		{
			const int width = overlay.width;
			const int height = overlay.height;
			Dp.Resize(width, height, 0);
			                                          // ink (unlabeled) stays 0
			invComponents.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!region[i]) { Dp[i] = kOutsideRegion; return; }                    // beyond the stroke reach
				const int d = contourDistance[i];                                      // distance to nearest contour
				Dp[i] = (BoxFillRadius(x, y, c.bounds, width, height) < d) ? 0 : static_cast<uint8_t>(d);
			});

			MedialRidgeAdjust(Dp, bg, invComponents);
		}

		/// <summary>
		/// The first precision normalization pass and its only ring search (Eq. 11).  Each
		/// in-region background pixel rings the ground-truth contour, starting at its exact
		/// contour distance.  The widest stroke width found on the ring becomes the pixel's
		/// stroke reach, cached for NormalizeNP.  A pixel farther out than its reach stays
		/// unmarked; within reach, a ring touching two different components marks the merging
		/// case of Fig. 14 with the pixel's background normalization.
		/// </summary>
		static void MarkMerges(Bytes& mergeMarker, Words& reachCache, const Mask& overlay, const Components& components, const Bytes& Dp, const Words& NP, const Words& contourDistance, const Components& invComponents)
		{
			const int width = Dp.width;

			invComponents.ForEachPixel([&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(Dp[i])) return;

				int reach = -1;
				int firstLabel = -1;
				bool adjacent = false;

				const bool found = FirstNonEmptyRing(c, x, y, width, [&](const int j)
				{
					if (!(overlay[j] & kContour)) return false;
					const int L = components.labels[j];                            // contour pixel -> its component
					const int v = components.items[L].strokeWidth & 0xFF;          // its Gsw_fg (low byte, as stored)

					if (v > reach) reach = v;

					if (firstLabel < 0) firstLabel = L;
					else if (L != firstLabel) adjacent = true;

					return true;
				}, nullptr, contourDistance[i]);

				reachCache[i] = found ? static_cast<uint16_t>(reach) : kUnreached;
				if (!found || Dp[i] > reach) return;                               // beyond the stroke reach: unmarked

				mergeMarker[i] = static_cast<uint8_t>((adjacent ? NP[i] : 0) & 0xFF);
			});
		}

		/// <summary>
		/// The second precision normalization pass: NP = min(Gc_sw, Gsw_bg) (Eq. 11), pure
		/// per-pixel arithmetic over MarkMerges' caches, no ring search.  Within the stroke
		/// reach, a pixel takes the inter-component gap when a merge was marked nearby and the
		/// gap is the smaller, and the stroke reach otherwise.
		/// </summary>
		static void NormalizeNP(Bytes& NPfinal, const Bytes& Dp, const Words& NP, const Bytes& mergeMarker, const Words& reachCache, const Components& invComponents)
		{
			const int width = Dp.width;
			const int height = Dp.height;

			invComponents.ForEachPixel([&](const Component&, int x, int y, int i)
			{
				if (!HasDistance(Dp[i])) return;

				const uint16_t cached = reachCache[i];
				if (cached == kUnreached) return;   // MarkMerges found no contour

				const int reach = cached;
				const int dp = Dp[i];
				if (dp > reach) return;

				const int np = NP[i];  // integer-valued (sqrt-rounded above)
				const bool merging = AnyWithin(mergeMarker, x, y, reach - dp, width, height);
				NPfinal[i] = static_cast<uint8_t>(((merging && np < reach) ? np : reach) & 0xFF);
			});
		}

		/// <summary>
		/// True when any nonzero pixel of map lies within Chebyshev distance radius of
		/// (col, row), over the image-clamped square window.  A radius of 0 finds nothing.
		/// </summary>
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
