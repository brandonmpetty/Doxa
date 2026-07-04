// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include <algorithm>
#include <vector>
#include "Image.hpp"
#include "Types.hpp"


namespace Doxa
{
	/// <summary>
	/// Convolution primitives, ordered from most specialized to most generic:
	///
	///   Stencil3x3      The shared 3x3 building block.  Caller supplies a
	///                   functor that produces one output value from the 9
	///                   neighborhood pixels.  Fully unrolled in the hot
	///                   interior loop, with a separate clamp-to-edge border
	///                   pass.  Output type is the caller's choice (uint8 for
	///                   Sobel/Laplacian, int for Canny's gradient stage).
	///
	///   Apply3x3        Sugar over Stencil3x3 for the common "apply this 3x3
	///                   kernel array" case.  Output is uint8, clamped.
	///
	///   Apply           Generic variable-size 2D convolution.  kernelSize
	///                   must be odd.  Output is uint8, clamped.
	///
	///   ApplySeparable  Generic variable-size separable convolution: a 1D
	///                   kernel applied horizontally and then vertically via
	///                   an internal scratch buffer.  This is what Gaussian
	///                   and any other separable kernel should use.
	///
	/// Every primitive uses clamp-to-edge boundary handling.
	/// </summary>
	class Convolution
	{
	public:
		/// <summary>
		/// Apply a fused 3x3 stencil to every pixel of `in`, writing each
		/// result into `out`.  `op` is called with the 9 neighborhood pixel
		/// values in row-major order:
		///
		///   Out op(int p00, int p01, int p02,
		///          int p10, int p11, int p12,
		///          int p20, int p21, int p22);
		///
		/// The interior loop reads neighbors without bounds checks; the
		/// 1-pixel border strip is handled separately with clamp-to-edge
		/// neighbor lookups.  `out` must point to `in.width * in.height`
		/// elements of type Out.
		/// </summary>
		template<typename Out, typename Op>
		static void Stencil3x3(Out* out, const Image& in, Op op)
		{
			const int W = in.width;
			const int H = in.height;
			const Pixel8* p = in.data;

			// Hot interior: every neighbor read is in-bounds.
			for (int y = 1; y < H - 1; ++y)
			{
				const int row = y * W;
				for (int x = 1; x < W - 1; ++x)
				{
					const int i = row + x;
					out[i] = op(
						p[i - W - 1], p[i - W], p[i - W + 1],
						p[i - 1],     p[i],     p[i + 1],
						p[i + W - 1], p[i + W], p[i + W + 1]);
				}
			}

			// Border strip: clamp-to-edge.
			auto pix = [&](int x, int y) -> int {
				if (x < 0) x = 0; else if (x >= W) x = W - 1;
				if (y < 0) y = 0; else if (y >= H) y = H - 1;
				return p[y * W + x];
			};
			auto edge = [&](int x, int y) {
				out[y * W + x] = op(
					pix(x - 1, y - 1), pix(x, y - 1), pix(x + 1, y - 1),
					pix(x - 1, y    ), pix(x, y    ), pix(x + 1, y    ),
					pix(x - 1, y + 1), pix(x, y + 1), pix(x + 1, y + 1));
			};

			// Top and bottom rows (full width).
			for (int x = 0; x < W; ++x) edge(x, 0);
			for (int x = 0; x < W; ++x) edge(x, H - 1);

			// Left and right columns (corners excluded -- already done above).
			for (int y = 1; y < H - 1; ++y)
			{
				edge(0, y);
				edge(W - 1, y);
			}
		}

		/// <summary>
		/// Apply a 3x3 kernel to `in`, writing the clamped 8-bit result into `out`.
		/// Kernel is in row-major order.
		/// </summary>
		template<typename T>
		static void Apply3x3(Image& out, const Image& in, const T kernel[9])
		{
			Stencil3x3<Pixel8>(out.data, in,
				[kernel](int p00, int p01, int p02,
				         int p10, int p11, int p12,
				         int p20, int p21, int p22) -> Pixel8 {
					T v = p00 * kernel[0] + p01 * kernel[1] + p02 * kernel[2]
					    + p10 * kernel[3] + p11 * kernel[4] + p12 * kernel[5]
					    + p20 * kernel[6] + p21 * kernel[7] + p22 * kernel[8];
					if (v < T(0))   v = T(0);
					if (v > T(255)) v = T(255);
					return static_cast<Pixel8>(v);
				});
		}

