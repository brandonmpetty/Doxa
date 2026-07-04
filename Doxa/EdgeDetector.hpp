// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef EDGEDETECTOR_HPP
#define EDGEDETECTOR_HPP

#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Image.hpp"
#include "Types.hpp"
#include "Parameters.hpp"
#include "Convolution.hpp"
#include "Filter.hpp"


namespace Doxa
{
	/// <summary>
	/// Edge detectors.
	///
	///   Sobel      Fused single-pass gradient magnitude using the L1 norm
	///              |Gx| + |Gy| (no sqrt).  Output is uint8 edge magnitude
	///              clamped to [0, 255]: sharp edges show as bright pixels,
	///              flat regions as 0.
	///
	///   Laplacian  Fused single-pass second-derivative response with the
	///              standard 8-neighbor stencil ([-1 -1 -1; -1 8 -1; -1 -1 -1]).
	///              Output is std::abs(value) clamped to [0, 255].  Taking the
	///              absolute value preserves both polarities of zero-crossing.
	///
	///   Canny      The classic 1986 pipeline:
	///                - Gaussian blur ->
	///                - Sobel-style gradient with quantized direction ->
	///                - non-maximum suppression ->
	///                - double-threshold classification ->
	///                - hysteresis edge tracking via BFS from strong seeds.
	///              Output is a binary edge map (0 or 255).
	///
	/// Canny parameters (via the standard Parameters key-value object):
	///   "gaussian-size" int    default 5     -- must be odd
	///   "sigma"         double default 0.0   -- 0 means derive from size
	///   "low"           int    default 50    -- weak-edge threshold (inclusive)
	///   "high"          int    default 150   -- strong-edge threshold (inclusive)
	/// </summary>
	class EdgeDetector
	{
	public:
		static void Sobel(Image& out, const Image& in)
		{
			Convolution::Stencil3x3<Pixel8>(out.data, in,
				[](int p00, int p01, int p02,
				   int p10, int p11, int p12,
				   int p20, int p21, int p22) -> Pixel8 {
					const int gx = -p00 + p02 - 2 * p10 + 2 * p12 - p20 + p22;
					const int gy = -p00 - 2 * p01 - p02 + p20 + 2 * p21 + p22;
					const int mag = std::abs(gx) + std::abs(gy);
					return static_cast<Pixel8>(std::min(mag, 255));
				});
		}

		static void Laplacian(Image& out, const Image& in)
		{
			Convolution::Stencil3x3<Pixel8>(out.data, in,
				[](int p00, int p01, int p02,
				   int p10, int p11, int p12,
				   int p20, int p21, int p22) -> Pixel8 {
					const int v = -p00 - p01 - p02
					              - p10 + 8 * p11 - p12
					              - p20 - p21 - p22;
					return static_cast<Pixel8>(std::min(std::abs(v), 255));
				});
		}

		static void Canny(Image& out, const Image& in, const Parameters& params = Parameters{})
		{
			const int    gaussianSize = params.Get("gaussian-size", 5);
			const double sigma        = params.Get("sigma",         0.0);
			const int    low          = params.Get("low",           50);
			const int    high         = params.Get("high",          150);

			const int W = in.width;
			const int H = in.height;
			const int N = in.size;

			// 1. Gaussian blur the input into out (out is reused as scratch).
			Filter::Gaussian(out, in, gaussianSize, sigma);

			// 2. Sobel-style gradient magnitude + direction bin on the blurred
			//    image.  Open-coded rather than using Stencil3x3 because we
			//    write two outputs per pixel (mag and dir), which the
			//    single-output op can't express -- and going direct lets
			//    gx/gy stay in registers.
			//
			//    Direction bin encodes which pair of neighbors NMS compares:
			//      0  W / E             (gradient ~horizontal)
			//      1  NE / SW           (gradient ~"/", signs of gx,gy differ)
			//      2  N / S             (gradient ~vertical)
			//      3  NW / SE           (gradient ~"\", signs of gx,gy match)
			//
			//    Split angles: tan(67.5 deg) = 2.4142.  Using double avoids
			//    atan2 and keeps the per-pixel cost at one mul + a compare.
			std::vector<int> mag(N);
			std::vector<uint8_t> dir(N);

			auto compute = [&](int p00, int p01, int p02,
			                   int p10, int p11, int p12,
			                   int p20, int p21, int p22, int i) {
				const int gx = -p00 + p02 - 2 * p10 + 2 * p12 - p20 + p22;
				const int gy = -p00 - 2 * p01 - p02 + p20 + 2 * p21 + p22;
				const int ax = std::abs(gx);
				const int ay = std::abs(gy);
				mag[i] = ax + ay;

				if      (ax > 2.4142 * ay) dir[i] = 0;
				else if (ay > 2.4142 * ax) dir[i] = 2;
				else if ((gx ^ gy) < 0)    dir[i] = 1;
				else                       dir[i] = 3;
			};

			const Pixel8* p = out.data;

			// Hot interior: every neighbor read is in-bounds.
			for (int y = 1; y < H - 1; ++y)
			{
				const int row = y * W;
				for (int x = 1; x < W - 1; ++x)
				{
					const int i = row + x;
					compute(
						p[i - W - 1], p[i - W], p[i - W + 1],
						p[i - 1],     p[i],     p[i + 1],
						p[i + W - 1], p[i + W], p[i + W + 1],
						i);
				}
			}

			// Border strip: clamp-to-edge.  These values are read by NMS at
			// pixels one step in from the border (e.g. (1,1) reads (0,0)).
			auto pix = [&](int x, int y) -> int {
				if (x < 0) x = 0; else if (x >= W) x = W - 1;
				if (y < 0) y = 0; else if (y >= H) y = H - 1;
				return p[y * W + x];
			};
			auto edge = [&](int x, int y) {
				compute(
					pix(x - 1, y - 1), pix(x, y - 1), pix(x + 1, y - 1),
					pix(x - 1, y    ), pix(x, y    ), pix(x + 1, y    ),
					pix(x - 1, y + 1), pix(x, y + 1), pix(x + 1, y + 1),
					y * W + x);
			};

			for (int x = 0; x < W; ++x) edge(x, 0);
			for (int x = 0; x < W; ++x) edge(x, H - 1);
			for (int y = 1; y < H - 1; ++y)
			{
				edge(0, y);
				edge(W - 1, y);
			}

			// 4. Non-maximum suppression along the quantized direction,
			//    double-threshold classification, and hysteresis seeding
			//    fused into one pass.  Writes 0 / 128 / 255 directly into
			//    out and collects strong-pixel seeds for the BFS.
			std::vector<int> seeds;
			seeds.reserve(N / 16);
			NonMaxSuppressAndClassify(out, seeds, mag.data(), dir.data(), W, H, low, high);

			// 5. Hysteresis edge tracking: BFS from strong seeds promotes
			//    8-connected weak (128) neighbors to strong (255).  Any
			//    remaining weak pixel is then cleared to 0.
			Hysteresis(out, seeds, W, H);
		}

