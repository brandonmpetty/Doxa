// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef THINNING_HPP
#define THINNING_HPP

#include <array>
#include <cstdint>
#include <utility>
#include <vector>


namespace Doxa
{
	namespace detail
	{
		/// <summary>
		/// Pack the 8 neighbors of (x, y) into a uint8_t using the bit-order
		/// convention shared by Chen-Hsu (1988, Figure 4) and Lee-Chen (1992, Table 1):
		///
		///   bit 0 (LSB) = P2  (N)        P9 P2 P3
		///   bit 1       = P3  (NE)       P8  * P4
		///   bit 2       = P4  (E)        P7 P6 P5
		///   bit 3       = P5  (SE)
		///   bit 4       = P6  (S)
		///   bit 5       = P7  (SW)
		///   bit 6       = P8  (W)
		///   bit 7 (MSB) = P9  (NW)
		///
		/// Reusable by any 3x3-neighborhood lookup-driven operation.
		/// Caller is responsible for the 1-pixel border skip.
		/// </summary>
		inline uint8_t PackNeighbors(
			const std::vector<uint8_t>& mask,
			const int idx,
			const int width)
		{
			const int north = idx - width;
			const int here  = idx;
			const int south = idx + width;

			uint8_t a = 0x00;
			if (mask[north    ]) a |= 0x01; // P2  N
			if (mask[north + 1]) a |= 0x02; // P3  NE
			if (mask[here  + 1]) a |= 0x04; // P4  E
			if (mask[south + 1]) a |= 0x08; // P5  SE
			if (mask[south    ]) a |= 0x10; // P6  S
			if (mask[south - 1]) a |= 0x20; // P7  SW
			if (mask[here  - 1]) a |= 0x40; // P8  W
			if (mask[north - 1]) a |= 0x80; // P9  NW

			return a;
		}

		/// <summary>
		/// One sweep over the interior of `mask`: for each foreground pixel,
		/// look up `table[PackNeighbors(...)]` and delete the pixel if the
		/// value is 0x00.  Any other table value (typically 0xFF, or 0x01 in
		/// Lee-Chen's "already deleted by Zhang-Suen" marker) leaves the
		/// pixel alone.
		///
		/// Removals are batched into the caller-provided `toRemove` scratch
		/// buffer so they do not influence other pixels in this sweep, and
		/// so successive sweeps share one allocation.  The buffer is
		/// cleared on entry; its contents on return are an implementation
		/// detail.  Returns true if any pixel was removed.  Border pixels
		/// are skipped, matching ZhangSuenThinning's border rule.
		/// </summary>
		inline bool ApplyTablePass(
			std::vector<uint8_t>& mask,
			const std::array<uint8_t, 256>& table,
			std::vector<int>& toRemove,
			const int width,
			const int height)
		{
			toRemove.clear();

			for (int y = 1; y < height - 1; ++y)
			{
				const int rowIdx = y * width;

				for (int x = 1; x < width - 1; ++x)
				{
					const int idx = rowIdx + x;
					if (!mask[idx]) continue;
					if (table[PackNeighbors(mask, idx, width)] == 0x00)
					{
						toRemove.push_back(idx);
					}
				}
			}

			for (int idx : toRemove) mask[idx] = 0;
			return !toRemove.empty();
		}