		/// <summary>
		/// Apply a square 2D kernel of any odd size to `in`, writing the clamped
		/// 8-bit result into `out`.  Kernel is in row-major order.
		/// </summary>
		template<typename T>
		static void Apply(Image& out, const Image& in, int kernelSize, const T* kernel)
		{
			const int W = in.width;
			const int H = in.height;
			const int HALF = kernelSize / 2;
			const Pixel8* p = in.data;

			auto clamp = [](T v) -> Pixel8 {
				if (v < T(0))   v = T(0);
				if (v > T(255)) v = T(255);
				return static_cast<Pixel8>(v);
			};

			// Hot interior: no boundary checks.
			for (int y = HALF; y < H - HALF; ++y)
			{
				for (int x = HALF; x < W - HALF; ++x)
				{
					T sum = 0;
					int k = 0;
					for (int dy = -HALF; dy <= HALF; ++dy)
					{
						const int row = (y + dy) * W;
						for (int dx = -HALF; dx <= HALF; ++dx)
							sum += static_cast<T>(p[row + x + dx]) * kernel[k++];
					}
					out.data[y * W + x] = clamp(sum);
				}
			}

			// Border strips: clamp-to-edge.
			auto edge = [&](int x, int y) {
				T sum = 0;
				int k = 0;
				for (int dy = -HALF; dy <= HALF; ++dy)
				{
					int yy = y + dy;
					if (yy < 0) yy = 0; else if (yy >= H) yy = H - 1;
					const int row = yy * W;
					for (int dx = -HALF; dx <= HALF; ++dx)
					{
						int xx = x + dx;
						if (xx < 0) xx = 0; else if (xx >= W) xx = W - 1;
						sum += static_cast<T>(p[row + xx]) * kernel[k++];
					}
				}
				out.data[y * W + x] = clamp(sum);
			};

			for (int y = 0;        y < HALF;     ++y) for (int x = 0; x < W; ++x) edge(x, y);
			for (int y = H - HALF; y < H;        ++y) for (int x = 0; x < W; ++x) edge(x, y);
			for (int y = HALF;     y < H - HALF; ++y)
			{
				for (int x = 0;        x < HALF; ++x) edge(x, y);
				for (int x = W - HALF; x < W;    ++x) edge(x, y);
			}
		}

		/// <summary>
		/// Apply a 1D kernel as a separable 2D convolution: a horizontal pass
		/// into an internal scratch buffer, then a vertical pass into `out`.
		/// Useful for Gaussian-class kernels where 2D = 1D_h * 1D_v.
		/// </summary>
		template<typename T>
		static void ApplySeparable(Image& out, const Image& in, int kernelSize, const T* kernel1D)
		{
			const int W = in.width;
			const int H = in.height;
			const int HALF = kernelSize / 2;
			const Pixel8* p = in.data;

			auto clamp = [](T v) -> Pixel8 {
				if (v < T(0))   v = T(0);
				if (v > T(255)) v = T(255);
				return static_cast<Pixel8>(v);
			};

			std::vector<T> scratch(in.size);

			// Horizontal pass: in -> scratch.
			for (int y = 0; y < H; ++y)
			{
				const int row = y * W;
				for (int x = HALF; x < W - HALF; ++x)
				{
					T sum = 0;
					for (int k = 0; k < kernelSize; ++k)
						sum += static_cast<T>(p[row + x + k - HALF]) * kernel1D[k];
					scratch[row + x] = sum;
				}
				auto hEdge = [&](int x) {
					T sum = 0;
					for (int k = 0; k < kernelSize; ++k)
					{
						int xx = x + k - HALF;
						if (xx < 0) xx = 0; else if (xx >= W) xx = W - 1;
						sum += static_cast<T>(p[row + xx]) * kernel1D[k];
					}
					scratch[row + x] = sum;
				};
				for (int x = 0;        x < HALF; ++x) hEdge(x);
				for (int x = W - HALF; x < W;    ++x) hEdge(x);
			}

			// Vertical pass: scratch -> out.
			for (int y = HALF; y < H - HALF; ++y)
			{
				for (int x = 0; x < W; ++x)
				{
					T sum = 0;
					for (int k = 0; k < kernelSize; ++k)
						sum += scratch[(y + k - HALF) * W + x] * kernel1D[k];
					out.data[y * W + x] = clamp(sum);
				}
			}
			auto vEdge = [&](int x, int y) {
				T sum = 0;
				for (int k = 0; k < kernelSize; ++k)
				{
					int yy = y + k - HALF;
					if (yy < 0) yy = 0; else if (yy >= H) yy = H - 1;
					sum += scratch[yy * W + x] * kernel1D[k];
				}
				out.data[y * W + x] = clamp(sum);
			};
			for (int y = 0;        y < HALF; ++y) for (int x = 0; x < W; ++x) vEdge(x, y);
			for (int y = H - HALF; y < H;    ++y) for (int x = 0; x < W; ++x) vEdge(x, y);
		}
	};
}


#endif // CONVOLUTION_HPP
