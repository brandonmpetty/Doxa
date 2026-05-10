// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef WELLNER_HPP
#define WELLNER_HPP

#include <vector>
#include "Algorithm.hpp"


namespace Doxa
{
	/// <summary>
	/// The Wellner Algorithm: Pierre D. Wellner
	///
	/// A single-pass adaptive thresholding algorithm.  Each pixel is compared
	/// against a recursively-maintained moving average of recently visited pixels,
	/// so the threshold tracks local background illumination without ever
	/// summing a full window.  The image is traversed boustrophedon
	/// (alternating direction per row) so the running average is not biased
	/// in one direction, and at each pixel the current row's running sum is
	/// blended with the same column on the previous row to introduce vertical
	/// context.
	///
	/// Per the paper:
	///   g(n) = g(n-1) - g(n-1)/s + p(n)         // approximate moving sum
	///   h(n) = (g(n) + g_prevrow(n)) / 2        // 2D blend
	///   T(n) = (h(n)/s) * (100 - t)/100         // threshold
	///   pixel < T(n) -> black, otherwise white
	///
	/// Default 's' is one-eighth of the image width rounded down to the
	/// nearest power of two; default 't' is 15.  These match the values
	/// recommended in the paper (which only specifies "around width/8").
	/// When 's' is a power of two the per-pixel `sum / s` collapses to a
	/// shift -- a ~3.5x speedup over the divide path on modern x86, since
	/// variable-divisor integer division dominates the inner loop.  Users
	/// who pass an explicit 's' stride get exactly that value, falling back
	/// to the divide path when it is not a power of two.
	///
	/// NOTE: The only reason to run this algorithm for the speed.
	/// If your stride is NOT a power of 2, just use Sauvola.
	///
	/// </summary>
	/// <remarks>"Interacting with Paper on the DigitalDesk", Wellner, 1994.</remarks>
	class Wellner : public Algorithm<Wellner>
	{
	public:

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const Image& in = Algorithm::grayScaleImageIn;

			// Read parameters, utilizing defaults
			int s = parameters.Get("s", 0); // 0 - Default to optimized stride
			const int t = parameters.Get("t", 15);

			// Round width/8 down to the nearest power of two so the default
			// hits the shift path automatically.  Explicit user-supplied
			// 's' values are honored exactly, with a divide fallback when
			// they aren't a power of two.
			if (!s)
			{
				s = 1;
				while (s * 2 <= in.width / 8) s *= 2;
			}

			// Power-of-two 's' lets us replace a per-pixel integer divide
			// with a shift.  Pick the right specialization once, up front,
			// so the hot loop stays branchless on this choice.
			const bool sIsPowerOfTwo = (s > 0) && ((s & (s - 1)) == 0);

			if (sIsPowerOfTwo)
				Process<true>(binaryImageOut, in, s, t);
			else
				Process<false>(binaryImageOut, in, s, t);
		}

	protected:

		/// <summary>
		/// One pass over the image, threshold each pixel against a recursively
		/// updated moving average.  When UseShift is true, the divide by 's'
		/// becomes a shift -- the rest of the routine is identical. 3.5-5x bump!
		/// </summary>
		template<bool UseShift>
		static void Process(Image& binaryImageOut, const Image& in, const int s, const int t)
		{
			const int width = in.width;
			const int height = in.height;

			// log2(s), only meaningful when UseShift is true.
			int sShift = 0;
			if constexpr (UseShift)
			{
				for (int v = s; v > 1; v >>= 1) ++sShift;
			}

			// The threshold check is `pixel < (h/s) * (100 - t) / 100`.
			// Cross-multiply by `s * 100` to keep the inner loop integer-only:
			//   pixel * sScaled < h * kFactor
			const int sScaled = s * 100;
			const int kFactor = 100 - t;

			// One row of the previous line's running averages.  Initialized to
			// the same neutral value as the moving sum so the very first pixels
			// don't trigger spurious black.
			std::vector<int> prevRow(width, 127 * s);

			// Approximate moving sum.  Carries across row boundaries -- the
			// boustrophedon scan makes the wrap-around continuous in content.
			int sum = 127 * s;

			for (int y = 0; y < height; ++y)
			{
				const int row = y * width;

				// Alternate direction every row.  Without this, lighting
				// gradients in one direction get over- or under-thresholded.
				const bool reverse = (y & 1) != 0;
				const int xStart = reverse ? width - 1 : 0;
				const int xEnd   = reverse ? -1        : width;
				const int xStep  = reverse ? -1        : 1;

				for (int x = xStart; x != xEnd; x += xStep)
				{
					const int pixel = in.data[row + x];

					// Large performance boost of 3.5-5x!  Without, Niblack is faster :/
					// TODO: See if this technique can be leveraged in other algorithms.
					if constexpr (UseShift)
						sum = sum - (sum >> sShift) + pixel;
					else
						sum = sum - sum / s + pixel;  // Not worth it.

					const int blended = (sum + prevRow[x]) >> 1; // Optimization: >> 1 == / 2
					prevRow[x] = sum;

					binaryImageOut.data[row + x] =
						(pixel * sScaled < blended * kFactor) ? Palette::Black : Palette::White;
				}
			}
		}
	};
}


#endif //WELLNER_HPP