		/// <summary>
		/// One sweep like ApplyTablePass, but each deletion is committed to
		/// `mask` immediately rather than batched.  This makes the pass
		/// *sequential*: a pixel removed earlier in the raster scan is already
		/// gone when a later pixel's neighborhood is packed, so the later
		/// pixel sees the hole.
		///
		/// This is the correct application order for a simple-point deletion
		/// table such as Lee-Chen's Table 1.  Such a table marks every
		/// 8-simple point for removal; applying it in parallel (ApplyTablePass)
		/// can delete two mutually-adjacent simple points in the same sweep and
		/// break the stroke.  Deleting in place prevents that: once one of the
		/// pair is gone, the other is no longer simple and its address no
		/// longer maps to 0x00.  (Zhang-Suen and Chen-Hsu must NOT use this --
		/// their sub-iteration rules are designed for parallel deletion.)
		///
		/// Border pixels are skipped, matching ApplyTablePass.  Returns true if
		/// any pixel was removed.
		/// </summary>
		inline bool ApplyTablePassInPlace(
			std::vector<uint8_t>& mask,
			const std::array<uint8_t, 256>& table,
			const int width,
			const int height)
		{
			bool removed = false;

			for (int y = 1; y < height - 1; ++y)
			{
				const int rowIdx = y * width;

				for (int x = 1; x < width - 1; ++x)
				{
					const int idx = rowIdx + x;
					if (!mask[idx]) continue;
					if (table[PackNeighbors(mask, idx, width)] == 0x00)
					{
						mask[idx] = 0; // commit now: later pixels see the hole
						removed = true;
					}
				}
			}

			return removed;
		}

		/// <summary>
		/// 180-degree rotation of an 8-bit neighbor address: in the
		/// bit-order convention above this is simply a low-nibble /
		/// high-nibble swap, equivalent to substituting each pixel for
		/// its diametrically-opposite neighbor (P2<->P6, P3<->P7,
		/// P4<->P8, P5<->P9).  Used to derive Chen-Hsu's sub-iter 2
		/// table from its sub-iter 1 table by the same address rotation.
		/// </summary>
		constexpr std::array<uint8_t, 256> Rotate180(
			const std::array<uint8_t, 256>& t)
		{
			std::array<uint8_t, 256> r{};
			for (int i = 0; i < 256; ++i)
			{
				const int j = ((i & 0x0F) << 4) | ((i & 0xF0) >> 4);
				r[i] = t[j];
			}

			return r;
		}

		/// <summary>
		/// Chen-Hsu 1988 sub-iter 1 deletion rule, evaluated directly from
		/// the paper's conditions for an 8-bit packed neighborhood `a`
		/// (bit order per PackNeighbors):
		///   (a) 2 <= B(P1) <= 7                          -- contour count
		///   (b) A(P1) == 1, with corner triples
		///       (c) P2*P4*P6 == 0  AND  (d) P4*P6*P8 == 0
		///   (e) A(P1) == 2, with either stair-pattern triple
		///       (f) P2*P4 == 1  AND  P6+P7+P8 == 0       -- NE stair
		///       (g) P4*P6 == 1  AND  P2+P8+P9 == 0       -- SE stair
		/// Returns 0x00 if any branch deletes P1, else 0xFF.  Lives in
		/// detail (not inside ChenHsuThinning) because MSVC won't evaluate
		/// an in-class constexpr member function from a sibling static
		/// constexpr data member initializer -- the function body is
		/// parsed after the class is complete.
		/// </summary>
		constexpr uint8_t ChenHsuSubIter1Rule(uint8_t a)
		{
			const int p2 = (a >> 0) & 1;
			const int p3 = (a >> 1) & 1;
			const int p4 = (a >> 2) & 1;
			const int p5 = (a >> 3) & 1;
			const int p6 = (a >> 4) & 1;
			const int p7 = (a >> 5) & 1;
			const int p8 = (a >> 6) & 1;
			const int p9 = (a >> 7) & 1;

			const int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
			if (B < 2 || B > 7) return 0xFF;

			int A = 0;
			if (!p2 && p3) ++A;
			if (!p3 && p4) ++A;
			if (!p4 && p5) ++A;
			if (!p5 && p6) ++A;
			if (!p6 && p7) ++A;
			if (!p7 && p8) ++A;
			if (!p8 && p9) ++A;
			if (!p9 && p2) ++A;

			if (A == 1)
			{
				if (p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0) return 0x00;
			}
			else if (A == 2)
			{
				if (p2 * p4 == 1 && (p6 + p7 + p8) == 0) return 0x00;
				if (p4 * p6 == 1 && (p2 + p8 + p9) == 0) return 0x00;
			}

			return 0xFF;
		}

