// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef MORPHOLOGY_HPP
#define MORPHOLOGY_HPP

#include <algorithm>
#include <cstring>
#include <vector>
#include "Image.hpp"


namespace Doxa
{
	/// <summary>
	/// Grayscale Erode, Dilate, Open, and Close over a square window.
	///
	/// A square window is separable: running a 1-D min/max filter across every row, then down every
	/// column of that result, produces the min/max of the full 2-D window.  The 1-D filter uses the
	/// van Herk / Gil-Werman (vHGW) algorithm, which costs about 3 comparisons per pixel no matter
	/// how large the window is.  One code path covers every window size.
	///
	/// vHGW, by example - a Dilate (max) with window size 3:
	///
	///   Line:    4 2 6 | 1 3 8 | 5     split into blocks as wide as the window
	///   Prefix:  4 4 6 | 1 3 8 | 5     running max, restarting at each block
	///   Suffix:  6 6 6 | 8 8 8 | 5     running max backwards, restarting at each block
	///
	/// Wherever the window lands, it covers the tail of one block and the head of the next.
	/// Suffix holds the max of any tail; Prefix holds the max of any head.  The window centered
	/// at position i is simply:  max(Suffix[i-1], Prefix[i+1])
	/// e.g. centered over the 1, the window {6,1,3} = max(Suffix[2], Prefix[4]) = max(6,3) = 6
	///
	/// Window edges are clipped at the image border, and even window sizes are widened by one,
	/// exactly like LocalWindow.
	/// </summary>
	/// <remarks>
	/// van Herk, "A fast algorithm for local minimum and maximum filters on rectangular and octagonal kernels", 1992.
	/// Gil, Werman, "Computing 2-D min, median, and max filters", 1993.
	/// </remarks>
	class Morphology
	{
	public:
		/// <summary>
		/// Open is simply Erode followed by Dilate.
		/// This can help reduce background noise.
		/// </summary>
		static void Open(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Erode(morphedImage, grayScaleImage, windowSize);
			Dilate(morphedImage, morphedImage, windowSize);
		}

		/// <summary>
		/// Close is simply Dilate followed by Erode.
		/// This can help fill holes in the foreground.
		/// </summary>
		static void Close(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Dilate(morphedImage, grayScaleImage, windowSize);
			Erode(morphedImage, morphedImage, windowSize);
		}

		/// <summary>
		/// Iterates through the gray scale image, recording the minimum value within the window.
		/// </summary>
		static void Erode(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Morph(morphedImage, grayScaleImage, windowSize, [](const Pixel8 a, const Pixel8 b) { 
				return (std::min)(a, b);
			});
		}

		/// <summary>
		/// Iterates through the grayscale image, recording the maximum value within the window.
		/// </summary>
		static void Dilate(Image& morphedImage, const Image& grayScaleImage, const int windowSize = 3)
		{
			Morph(morphedImage, grayScaleImage, windowSize, [](const Pixel8 a, const Pixel8 b) {
				return (std::max)(a, b);
			});
		}