	protected:
		static void NonMaxSuppressAndClassify(
			Image& out, std::vector<int>& seeds,
			const int* mag, const uint8_t* dir,
			int w, int h, int low, int high)
		{
			Pixel8* o = out.data;

			// Border pixels can't be safely compared along the gradient
			// direction.  Zero them outright -- clamping would falsely
			// suppress real edges adjacent to the image border.
			for (int x = 0; x < w; ++x)
			{
				o[x] = 0;
				o[(h - 1) * w + x] = 0;
			}
			for (int y = 1; y < h - 1; ++y)
			{
				o[y * w] = 0;
				o[y * w + (w - 1)] = 0;
			}

			for (int y = 1; y < h - 1; ++y)
			{
				const int row = y * w;
				for (int x = 1; x < w - 1; ++x)
				{
					const int i = row + x;
					const int m = mag[i];

					int a, b;
					switch (dir[i])
					{
						case 0:  a = mag[i - 1];     b = mag[i + 1];     break;  // W, E
						case 1:  a = mag[i - w + 1]; b = mag[i + w - 1]; break;  // NE, SW
						case 2:  a = mag[i - w];     b = mag[i + w];     break;  // N, S
						default: a = mag[i - w - 1]; b = mag[i + w + 1]; break;  // NW, SE
					}

					// Asymmetric comparison: keeps ridges, drops plateau
					// duplicates.  m must be strictly greater than one side
					// and at least as great as the other.
					const int s = (m > a && m >= b) ? m : 0;

					if (s >= high)     { o[i] = 255; seeds.push_back(i); }
					else if (s >= low) o[i] = 128;
					else               o[i] = 0;
				}
			}
		}

		static void Hysteresis(Image& out, std::vector<int>& seeds, int w, int h)
		{
			Pixel8* o = out.data;

			// BFS: any 8-connected weak (128) neighbor of a strong pixel
			// becomes strong itself.  out is its own visited marker --
			// promoting a weak pixel to 255 prevents it being re-queued.
			while (!seeds.empty())
			{
				const int i = seeds.back();
				seeds.pop_back();
				const int y = i / w;
				const int x = i - y * w;

				for (int dy = -1; dy <= 1; ++dy)
				{
					const int ny = y + dy;
					if (ny < 0 || ny >= h) continue;
					for (int dx = -1; dx <= 1; ++dx)
					{
						if (dx == 0 && dy == 0) continue;
						const int nx = x + dx;
						if (nx < 0 || nx >= w) continue;
						const int ni = ny * w + nx;
						if (o[ni] == 128)
						{
							o[ni] = 255;
							seeds.push_back(ni);
						}
					}
				}
			}

			// Any weak pixel not reached by a strong seed is not an edge.
			const int n = w * h;
			for (int i = 0; i < n; ++i)
				if (o[i] == 128) o[i] = 0;
		}
	};
}


#endif // EDGEDETECTOR_HPP