		/// <summary>
		/// Build the Chen-Hsu sub-iter 1 lookup table at compile time by
		/// evaluating ChenHsuSubIter1Rule for every 8-bit neighborhood
		/// address.  See ChenHsuThinning::kSubIter1Table for the caller.
		/// </summary>
		constexpr std::array<uint8_t, 256> MakeChenHsuSubIter1Table()
		{
			std::array<uint8_t, 256> t{};
			for (int i = 0; i < 256; ++i)
			{
				t[i] = ChenHsuSubIter1Rule(static_cast<uint8_t>(i));
			}
			return t;
		}

		/// <summary>
		/// Zhang-Suen 1984 deletion rule for sub-iteration `subIter` (1 or 2),
		/// evaluated on an 8-bit packed neighborhood `a` (bit order per
		/// PackNeighbors).  Returns 0x00 to delete P1, 0xFF to keep:
		///   B(P1) in [2, 6]  -- contour count
		///   A(P1) == 1       -- exactly one 0->1 transition in P2..P9..P2
		///   Sub-iter 1 corner triples:  P2*P4*P6 == 0  AND  P4*P6*P8 == 0
		///   Sub-iter 2 corner triples:  P2*P4*P8 == 0  AND  P2*P6*P8 == 0
		/// Reference: Zhang, T. Y., Suen, C. Y., Comm. ACM 27(3), 1984.
		/// In detail (not inside ZhangSuenThinning) for the same MSVC
		/// reason ChenHsuSubIter1Rule is.
		/// </summary>
		constexpr uint8_t ZhangSuenRule(uint8_t a, int subIter)
		{
			const int p2 = (a >> 0) & 1;
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

			if (subIter == 1)
			{
				if (p2 && p4 && p6) return 0xFF;
				if (p4 && p6 && p8) return 0xFF;
			}
			else
			{
				if (p2 && p4 && p8) return 0xFF;
				if (p2 && p6 && p8) return 0xFF;
			}

			return 0x00;
		}

		/// <summary>
		/// Build a Zhang-Suen lookup table for `subIter` (1 or 2) at compile
		/// time by evaluating ZhangSuenRule over all 256 neighborhoods.
		/// See ZhangSuenThinning::kSubIter1Table / kSubIter2Table.
		/// </summary>
		constexpr std::array<uint8_t, 256> MakeZhangSuenTable(int subIter)
		{
			std::array<uint8_t, 256> t{};
			for (int i = 0; i < 256; ++i)
			{
				t[i] = ZhangSuenRule(static_cast<uint8_t>(i), subIter);
			}
			return t;
		}


		// --- Skeleton tracing (Lee-Chen 1992, Section 2 / page 545) ----------
		//
		// Chain-code geometry of the 8 neighbors, ordered by Lee-Chen's Figure
		// 4 direction code (0=E, 1=NE, 2=N, 3=NW, 4=W, 5=SW, 6=S, 7=SE) with
		// image y growing downward.  The order is cyclically adjacent (each
		// code is 8-adjacent to the next), so the same arrays drive both the
		// chain-coding of curves and the crossing-number branch count below.
		constexpr int kChainDx[8] = {  1,  1,  0, -1, -1, -1,  0,  1 };
		constexpr int kChainDy[8] = {  0, -1, -1, -1,  0,  1,  1,  1 };

		// Per-step length (Lemma 1): 1 for an even (orthogonal) code, sqrt(2)
		// for an odd (diagonal) code.  Constant avoids pulling in <cmath>.
		constexpr double kDiagLength = 1.4142135623730951;
		inline double StepLength(const int code) { return (code & 1) ? kDiagLength : 1.0; }