	protected:
		/// <summary>
		/// Applies the 1-D vHGW filter to every row of the source, then down the columns of that result.
		/// The column pass works a whole row at a time, keeping memory access sequential and letting the
		/// compiler vectorize the element-wise min/max of adjacent rows.
		///
		/// Every buffer shares one geometry, so a single row offset indexes them all.  The morphed image
		/// doubles as working memory: it receives the row pass, folds into its own column prefix rows, and
		/// merges in place; only the column suffix rows need scratch.  Merging at row y reads prefix rows
		/// at y+half and beyond, which it has not yet overwritten.
		///
		/// The morphed image may safely be the same object as the gray scale image.
		/// </summary>
		template<typename MinMax>
		static void Morph(Image& morphedImage, const Image& grayScaleImage, const int windowSize, MinMax op)
		{
			const int width = grayScaleImage.width;
			const int height = grayScaleImage.height;
			const int half = windowSize / 2;
			const int window = half + half + 1;

			// Row pass: filter every row of the source into the output image
			std::vector<Pixel8> prefix(width), suffix(width);

			for (int row = 0; row < grayScaleImage.size; row += width)
			{
				FilterLine(morphedImage.data + row, grayScaleImage.data + row, width, half, prefix.data(), suffix.data(), op);
			}

			// Column pass: FilterLine again, at row granularity, one block of rows at a time.
			// Within each block, suffix rows are built bottom-up; prefix rows top-down, in place,
			// turning the output image into the prefix image.
			Image suffixImage(width, height);
			const int lastRow = (height - 1) * width;
			const int blockRows = window * width;

			for (int start = 0; start < grayScaleImage.size; start += blockRows)
			{
				const int blockLast = (std::min)(start + blockRows, grayScaleImage.size) - width;

				std::memcpy(suffixImage.data + blockLast, morphedImage.data + blockLast, width);
				for (int row = blockLast - width; row >= start; row -= width)
				{
					CombineRows(suffixImage.data + row, suffixImage.data + row + width, morphedImage.data + row, width, op);
				}

				for (int row = start + width; row <= blockLast; row += width)
				{
					CombineRows(morphedImage.data + row, morphedImage.data + row - width, width, op);
				}
			}

			// Each output row looks half a window up (suffix) and half a window down (prefix)
			const int lastBlock = ((height - 1) / window) * window;
			const int halfRows = half * width;

			for (int y = 0, row = 0; y < height; ++y, row += width)
			{
				if (y < half) // memmove: on an image shorter than half a window, this can copy a row onto itself
					std::memmove(morphedImage.data + row, morphedImage.data + (std::min)(row + halfRows, lastRow), width);
				else if (y + half < height)
					CombineRows(morphedImage.data + row, suffixImage.data + row - halfRows, morphedImage.data + row + halfRows, width, op);
				else if (y - half >= lastBlock)
					std::memcpy(morphedImage.data + row, suffixImage.data + row - halfRows, width);
				else
					CombineRows(morphedImage.data + row, suffixImage.data + row - halfRows, morphedImage.data + lastRow, width, op);
			}
		}

		/// <summary>
		/// The 1-D vHGW filter: out[i] = min/max of in[i-half .. i+half], clipped to the line.
		/// Prefix and suffix are caller-provided scratch space, one line wide.
		/// Out may alias in: the merge step below reads only prefix and suffix.
		/// </summary>
		template<typename MinMax>
		static void FilterLine(Pixel8* out, const Pixel8* in, const int n, const int half, Pixel8* prefix, Pixel8* suffix, MinMax op)
		{
			const int window = half + half + 1;

			// prefix[i] spans from the start of i's block; suffix[i] spans to the end of i's block
			for (int start = 0; start < n; start += window)
			{
				const int end = (std::min)(start + window, n);

				prefix[start] = in[start];
				for (int i = start + 1; i < end; ++i)
				{
					prefix[i] = op(prefix[i - 1], in[i]);
				}

				suffix[end - 1] = in[end - 1];
				for (int i = end - 2; i >= start; --i)
				{
					suffix[i] = op(suffix[i + 1], in[i]);
				}
			}

			const int lastBlock = ((n - 1) / window) * window;
			const int leftEdge = (std::min)(half, n);
			int i = 0;

			// Left edge: the clipped window [0, i+half] sits inside the first block
			for (; i < leftEdge; ++i)
			{
				out[i] = prefix[(std::min)(i + half, n - 1)];
			}

			for (; i + half < n; ++i)
			{
				out[i] = op(suffix[i - half], prefix[i + half]);
			}

			// Right edge: suffix spans the clipped window [i-half, n-1], unless it starts before the last block
			for (; i < n; ++i)
			{
				out[i] = (i - half >= lastBlock) ? suffix[i - half] : op(suffix[i - half], prefix[n - 1]);
			}
		}

		/// <summary>
		/// dst[i] = op(a[i], b[i]) - the column pass runs on whole rows at a time.
		/// Dst may alias b: each element is read before it is written.
		/// </summary>
		template<typename MinMax>
		static void CombineRows(Pixel8* dst, const Pixel8* a, const Pixel8* b, const int n, MinMax op)
		{
			for (int i = 0; i < n; ++i)
			{
				dst[i] = op(a[i], b[i]);
			}
		}

		/// <summary>
		/// dst[i] = op(dst[i], a[i]) - in-place variant, used to build the column prefix rows.
		/// </summary>
		template<typename MinMax>
		static void CombineRows(Pixel8* dst, const Pixel8* a, const int n, MinMax op)
		{
			for (int i = 0; i < n; ++i)
			{
				dst[i] = op(dst[i], a[i]);
			}
		}
	};
}


#endif //MORPHOLOGY_HPP
