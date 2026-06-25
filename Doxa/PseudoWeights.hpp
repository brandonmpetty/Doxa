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
	/// The paper defines the weights symmetrically about the ground-truth text
	/// contour: pseudo-Recall weights the FOREGROUND by its distance from the
	/// contour, normalised by the local stroke width (Fig. 10); pseudo-Precision
	/// weights the BACKGROUND by its distance from that SAME contour, normalised
	/// by the distance to the nearest neighbouring component (Fig. 15).  So both
	/// measures run one pipeline -- distance-from-contour, then a stroke-width
	/// normalisation along the line normal to the skeleton -- once on the
	/// foreground and once on the (inverted) background.  Generate() exploits this:
	/// it computes the recall side once and reuses its contour, distance map,
	/// skeleton normalisation and component labelling for the precision side.
	///
	/// Vocabulary, following the paper's Section III:
	///   D    = Chebyshev distance map from the contour points        (Eq. 2, Fig. 10c)
	///   S    = skeleton of the ground-truth text                     (Fig. 10b)
	///   Gsw  = stroke-width image (2R+1 at the skeleton)             (Fig. 10e)
	///   NR   = Normalization type I, so D sums to 1 along the cross  (Eq. 3, Fig. 7)
	///   GW   = D / NR                                                (Eq. 2)
	///   Gsw_bg = background region reached by a component's stroke   (Eq. 10, Fig. 15b)
	///   NP   = min(Gc_sw, Gsw_bg) background normalisation           (Eq. 11)
	///   PW   = 1 + D / NP                                            (Eq. 10)
	///
	/// The paper leaves several implementation details unspecified; where it does,
	/// the code below says so and describes the choice made (the medial-ridge value
	/// of D, the realisation of NR for real strokes, padding, and empty-skeleton
	/// seeding).  The skeleton itself follows the paper's reference [60] = Lee, Chen,
	/// "Recognition of handwritten Chinese characters via short line segments,"
	/// Pattern Recognition 25(5), 1992; the skeleton helpers are documented in that
	/// paper's terms (Table 1 look-up, termination/fork points).
	///
	/// Self-contained but for two collaborators: ConnectedComponents (the labelling
	/// Gcc) and Thinning (Zhang-Suen + the Table-1 look-up).  Everything else --
	/// the chessboard distance transform and every weighting pass -- lives here.
	/// </summary>
	class PseudoWeights
	{
	public:
		/// <summary>
		/// Both weight maps.  gw is GW(x,y) (Eq. 2); pw is the stored precision
		/// weight PW(x,y) - 1 = D/NP capped at 2 (Eq. 10/11), which is the value
		/// ClassifiedPerformance consumes -- the full pseudo-Precision weight is
		/// pw + 1.  foreground selects the ink value (Palette::Black for DIBCO
		/// ground truth).  The recall chain is computed once and reused by the
		/// precision side, so this is the efficient way to obtain both.
		/// </summary>
		static void Generate(
			std::vector<double>& gw,
			std::vector<double>& pw,
			const Image& groundTruth,
			const Pixel8 foreground = Palette::Black)
		{
			const RecallArtifacts recall = ComputeRecall(gw, groundTruth, foreground);
			ComputePrecision(pw, recall, foreground);
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
		/// simply runs Generate and keeps the precision map; prefer Generate when
		/// both maps are wanted.
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
		// "Not yet reached" in a chessboard sweep; no real distance approaches it,
		// so the +1 relaxation never overflows.
		static constexpr uint16_t kUnreached = 0xFFFF;

		// 250: the marker for a background pixel beyond every component's stroke
		// reach -- outside the Gsw_bg region, where the paper sets PW = 1 (Eq. 10),
		// i.e. the stored weight is 0.  Distances this large never occur on real
		// strokes, so the value doubles as an "outside the weight domain" sentinel.
		static constexpr uint8_t kOutsideRegion = 0xFA;

		// A pixel carries a usable distance when D is in [1, 249]: nonzero (it is in
		// the weight domain -- foreground for recall, in-region background for
		// precision) and below the out-of-region marker.
		static bool HasDistance(const uint8_t d) { return d != 0 && d < kOutsideRegion; }

		// Release a buffer's memory immediately rather than at scope end -- used to keep
		// the precision peak down by freeing each intermediate at its last use.
		template <typename V> static void Release(V& v) { V().swap(v); }

		/// <summary>
		/// The recall-side products the precision side reuses.  The two measures
		/// share the contour, its distance transform, the skeleton normalisation and
		/// the component labelling (the precision contour IS the recall contour --
		/// the single ground-truth text boundary, Eq. 10/11), so the recall pass
		/// hands them on rather than recomputing them.
		/// </summary>
		struct RecallArtifacts
		{
			int                   width = 0;
			int                   height = 0;
			std::vector<uint8_t>  fg;               // foreground mask (1 = ink)
			Components            components;        // Gcc labelling (Eq. 4-5, 12-17)
			std::vector<uint8_t>  skeleton;          // S(x,y) (Fig. 10b)
			std::vector<uint8_t>  contour;           // contour points (Fig. 10b)
			std::vector<uint16_t> contourDistance;   // chessboard transform of the contour, reused for the background D
			std::vector<uint8_t>  medialFactor;      // the per-skeleton factor whose product with D realises NR
		};

		/// <summary>
		/// Pseudo-Recall pipeline (Eq. 2-3).  D = distance from the contour; the
		/// medial normalisation NR along the line normal to the skeleton; GW = D/NR.
		/// Fills gw and returns the artifacts the precision side reuses.
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
			recall.width = width;
			recall.height = height;

			recall.fg.assign(size, 0);
			for (int i = 0; i < size; ++i) recall.fg[i] = (groundTruth.data[i] == foreground) ? 1 : 0;

			recall.components = ConnectedComponents::Generate(groundTruth, foreground, /*8-conn*/ true);

			Skeletonize(recall.skeleton, recall.fg, width, height);
			EnsureComponentSeeds(recall.skeleton, recall.components, width, height);

			Contour(recall.contour, recall.fg, width, height);
			ChebyshevDistance(recall.contourDistance, recall.contour, width, height);

			std::vector<uint8_t> D;
			ForegroundDistanceMap(D, recall.fg, recall.contour, recall.contourDistance, recall.skeleton, recall.components, width, height);

			std::vector<uint16_t> NR;
			MedialNormalization(recall.medialFactor, NR, D, recall.contour, recall.skeleton, recall.components, width, height);

			// GW = D / NR (Eq. 2).  EnsureComponentSeeds guarantees a skeleton per
			// component, so NR > 0 at every ink pixel; the NR != 0 guard is then only
			// defense-in-depth (a 0 weight is saner than an inf were NR ever 0).
			gw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
				if (D[i] != 0 && NR[i] != 0) gw[i] = static_cast<double>(D[i]) / static_cast<double>(NR[i]);

			return recall;
		}

		/// <summary>
		/// Pseudo-Precision pipeline (Eq. 9-11).  The background is weighted by its
		/// distance from the ground-truth contour, normalised so the weight grows
		/// toward the midline between neighbouring components and is capped where a
		/// component's stroke no longer reaches (Eq. 10).  Runs the same
		/// distance/normalisation machinery as recall, on the inverted image, then
		/// combines it with the recall-side stroke widths.
		/// </summary>
		static void ComputePrecision(
			std::vector<double>& pw,
			const RecallArtifacts& recall,
			const Pixel8 foreground)
		{
			const int width = recall.width;
			const int height = recall.height;
			const int size = width * height;
			const Pixel8 background = (foreground == Palette::Black) ? Palette::White : Palette::Black;

			// Gsw_fg per component, and the Gsw_bg region it reaches into the
			// background (Fig. 15a-b).
			std::vector<int> componentStrokeWidth;     // Gsw_fg per label
			std::vector<uint8_t> strokeWidthMap;       // Gsw_fg stamped over each component's ink
			ComponentStrokeWidths(strokeWidthMap, componentStrokeWidth, recall.medialFactor, recall.skeleton, recall.components, width, height);

			std::vector<uint8_t> region;               // Gsw_bg region (Eq. 10, Fig. 15b)
			BackgroundStrokeRegion(region, recall.fg, componentStrokeWidth, recall.components, width, height);

			// The inverted image: foreground becomes background and vice versa, so a
			// CC labelling and a skeleton of the background can be taken with the same
			// tools.  Each intermediate is released (below) at its last use to keep the
			// precision peak down.
			std::vector<uint8_t> invFg(size);
			for (int i = 0; i < size; ++i) invFg[i] = recall.fg[i] ? 0 : 1;

			// Label the background.  The inverted image is needed only to label, so it
			// is scoped to free as soon as the labelling is done.
			Components invComponents;
			{
				Image inverted(width, height);
				for (int i = 0; i < size; ++i) inverted.data[i] = recall.fg[i] ? background : foreground;
				invComponents = ConnectedComponents::Generate(inverted, foreground, /*8-conn*/ true);
			}

			// Skeleton of the background.  The image border is treated as background
			// (the rest of Doxa's thinning/distance code does likewise), so the inverted
			// frame is zeroed before skeletonising; that framed copy is scoped to free
			// once thinning is done.
			std::vector<uint8_t> invSkeleton;
			{
				std::vector<uint8_t> invFrame = invFg;
				for (int x = 0; x < width; ++x) { invFrame[x] = 0; invFrame[static_cast<size_t>(height - 1) * width + x] = 0; }
				for (int y = 0; y < height; ++y) { invFrame[static_cast<size_t>(y) * width] = 0; invFrame[static_cast<size_t>(y) * width + width - 1] = 0; }
				Skeletonize(invSkeleton, invFrame, width, height);
			}
			EnsureComponentSeeds(invSkeleton, invComponents, width, height);

			// D for the background, measured from the SAME ground-truth contour
			// (Eq. 10), gated to the Gsw_bg region (beyond it, the sentinel marks
			// PW = 1).  The contour distance transform is reused from the recall pass.
			std::vector<uint8_t> Dp;
			BackgroundDistanceMap(Dp, invFg, region, recall.contour, recall.contourDistance, invSkeleton, invComponents, width, height);
			Release(invFg);    // only the Dp gate needed it
			Release(region);   // only Dp needed it

			// The background medial normalisation, same routine as recall.  It
			// accumulates an area (~R^2); NP per Eq. 11 is a stroke width, so take the
			// square root back to a radius at every in-region background pixel.
			std::vector<uint8_t> invMedialFactor;
			std::vector<uint16_t> NP;
			MedialNormalization(invMedialFactor, NP, Dp, recall.contour, invSkeleton, invComponents, width, height);
			WalkComponents(invComponents, width, [&](const Component&, int, int, int i)
			{
				if (HasDistance(Dp[i])) NP[i] = static_cast<uint16_t>(std::floor(std::sqrt(static_cast<double>(NP[i])) + 0.5));
			});
			Release(invMedialFactor);   // written by MedialNormalization, never read again
			Release(invSkeleton);       // last used by MedialNormalization

			// NP = min(Gc_sw, Gsw_bg) (Eq. 11), realised with two component-local ring
			// passes over the background: the first marks where adjacent components
			// meet (the character-merging case, Fig. 14d), the second uses the
			// inter-component gap there and the stroke reach elsewhere.
			std::vector<uint8_t> mergeMarker(size, 0), NPfinal(size, 0);
			PrecisionNormalizationPass(mergeMarker, PrecisionPass::MarkMerges, strokeWidthMap, recall.contour, recall.components.labels, Dp, NP, mergeMarker, invComponents, width, height);
			PrecisionNormalizationPass(NPfinal, PrecisionPass::Normalize, strokeWidthMap, recall.contour, recall.components.labels, Dp, NP, mergeMarker, invComponents, width, height);
			Release(NP);          // both passes done
			Release(mergeMarker); // consumed by the Normalize pass

			// Stored precision weight = PW - 1 = D/NP, capped at 2 (Eq. 10).
			pw.assign(size, 0.0);
			for (int i = 0; i < size; ++i)
			{
				if (NPfinal[i] == 0) continue;
				const double v = static_cast<double>(Dp[i]) / NPfinal[i];
				pw[i] = (v > 2.0) ? 2.0 : v;
			}
		}

		// ---- shared pipeline ---------------------------------------------------------

		/// <summary>
		/// The medial normalisation shared by both measures: from the distance map D
		/// and the skeleton, produce the per-skeleton medial factor and the
		/// normalisation NR (Eq. 3 / Normalization type I).  The paper specifies NR
		/// in closed form only for ideal cross-sections (Eq. 3); for real strokes it
		/// is realised here as the distance-to-skeleton driven factor, the maximal
		/// D*factor along the local cross-section, and a propagation along the stroke
		/// so each break is penalised equally regardless of local width (the paper's
		/// stated intent, Section III-A).
		/// </summary>
		static void MedialNormalization(
			std::vector<uint8_t>& medialFactor,
			std::vector<uint16_t>& NR,
			const std::vector<uint8_t>& D,
			const std::vector<uint8_t>& contour,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			std::vector<uint8_t> skeletonDistance;
			SkeletonDistance(skeletonDistance, D, contour, skeleton, width, height);
			MedialFactor(medialFactor, D, skeletonDistance, skeleton, components, width, height);
			Normalization(NR, D, medialFactor, skeleton, components, width, height);
		}

		/// <summary>
		/// Visits every label-owned pixel of every component in component -> row ->
		/// column order, passing the component, the (x,y) and the linear index i.
		/// This order matters for the in-place passes below (a pixel sees its
		/// already-updated up/left neighbours), and the per-component window is
		/// clamped to the component's own bounds.  Shared by every component-local
		/// pass.
		/// </summary>
		template <typename Visitor>
		static void WalkComponents(const Components& components, const int width, Visitor&& visit)
		{
			for (const Component& c : components)
			{
				const int x0 = c.bounds.upperLeft.x,  x1 = c.bounds.bottomRight.x;
				const int y0 = c.bounds.upperLeft.y,  y1 = c.bounds.bottomRight.y;
				for (int y = y0; y <= y1; ++y)
				{
					const int row = y * width;
					for (int x = x0; x <= x1; ++x)
					{
						const int i = row + x;
						if (components.labels[i] == c.label) visit(c, x, y, i);
					}
				}
			}
		}

		/// <summary>
		/// The one ring scan every component-local worker shares.  Grows a square
		/// window R = 0,1,2..., clamped to the component bbox, scanning only the
		/// outer ring at each R; calls visit(j) for each ring cell (j = its linear
		/// index), where visit returns true if that cell qualifies (carries the
		/// feature being sought).  Stops at the first R whose ring has at least one
		/// qualifying cell (returns true), or when the full bbox has been scanned
		/// with none (returns false).  Per-cell work and accumulation live in the
		/// visitor; clamping makes a degenerate ring revisit cells, which is harmless
		/// because every visitor's accumulation is idempotent (a write of a fixed
		/// value, a max, or a set-membership test).
		///
		/// IMPORTANT: this is NOT a nearest-feature lookup.  It aggregates over EVERY
		/// feature on the first non-empty ring (all equidistant pixels participate) and
		/// the ring is clamped to the component bbox.  Do not "optimise" it into a
		/// Voronoi / nearest-owner map: that picks one tie-broken owner instead of the
		/// whole ring and changes the result -- the output must stay bit-exact with the
		/// DIBCO reference weight files.
		/// </summary>
		template <typename Visit>
		static bool FirstNonEmptyRing(
			const Component& c,
			const int ax, const int ay,
			const int width, const int height,
			Visit&& visit)
		{
			const int bxmin = c.bounds.upperLeft.x,  bxmax = c.bounds.bottomRight.x;
			const int bymin = c.bounds.upperLeft.y,  bymax = c.bounds.bottomRight.y;

			for (int R = 0; ; ++R)
			{
				bool found = false;
				int xlo = ax - R, xhi = ax + R, ylo = ay - R, yhi = ay + R;
				if (xlo < bxmin) xlo = bxmin;  if (xhi > bxmax) xhi = bxmax;
				if (ylo < bymin) ylo = bymin;  if (yhi > bymax) yhi = bymax;

				const auto cell = [&](const int col, const int row) { if (visit(row * width + col)) found = true; };
				for (int row = ylo + 1; row < yhi; ++row) cell(xlo, row);
				for (int row = ylo + 1; row < yhi; ++row) cell(xhi, row);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, ylo);
				for (int col = xlo + 1; col < xhi; ++col) cell(col, yhi);
				cell(xlo, ylo); cell(xlo, yhi); cell(xhi, ylo); cell(xhi, yhi);

				if (found) return true;
				if (xlo == bxmin && xhi == bxmax && ylo == bymin && yhi == bymax) return false;
			}
		}

		/// <summary>
		/// Exact chessboard (Chebyshev) distance to the nearest seed (seed == nonzero
		/// in the feature map).  A forward raster pass over the four causal
		/// neighbours then a backward pass over the four anticausal neighbours yields
		/// the exact chessboard distance in one allocation, no queue.  Distance is 0
		/// on the seeds, rising outward.  Used for D (feature = contour) and for the
		/// distance-to-skeleton factor (feature = skeleton).
		/// </summary>
		static void ChebyshevDistance(
			std::vector<uint16_t>& distance,
			const std::vector<uint8_t>& feature,
			const int width,
			const int height)
		{
			const int size = width * height;
			distance.assign(size, 0);
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
		/// (the contour points of Fig. 10b).  The frame is treated as background, so
		/// an edge pixel touches "outside".
		/// </summary>
		static void Contour(
			std::vector<uint8_t>& contour,
			const std::vector<uint8_t>& fg,
			const int width,
			const int height)
		{
			contour.assign(static_cast<size_t>(width) * height, 0);
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
		/// The medial-ridge value of D.  The paper's D is the raw contour distance
		/// (Fig. 10c); the paper does not specify D on the skeleton ridge, where the
		/// true medial radius is one beyond the contour distance.  This raises a
		/// skeleton pixel's D by 1 when it equals all four border-clamped
		/// 4-neighbours (a flat ridge).  In place, in component order.
		/// </summary>
		static void MedialRidgeAdjust(
			std::vector<uint8_t>& D,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			WalkComponents(components, width, [&](const Component&, int x, int y, int i)
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
		/// distance-to-skeleton: the chessboard distance from each pixel to the
		/// nearest skeleton point, with skel&amp;!contour -> 1 (skel&amp;contour stays 0
		/// via the self-hit), masked to pixels carrying a distance.  Together with D
		/// it brackets the local half-stroke and drives the per-skeleton factor.
		/// </summary>
		static void SkeletonDistance(
			std::vector<uint8_t>& skeletonDistance,
			const std::vector<uint8_t>& D,
			const std::vector<uint8_t>& contour,
			const std::vector<uint8_t>& skeleton,
			const int width,
			const int height)
		{
			const int size = width * height;
			std::vector<uint16_t> distance;
			ChebyshevDistance(distance, skeleton, width, height);

			skeletonDistance.assign(size, 0);
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
		/// factor[q] = D[q] + (skeletonDistance[centre] >= D[q] ? 1 : 0) for each
		/// skeleton q on that ring (component -> row -> column order, last writer
		/// wins); (endpoint) every skeleton pixel that is a Lee-Chen termination
		/// point (exactly one skeleton neighbour, Fig. 3a) inherits that neighbour's
		/// factor + 1, extending the normalisation to the curve end.
		/// </summary>
		static void MedialFactor(
			std::vector<uint8_t>& factor,
			const std::vector<uint8_t>& D,
			const std::vector<uint8_t>& skeletonDistance,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			factor = skeleton;   // skeleton pixels = 1, else 0

			// cross-section pass: each centre writes the skeleton pixels on its first
			// non-empty ring (idempotent per cell, so last-writer-wins across centres).
			// Intentional scatter-write: the component -> row -> column traversal order
			// is part of the result.  Do not convert it to a per-skeleton-pixel gather.
			WalkComponents(components, width, [&](const Component& c, int x, int y, int i)
			{
				const uint8_t d = D[i];
				if (!HasDistance(d)) return;
				const uint8_t reach = skeletonDistance[i];
				FirstNonEmptyRing(c, x, y, width, height, [&](const int j)
				{
					if (!skeleton[j]) return false;
					const uint8_t dq = D[j];
					factor[j] = static_cast<uint8_t>(reach >= dq ? dq + 1 : dq);
					return true;
				});
			});

			// endpoint pass
			WalkComponents(components, width, [&](const Component&, int x, int y, int i)
			{
				if (!skeleton[i]) return;
				const int v = TerminationPointFactor(factor, skeleton, x, y, width, height);
				if (v > 0) factor[i] = static_cast<uint8_t>(v + 1);
			});
		}

		/// <summary>
		/// NR(x,y) -- Normalization type I (Eq. 3, Fig. 7).  For each pixel with a
		/// distance, the MAX of D*factor over the skeleton pixels on the first
		/// non-empty ring of its component window (the cross-section value); then a
		/// propagation pass spreads a stroke's peak along it, so a break is penalised
		/// equally regardless of the local stroke width.
		/// </summary>
		static void Normalization(
			std::vector<uint16_t>& NR,
			const std::vector<uint8_t>& D,
			const std::vector<uint8_t>& factor,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			// NR only ever holds integers: max(D*factor) (<= ~64000, fits uint16) and
			// copies of it.  Stored as uint16 (not double) to halve the footprint; the
			// single floating-point step, GW = D/NR, casts at the point of use.
			NR.assign(static_cast<size_t>(width) * height, 0);

			WalkComponents(components, width, [&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				int best = -1;
				const bool found = FirstNonEmptyRing(c, x, y, width, height, [&](const int j)
				{
					if (!skeleton[j]) return false;
					const int v = static_cast<int>(D[j]) * static_cast<int>(factor[j]);
					if (v > best) best = v;
					return true;
				});
				NR[i] = found ? static_cast<uint16_t>(best) : 0;
			});

			// propagation: a pixel whose NR differs from all four (set) clamped
			// neighbours inherits its left neighbour's NR (which may already be
			// updated this sweep), spreading the peak cross-section along the stroke.
			WalkComponents(components, width, [&](const Component&, int x, int y, int i)
			{
				if (!HasDistance(D[i])) return;
				if (PropagateAlongStroke(NR, x, y, width, height)) NR[i] = NR[i - 1];
			});
		}

		/// <summary>
		/// Guarantees every component owns at least one skeleton pixel when thinning
		/// left it empty -- e.g. a small symmetric blob the look-up pass erodes to
		/// nothing.  The paper assumes a non-empty S(x,y) per component; this forces
		/// the (rounded) centroid pixel, falling back to the raster-first seed if the
		/// centroid lands off a non-convex blob.  So no component is ever
		/// skeleton-less and NR is never 0 at a pixel carrying a distance.
		/// </summary>
		static void EnsureComponentSeeds(
			std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			const int n = static_cast<int>(components.items.size());
			std::vector<uint8_t> hasSkeleton(n, 0);
			std::vector<uint64_t> sumX(n, 0), sumY(n, 0), count(n, 0);
			for (int y = 0; y < height; ++y)
			{
				const int row = y * width;
				for (int x = 0; x < width; ++x)
				{
					const int i = row + x;
					const int L = components.labels[i];
					if (!L) continue;
					sumX[L] += x; sumY[L] += y; ++count[L];
					if (skeleton[i]) hasSkeleton[L] = 1;
				}
			}
			for (const Component& c : components)
			{
				const int L = c.label;
				if (hasSkeleton[L]) continue;
				const int cx = static_cast<int>(std::llround(static_cast<double>(sumX[L]) / count[L]));
				const int cy = static_cast<int>(std::llround(static_cast<double>(sumY[L]) / count[L]));
				if (cx >= 0 && cx < width && cy >= 0 && cy < height &&
					components.labels[static_cast<size_t>(cy) * width + cx] == L)
					skeleton[static_cast<size_t>(cy) * width + cx] = 1;
				else
					skeleton[static_cast<size_t>(c.seed.y) * width + c.seed.x] = 1;
			}
		}

		// ---- skeleton: Lee-Chen 1992 (the evaluation paper's reference [60]) ---------

		/// <summary>
		/// The skeleton S(x,y) per Lee-Chen 1992: Zhang-Suen thinning to a fixed
		/// point, then the Table-1 look-up that deletes 8-simple points while
		/// preserving the T-junctions and cross junctions (Fig. 1) a plain Zhang-Suen
		/// would erode.  Doxa's detail::ApplyTablePassInPlace performs exactly the
		/// paper's look-up (same neighbour packing -- high nibble P9 P8 P7 P6, low
		/// nibble P5 P4 P3 P2 -- and the same "delete iff table[address]==0, in place"
		/// rule), driven by kLeeChenTable1.  The pass is iterated to a fixed point.
		///
		/// The evaluation tool's weight files are generated from this raw skeleton,
		/// WITHOUT Lee-Chen's subsequent tracing + short-curve deletion (Section 2,
		/// threshold Tl = (m+n)/2), so it is omitted here too -- which is why Doxa's
		/// general LeeChenThinning (which does prune short curves) is not reused.
		///
		/// Worked on a 1-pixel background-padded buffer so a stroke touching the real
		/// image border still thins (a detail the paper does not address).
		/// </summary>
		static void Skeletonize(
			std::vector<uint8_t>& skeleton,
			const std::vector<uint8_t>& fg,
			const int width,
			const int height)
		{
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

			skeleton.assign(static_cast<size_t>(width) * height, 0);
			for (int y = 0; y < height; ++y)
			{
				const int srow = y * width, prow = (y + 1) * pw;
				for (int x = 0; x < width; ++x)
					skeleton[srow + x] = thinned[prow + (x + 1)];
			}
		}

		// Lee-Chen 1992 Table 1 (page 544): the 256-entry simple-point deletion table.
		// Index = (P9 P8 P7 P6) << 4 | (P5 P4 P3 P2); 0x00 deletes P1, 0xFF keeps it,
		// 0x01 marks a point Zhang-Suen already removed (treated as keep).  Matches the
		// paper's worked patterns (16h->00, 1Eh->01, 55h->FF, 57h loop point->FF,
		// 6Dh 8-simple point->00).  This is NOT Doxa's general
		// LeeChenThinning::kPostPassTable -- they differ in four entries (0x0E, 0x45,
		// 0x54, 0xE0) and produce different skeletons; this table is the one that
		// reproduces the DIBCO reference weight files, so it is carried here.
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

		// ---- recall-side distance map ------------------------------------------------

		/// <summary>
		/// D(x,y) for the foreground (Eq. 2, Fig. 10c): the contour distance (reused
		/// transform), with skel&amp;contour -> 1, masked to the foreground (D is 0 off
		/// the foreground), then the medial-ridge adjustment.
		/// </summary>
		static void ForegroundDistanceMap(
			std::vector<uint8_t>& D,
			const std::vector<uint8_t>& fg,
			const std::vector<uint8_t>& contour,
			const std::vector<uint16_t>& contourDistance,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			const int size = width * height;
			D.assign(size, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!fg[i]) continue;
				D[i] = (contour[i] && skeleton[i]) ? 1 : static_cast<uint8_t>(contourDistance[i]);
			}
			MedialRidgeAdjust(D, skeleton, components, width, height);
		}

		/// <summary>
		/// D(x,y) for the background (Eq. 10): the distance to the SAME ground-truth
		/// contour (reused transform), with invSkel&amp;contour -> 1, taken only inside
		/// the Gsw_bg region; beyond the region the out-of-region marker stands in for
		/// PW = 1; ink pixels are 0.  Then the medial-ridge adjustment on the inverted
		/// skeleton.
		/// </summary>
		static void BackgroundDistanceMap(
			std::vector<uint8_t>& Dp,
			const std::vector<uint8_t>& invFg,
			const std::vector<uint8_t>& region,
			const std::vector<uint8_t>& contour,
			const std::vector<uint16_t>& contourDistance,
			const std::vector<uint8_t>& invSkeleton,
			const Components& invComponents,
			const int width,
			const int height)
		{
			const int size = width * height;
			Dp.assign(size, 0);
			for (int i = 0; i < size; ++i)
			{
				if (!invFg[i]) continue;                                   // ink pixel -> 0
				Dp[i] = (invSkeleton[i] && contour[i]) ? 1
				      : region[i] ? static_cast<uint8_t>(contourDistance[i]) // in-region distance (< 250)
				      : kOutsideRegion;                                      // beyond the stroke reach
			}
			MedialRidgeAdjust(Dp, invSkeleton, invComponents, width, height);
		}

		// ---- recall-side helpers -----------------------------------------------------

		// Lee-Chen termination point (Fig. 3a): count the 8 border-clamped skeleton
		// neighbours; if exactly one, return its medial factor so the endpoint can
		// inherit it (+1).  The bottom-right neighbour's factor is read at
		// (row+D)*W + B (the +col term differs from the other seven); this matches the
		// published DIBCO reference weight files exactly and is kept for bit-exact
		// .dat parity.
		static int TerminationPointFactor(
			const std::vector<uint8_t>& factor,
			const std::vector<uint8_t>& skeleton,
			const int col, const int row,
			const int width, const int height)
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

		// NR propagation predicate: true iff all four border-clamped neighbours are
		// set (NR != 0) and NR[centre] differs from every one of them.  (NR is
		// integer-valued, so the former ">= 0.5" set-test is "!= 0" and no truncation
		// is needed.)
		static bool PropagateAlongStroke(
			const std::vector<uint16_t>& NR,
			const int col, const int row,
			const int width, const int height)
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

		// ---- precision-side helpers --------------------------------------------------

		// Gsw_fg per component (Fig. 15a) and its map: componentStrokeWidth[label] =
		// 2 * floor(mean medial factor over the component's skeleton) (integer mean,
		// then *2; EnsureComponentSeeds guarantees a nonzero count).  strokeWidthMap
		// stamps that value over the component's ink pixels -- the value the precision
		// ring takes its max over -- and componentStrokeWidth is also the reach that
		// sizes the Gsw_bg region.
		static void ComponentStrokeWidths(
			std::vector<uint8_t>& strokeWidthMap,
			std::vector<int>& componentStrokeWidth,
			const std::vector<uint8_t>& medialFactor,
			const std::vector<uint8_t>& skeleton,
			const Components& components,
			const int width,
			const int height)
		{
			const int n = static_cast<int>(components.items.size());
			std::vector<long long> sum(n, 0), count(n, 0);
			WalkComponents(components, width, [&](const Component& c, int, int, int i)
			{
				if (skeleton[i]) { sum[c.label] += medialFactor[i]; ++count[c.label]; }
			});

			componentStrokeWidth.assign(n, 0);
			for (const Component& c : components)
				componentStrokeWidth[c.label] = count[c.label]
					? static_cast<int>((sum[c.label] / count[c.label]) * 2)
					: 0;

			strokeWidthMap.assign(static_cast<size_t>(width) * height, 0);
			WalkComponents(components, width, [&](const Component& c, int, int, int i)
			{
				strokeWidthMap[i] = static_cast<uint8_t>(componentStrokeWidth[c.label] & 0xFF);
			});
		}

		// Gsw_bg region (Eq. 10, Fig. 15b): a background pixel inside SOME component's
		// bounding box dilated by 2 * componentStrokeWidth on every side (clamped to
		// the image) is "reached" by that component's stroke.  Outside every such box,
		// a background pixel is beyond the stroke reach -- PW = 1 there (Eq. 10).
		static void BackgroundStrokeRegion(
			std::vector<uint8_t>& region,
			const std::vector<uint8_t>& fg,
			const std::vector<int>& componentStrokeWidth,
			const Components& components,
			const int width,
			const int height)
		{
			region.assign(static_cast<size_t>(width) * height, 0);
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
		// background ring touches two distinct components (the merging case); the
		// second produces NP, using the marked inter-component gap where merging looms
		// and the stroke reach elsewhere.
		enum class PrecisionPass { MarkMerges, Normalize };

		// One precision pass over the background (inverted) components (gate:
		// label-owned, Dp in [1,249]).
		static void PrecisionNormalizationPass(
			std::vector<uint8_t>& out,
			const PrecisionPass pass,
			const std::vector<uint8_t>& strokeWidthMap,
			const std::vector<uint8_t>& contour,
			const std::vector<int>& componentLabels,
			const std::vector<uint8_t>& Dp,
			const std::vector<uint16_t>& NP,
			const std::vector<uint8_t>& mergeMarker,
			const Components& invComponents,
			const int width,
			const int height)
		{
			WalkComponents(invComponents, width, [&](const Component& c, int x, int y, int i)
			{
				if (!HasDistance(Dp[i])) return;
				out[i] = static_cast<uint8_t>(
					PrecisionNormalizationRing(strokeWidthMap, contour, componentLabels, Dp, NP, mergeMarker, c, x, y, pass, width, height));
			});
		}

		// The precision counterpart of NormalizationRing.  Rings on the ground-truth
		// contour; for each contour pixel q on the first non-empty ring collect
		// strokeWidthMap[q] (max -> reach) and whether two distinct components appear
		// (adjacent -> merge risk).  Then, with dp = Dp[centre] and np = trunc(NP[centre]):
		//   dp > reach                 -> 0
		//   MarkMerges                 -> adjacent ? np : 0
		//   Normalize                  -> (a merge was marked within Chebyshev radius
		//                                   (reach - dp) of the centre  &&  np < reach)
		//                                   ? np : reach          (Eq. 11: min(Gc_sw, Gsw_bg))
		// No contour pixel anywhere in the bbox -> 0.
		static int PrecisionNormalizationRing(
			const std::vector<uint8_t>& strokeWidthMap,
			const std::vector<uint8_t>& contour,
			const std::vector<int>& componentLabels,
			const std::vector<uint8_t>& Dp,
			const std::vector<uint16_t>& NP,
			const std::vector<uint8_t>& mergeMarker,
			const Component& c,
			const int ax, const int ay, const PrecisionPass pass,
			const int width, const int height)
		{
			int reach = -1, firstLabel = -1;
			bool adjacent = false;
			const bool found = FirstNonEmptyRing(c, ax, ay, width, height, [&](const int j)
			{
				if (!contour[j]) return false;
				const int v = strokeWidthMap[j];
				if (v > reach) reach = v;
				const int L = componentLabels[j];
				if (firstLabel < 0) firstLabel = L;
				else if (L != firstLabel) adjacent = true;
				return true;
			});
			if (!found) return 0;

			const int i = ay * width + ax;
			const int dp = Dp[i];
			const int np = NP[i];   // NP is integer-valued (sqrt-rounded above)
			if (dp > reach) return 0;
			if (pass == PrecisionPass::MarkMerges)
				return (adjacent ? np : 0) & 0xFF;

			const int diff = reach - dp;
			const bool merging = AnyWithin(mergeMarker, ax, ay, diff, width, height);
			return ((merging && np < reach) ? np : reach) & 0xFF;
		}

		// True iff any nonzero pixel of map lies within Chebyshev distance `radius` of
		// (col,row), over the image-clamped square window.  radius 0 -> false.
		static bool AnyWithin(
			const std::vector<uint8_t>& map,
			const int col, const int row, const int radius,
			const int width, const int height)
		{
			if (radius == 0) return false;
			int xlo = col - radius, xhi = col + radius, ylo = row - radius, yhi = row + radius;
			if (xlo < 0) xlo = 0;  if (xhi > width - 1) xhi = width - 1;
			if (ylo < 0) ylo = 0;  if (yhi > height - 1) yhi = height - 1;
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