		/// <summary>
		/// Number of distinct foreground branches meeting at a skeleton pixel,
		/// computed as the crossing number A: the count of 0->1 transitions
		/// around the 8-ring in chain-code order.  This counts branches, not
		/// raw neighbors, so a "fat corner" (two mutually-adjacent neighbors)
		/// reads as one branch -- the paper's "nonconnected neighbors" notion
		/// (Fig 3).  1 = termination point (Fig 3a), 2 = ordinary curve point,
		/// >= 3 = fork/junction (Fig 3b/c), 0 = isolated pixel.  Out-of-bounds
		/// (border, treated as background) contributes 0.
		/// </summary>
		inline int BranchCount(
			const std::vector<uint8_t>& mask,
			const int x,
			const int y,
			const int width,
			const int height)
		{
			uint8_t ring[8];
			for (int i = 0; i < 8; ++i)
			{
				const int nx = x + kChainDx[i];
				const int ny = y + kChainDy[i];
				ring[i] = (nx >= 0 && nx < width && ny >= 0 && ny < height && mask[ny * width + nx]) ? 1 : 0;
			}

			int a = 0;
			for (int i = 0; i < 8; ++i)
				if (!ring[i] && ring[(i + 1) & 7]) ++a;
			return a;
		}

		/// <summary>
		/// On an ordinary curve pixel (BranchCount == 2), given the chain-code
		/// direction back toward the pixel we arrived from (backCode), return
		/// the chain code that continues the curve: a foreground neighbor that
		/// belongs to the *other* branch (not in the cyclic run that contains
		/// backCode).  Returns -1 if there is no continuation.
		/// </summary>
		inline int NextChainCode(
			const std::vector<uint8_t>& mask,
			const int x,
			const int y,
			const int width,
			const int height,
			const int backCode)
		{
			uint8_t fg[8];
			for (int i = 0; i < 8; ++i)
			{
				const int nx = x + kChainDx[i];
				const int ny = y + kChainDy[i];
				fg[i] = (nx >= 0 && nx < width && ny >= 0 && ny < height && mask[ny * width + nx]) ? 1 : 0;
			}

			// Mark every code in the same cyclic run as backCode (expand both
			// ways while foreground); the continuation is in a different run.
			bool inBackRun[8] = { false };
			inBackRun[backCode] = true;
			for (int d = 1; d <= 7; ++d) { const int j = (backCode + d) & 7; if (fg[j]) inBackRun[j] = true; else break; }
			for (int d = 1; d <= 7; ++d) { const int j = (backCode - d + 8) & 7; if (fg[j]) inBackRun[j] = true; else break; }

			for (int i = 0; i < 8; ++i)
				if (fg[i] && !inBackRun[i]) return i;
			return -1;
		}

		/// <summary>
		/// One traced curve: an ordered run of pixels (endpoints included) and
		/// its accumulated chain-code length (Lemma 1).  A single isolated
		/// pixel is a zero-length curve of one pixel.
		/// </summary>
		struct TracedCurve
		{
			std::vector<int> pixels;
			double           length = 0.0;
		};

		/// <summary>
		/// Trace the skeleton into curves (Lee-Chen Section 2, p.545).  A curve
		/// is a maximal run of ordinary points (BranchCount == 2) bounded by
		/// nodes -- termination points (1) or junctions (>= 3); an isolated
		/// pixel (0) is a zero-length curve.  Scanned top-to-bottom,
		/// left-to-right, with each curve emitted exactly once: walks start at
		/// the first code of each foreground run around a node (one walk per
		/// branch), interior pixels are marked consumed so the mirror walk from
		/// the far node stops, and a direct node-to-node edge (no interior) is
		/// emitted only from the smaller pixel index.  Pure loops (cycles with
		/// no node) are intentionally not emitted -- they have no endpoints,
		/// are never noise-short, and are left intact.
		/// </summary>
		inline std::vector<TracedCurve> TraceSkeleton(
			const std::vector<uint8_t>& mask,
			const int width,
			const int height)
		{
			std::vector<TracedCurve> curves;
			std::vector<uint8_t> consumed(mask.size(), 0); // ordinary pixels already on a curve

			for (int y = 1; y < height - 1; ++y)
			{
				for (int x = 1; x < width - 1; ++x)
				{
					const int nIdx = y * width + x;
					if (!mask[nIdx]) continue;

					const int a = BranchCount(mask, x, y, width, height);
					if (a == 2) continue;        // ordinary point: reached via its node(s)

					if (a == 0)                  // isolated pixel: zero-length curve
					{
						TracedCurve c;
						c.pixels.push_back(nIdx);
						curves.push_back(std::move(c));
						continue;
					}

					// Node (termination or junction): one walk per foreground run.
					for (int code = 0; code < 8; ++code)
					{
						const int mx = x + kChainDx[code];
						const int my = y + kChainDy[code];
						if (mx < 0 || mx >= width || my < 0 || my >= height) continue;
						const int mIdx = my * width + mx;
						if (!mask[mIdx]) continue;

						// Only start at the beginning of a run, so each branch is
						// walked once even when a run spans two adjacent neighbors.
						const int pCode = (code - 1 + 8) & 7;
						const int px = x + kChainDx[pCode];
						const int py = y + kChainDy[pCode];
						const bool prevFg = px >= 0 && px < width && py >= 0 && py < height && mask[py * width + px];
						if (prevFg) continue;

						const int mA = BranchCount(mask, mx, my, width, height);

						// Direct node-to-node edge (no interior): emit once.
						if (mA != 2)
						{
							if (nIdx < mIdx)
							{
								TracedCurve c;
								c.pixels = { nIdx, mIdx };
								c.length = StepLength(code);
								curves.push_back(std::move(c));
							}
							continue;
						}

						// Edge with interior; skip if walked from the far node.
						if (consumed[mIdx]) continue;

						TracedCurve c;
						c.pixels.push_back(nIdx);
						c.pixels.push_back(mIdx);
						c.length = StepLength(code);

						int cur = mIdx, curCode = code;
						while (true)
						{
							consumed[cur] = 1;
							const int cx = cur % width, cy = cur / width;
							const int backCode = (curCode + 4) & 7; // cur -> prev
							const int nextCode = NextChainCode(mask, cx, cy, width, height, backCode);
							if (nextCode < 0) break; // dead end (should not happen for A == 2)

							const int nx = cx + kChainDx[nextCode];
							const int ny = cy + kChainDy[nextCode];
							const int nextIdx = ny * width + nx;

							// Rejoined already-walked territory (a tight cycle or a
							// fat-corner oscillation): stop to keep the walk finite.
							if (consumed[nextIdx]) break;

							c.pixels.push_back(nextIdx);
							c.length += StepLength(nextCode);
							cur = nextIdx; curCode = nextCode;

							if (BranchCount(mask, nx, ny, width, height) != 2) break; // reached a node
						}

						curves.push_back(std::move(c));
					}
				}
			}

			return curves;
		}

		/// <summary>
		/// Lee-Chen short-curve deletion (Section 2, p.545): trace the
		/// skeleton, then remove every curve shorter than minLength.  A curve's
		/// interior pixels are cleared, and a termination/isolated endpoint is
		/// cleared too, but a junction endpoint (BranchCount >= 3) is kept --
		/// it anchors other curves.  A short curve whose BOTH endpoints are
		/// junctions is a connecting bridge, not a spur, and is left intact so
		/// removing noise never disconnects the skeleton.  Classification and
		/// deletion both read the original skeleton, so the pass is order
		/// independent (single pass, matching the paper).
		/// </summary>
		inline void RemoveShortCurves(
			std::vector<uint8_t>& skeleton,
			const int width,
			const int height,
			const double minLength)
		{
			if (minLength <= 0.0) return;

			const std::vector<TracedCurve> curves = TraceSkeleton(skeleton, width, height);

			std::vector<uint8_t> toDelete(skeleton.size(), 0);
			for (const TracedCurve& c : curves)
			{
				if (c.length >= minLength) continue;

				const int n = static_cast<int>(c.pixels.size());
				const int front = c.pixels.front();
				const int back  = c.pixels.back();

				const bool frontJunction = BranchCount(skeleton, front % width, front / width, width, height) >= 3;
				const bool backJunction  = n > 1 && BranchCount(skeleton, back % width, back / width, width, height) >= 3;

				// Bridge between two junctions: keep it to preserve connectivity.
				if (n > 1 && frontJunction && backJunction) continue;

				for (int i = 1; i + 1 < n; ++i) toDelete[c.pixels[i]] = 1; // interior
				if (!frontJunction) toDelete[front] = 1;
				if (n > 1 && !backJunction) toDelete[back] = 1;
			}

			for (size_t i = 0; i < skeleton.size(); ++i)
				if (toDelete[i]) skeleton[i] = 0;
		}
	}


	/// <summary>
	/// Zhang-Suen iterative thinning -- the parameter-free standard for
	/// producing a one-pixel-wide medial skeleton from a binary mask.
	///
	/// Each iteration has two sub-passes that mark removable foreground
	/// pixels using local 3x3 connectivity tests (B, A, and corner products
	/// per the original paper).  Removals are batched per sub-pass; the
	/// algorithm terminates when a full iteration removes no pixels.
	///
	/// Implementation: pure table-driven.  Each sub-iteration's removal
	/// rule depends only on the 8-neighbor pattern, so we precompute two
	/// 256-entry constexpr lookup tables from detail::ZhangSuenRule and
	/// run them through the same detail::ApplyTablePass loop used by
	/// ChenHsuThinning and LeeChenThinning.
	///
	/// Input mask convention: 1 == foreground, 0 == background.  The output
	/// mask uses the same convention.  The 1-pixel image border is treated
	/// as background -- pixels touching the border are not eligible for
	/// removal in their own sub-pass.  Callers that need a skeleton inside
	/// the image frame should pad the mask before calling and crop after.
	///
	/// Reference: Zhang, T. Y., Suen, C. Y. "A fast parallel algorithm for
	/// thinning digital patterns." Comm. ACM 27(3), 1984.
	/// </summary>
	class ZhangSuenThinning
	{
	public:
		static void Skeletonize(
			std::vector<uint8_t>& skeletonOut,
			const std::vector<uint8_t>& foregroundMaskIn,
			const int width,
			const int height)
		{
			skeletonOut = foregroundMaskIn;

			std::vector<int> toRemove;
			toRemove.reserve(256);

			bool changed = true;
			while (changed)
			{
				changed = false;
				changed |= detail::ApplyTablePass(skeletonOut, kSubIter1Table, toRemove, width, height);
				changed |= detail::ApplyTablePass(skeletonOut, kSubIter2Table, toRemove, width, height);
			}
		}

		// Sub-iteration 1 and 2 thinning tables, generated at compile time
		// from detail::ZhangSuenRule -- a direct encoding of the paper's
		// B, A, and corner-triple conditions.  Value 0x00 = delete center;
		// 0xFF = keep.
		static constexpr std::array<uint8_t, 256> kSubIter1Table = detail::MakeZhangSuenTable(1);
		static constexpr std::array<uint8_t, 256> kSubIter2Table = detail::MakeZhangSuenTable(2);
	};


	/// <summary>
	/// Chen-Hsu 1988 parallel thinning -- a modification of Zhang-Suen that
	/// widens the contour-pixel bound from B <= 6 to B <= 7 and adds an
	/// A(P1) = 2 branch with two stair-pattern triples per sub-iteration.
	/// The combined effect is less shrinking and complete one-pixel-wide
	/// strokes under the 8-neighbor connectivity model, while preserving
	/// the contour-noise immunity of the original.
	///
	/// Implementation: pure table-driven.  Per the paper's Section 3 each
	/// sub-iteration maps the 8-neighbor pattern through a 256-entry
	/// lookup table (Figure 4).  Sub-iter 1's table is generated at
	/// compile time by evaluating the paper's conditions (a)-(g) for
	/// every 8-bit neighborhood -- see SubIter1Rule.  Sub-iter 2's table
	/// is derived at compile time by a 180-degree rotation of the
	/// address (nibble swap: bit0<->bit4, bit1<->bit5, bit2<->bit6,
	/// bit3<->bit7).  The rotation is correct because the conditions
	/// (c'), (d'), (f'), (g') of sub-iter 2 are exactly the substitution
	/// P2<->P6, P3<->P7, P4<->P8, P5<->P9 applied to sub-iter 1's
	/// (c), (d), (f), (g).  An exhaustive oracle test compares the
	/// rotated sub-iter 2 table against the rotated conditions
	/// evaluated directly -- which jointly validates both the rule and
	/// the rotation derivation.
	///
	/// Input and output mask convention: 1 == foreground, 0 == background.
	/// 1-pixel image border is treated as background (same rule as
	/// ZhangSuenThinning).
	///
	/// Reference: Chen, Y. S., Hsu, W. H. "A modified fast parallel
	/// algorithm for thinning digital patterns." Pattern Recognition
	/// Letters 7(2), 1988, pp. 99-106.
	/// </summary>
	class ChenHsuThinning
	{
	public:
		static void Skeletonize(
			std::vector<uint8_t>& skeletonOut,
			const std::vector<uint8_t>& foregroundMaskIn,
			const int width,
			const int height)
		{
			skeletonOut = foregroundMaskIn;

			std::vector<int> toRemove;
			toRemove.reserve(256);

			bool changed = true;
			while (changed)
			{
				changed = false;
				changed |= detail::ApplyTablePass(skeletonOut, kSubIter1Table, toRemove, width, height);
				changed |= detail::ApplyTablePass(skeletonOut, kSubIter2Table, toRemove, width, height);
			}
		}

		// Sub-iteration 1 thinning table, generated at compile time from
		// detail::ChenHsuSubIter1Rule -- a direct encoding of Section 3
		// of Chen, Hsu 1988 (pages 102-103).  Value 0x00 = delete center;
		// 0xFF = keep.  Equivalent to Figure 4(a) of the paper; see
		// ChenHsuSubIter1Rule in detail for the conditions, and
		// ChenHsuThinningTests for canonical patterns that pin the
		// interpretation.
		static constexpr std::array<uint8_t, 256> kSubIter1Table = detail::MakeChenHsuSubIter1Table();

		// Sub-iteration 2 table, derived at compile time from sub-iter 1
		// by the 180-degree address rotation (low nibble <-> high nibble).
		// See detail::Rotate180 for why this is correct.
		static constexpr std::array<uint8_t, 256> kSubIter2Table = detail::Rotate180(kSubIter1Table);
	};


	/// <summary>
	/// Lee-Chen 1992 thinning -- the full Section-2 skeleton, not just a
	/// post-passed Zhang-Suen.  The paper's deliverable is a unitary
	/// (one-pixel-wide, 8-connected) skeleton with T-junctions and cross
	/// junctions preserved, and the visible noise barbs removed; reaching it
	/// takes three stages:
	///
	///   1. Zhang-Suen to a fixed point.
	///   2. The post-pass lookup table (Table 1) applied to delete every
	///      8-simple point whose 8-neighbor address maps to 0x00.  This pass
	///      is run SEQUENTIALLY in place (detail::ApplyTablePassInPlace), not
	///      batched: the table marks simple points, and deleting two
	///      mutually-adjacent simple points in one parallel sweep would break
	///      the stroke.  Committing each deletion immediately means the second
	///      of such a pair is no longer simple by the time it is visited.
	///   3. Tracing + short-curve deletion (page 545).  The skeleton is walked
	///      into curves between termination points (Fig 3a) and junctions
	///      (Fig 3b/c); curves shorter than minCurveLength are pruned as noise
	///      (detail::RemoveShortCurves), preserving junctions so the cleanup
	///      never disconnects the skeleton.
	///
	/// minCurveLength is the short-curve threshold in accumulated chain-code
	/// length (Lemma 1: orthogonal step 1, diagonal sqrt(2)).  The paper uses
	/// a per-normalized-character Tl = (rows + cols) / 2, which only makes
	/// sense once characters are segmented; for a general (multi-character)
	/// image that erases everything, so the default here is small -- it strips
	/// 1-2 pixel barbs and isolated specks while leaving real strokes intact.
	/// Pass a larger value when skeletonizing a single segmented glyph.
	///
	/// Table value convention from the paper:
	///   0xFF -- keep the pixel
	///   0x00 -- delete in Step 2 (the post-pass)
	///   0x01 -- INFORMATIONAL: Zhang-Suen Step 1 would have already
	///           removed this; the value is documentary, not algorithmic.
	///           The pass treats anything != 0x00 as "keep".
	///
	/// Input and output mask convention: 1 == foreground, 0 == background; the
	/// 1-pixel image border is treated as background (same rule as
	/// ZhangSuenThinning).
	///
	/// Reference: Lee, H. J., Chen, B. "Recognition of handwritten Chinese
	/// characters via short line segments." Pattern Recognition 25(5),
	/// 1992, pp. 543-552.  Table 1 is on page 544; tracing and short-curve
	/// deletion are on page 545.
	/// </summary>
	class LeeChenThinning
	{
	public:
		// Default short-curve threshold (chain-code length).  Removes isolated
		// specks (length 0) and 1-2 pixel barbs (length 1 .. ~2.4) while
		// keeping anything that reads as a real stroke.  See class comment.
		static constexpr double kDefaultMinCurveLength = 3.0;

		static void Skeletonize(
			std::vector<uint8_t>& skeletonOut,
			const std::vector<uint8_t>& foregroundMaskIn,
			const int width,
			const int height,
			const double minCurveLength = kDefaultMinCurveLength)
		{
			// Step 1: Zhang-Suen to fixed point.
			ZhangSuenThinning::Skeletonize(skeletonOut, foregroundMaskIn, width, height);

			// Step 2: sequential in-place post-pass (simple-point deletion).
			detail::ApplyTablePassInPlace(skeletonOut, kPostPassTable, width, height);

			// Step 3: trace + short-curve deletion (prune noise barbs/specks).
			detail::RemoveShortCurves(skeletonOut, width, height, minCurveLength);
		}

		// Post-pass lookup table, best-effort transcription of Lee-Chen 1992
		// Table 1 (page 544).  Validation tests in ThinningTests.cpp pin the
		// 0x01 entries against a Zhang-Suen oracle and pin specific patterns
		// quoted by name in the paper text (0x16, 0x1E, 0x6D).
		//
		// Row = high nibble (P9 P8 P7 P6); column = low nibble (P5 P4 P3 P2).
		static constexpr std::array<uint8_t, 256> kPostPassTable = {{
			// row 0
			0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01,
			// row 1
			0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01,
			// row 2
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			// row 3
			0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01,
			// row 4
			0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			// row 5
			0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
			// row 6
			0x01, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			// row 7
			0x01, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0x00, 0xFF, 0x00, 0x01, 0xFF, 0x01, 0xFF,
			// row 8
			0xFF, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			// row 9
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			// row A
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			// row B
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			// row C
			0x01, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x01,
			// row D
			0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
			// row E
			0x01, 0x01, 0xFF, 0x01, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
			// row F
			0x01, 0x01, 0xFF, 0x01, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0x01, 0xFF, 0x00, 0x01, 0xFF, 0x00, 0xFF,
		}};
	};
}


#endif // THINNING_HPP
