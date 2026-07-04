// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef DRDM_HPP
#define DRDM_HPP

#include <algorithm>
#include "Image.hpp"
#include "Palette.hpp"
#include "Region.hpp"
#include "LocalWindow.hpp"
#include "SIMDOps.hpp"


namespace Doxa
{
	/// <summary>
	/// The Distance-Reciprocal Distortion Measure (DRDM) Algorithm: Haiping Lu, Jian Wang, A.C. Kot, Y.Q. Shi
	///
    /// Accuracy Note:
    /// This implementation will differ from the DIBO metrics implementation by roughly ~1e-5.
    /// Their MATLAB implemenation suffers from float drift while ours offers full precision.
    /// Cause: Their "sum_DRDk = sum_DRDk + DRDk" accumulates the ENTIRE image in float32.
    /// Real world exmple: Our 1.9521414 (1.9521) vs DIBCO Metrics 1.9521665 (1.9522)
    /// 
    /// Also, the original author's MATLAB implementation, Haiping Lu, over penalizes edge pixels in a way that
    /// would make following its implementation differ too greatly from DIBCO's numbers.
    /// 
    /// </summary>
	/// <remarks>"An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.</remarks>
	class DRDM
	{
	public:
		static double CalculateDRDM(const Image& controlImage, const Image& experimentImage)
		{
			const uint64_t sumDRDk = SumDRDkForMismatchedPixels(controlImage, experimentImage);

			// The weights are pre-scaled by 1e9 (see Wm), so divide it back out here.
			return sumDRDk / (double)(NUBN(controlImage) * 1000000000ULL);
		}

	protected:
        static constexpr int N = 5;
        static constexpr int R = N / 2;

        // Normalized Weighted Matrix (reciprocal Euclidean distance to the center, normalized to sum of 1).
        // Values are pre-multiplied by 1,000,000,000 so the whole calculation stays in exact integers and
        // avoids the floating-point drift described above. 9 significant figures track DRDM to ~1e-9.
        //
        // Overflow: This supports images up to ~1.8e10 pixels (~135000 x 135000) - an 18 gigapixel image.
        static constexpr uint32_t Wm[N * N] = {
            25582088, 32359066, 36178535, 32359066, 25582088,
            32359066, 51164175, 72357071, 51164175, 32359066,
            36178535, 72357071,        0, 72357071, 36178535,
            32359066, 51164175, 72357071, 51164175, 32359066,
            25582088, 32359066, 36178535, 32359066, 25582088
        };

        /// <summary>
		/// Sum DRDk for all mismatched pixels between control and experiment images.
        /// This is an optimized algorithm.
		/// </summary>
        static uint64_t SumDRDkForMismatchedPixels(const Image& control, const Image& experiment)
        {
            uint64_t sum = 0;
            const int w = control.width;
            const int h = control.height;

            const Pixel8* ctl = control.data;
            const Pixel8* exp = experiment.data;

            for (int y = 0; y < h; ++y)
            {
                const int row = y * w;

                // Clamp region - Y
                const int y0 = (y - R < 0) ? 0 : y - R;
                const int y1 = (y + R >= h) ? h - 1 : y + R;

                for (int x = 0; x < w; ++x)
                {
                    /* TODO: Validate that this is truly better on a wide range of images
                    // Compare 16 pixels at once for a ~20% speedup
                    // This is only beneficial if your images are very similar
                    if (x + 15 < w) // Read X + 15 More = 16
                    {
                        //if (VEC_ALL_EQ_U8(VEC_LOAD(ctl + row + x), VEC_LOAD(exp + row + x)))
                        if (memcmp(ctl + row + x, exp + row + x, 16) == 0) // No SIMD necessary
                        {
                            x += 15;
                            continue;
                        }
                    }
                    */

                    const Pixel8 g = exp[row + x];

                    if (ctl[row + x] == g)
                        continue;

                    uint32_t localSum = 0;

                    // Clamp region - X
                    const int x0 = (x - R < 0) ? 0 : x - R;
                    const int x1 = (x + R >= w) ? w - 1 : x + R;

                    // Walk neighborhood
                    for (int ny = y0; ny <= y1; ++ny)
                    {
                        const int base = ny * w;
                        const int wy = ny - (y - R);
                        const int wyRow = wy * 5;

                        for (int nx = x0; nx <= x1; ++nx)
                        {                    
                            const int wx = nx - (x - R);

                            // Compute weight index
                            const uint32_t weight = Wm[wyRow + wx];

                            // Branchless add:
                            localSum += weight * (ctl[base + nx] != g);
                        }
                    }

                    sum += localSum;
                }
            }

            return sum;
        }


        /// <summary>
        /// Calculate the number of non-uniform MxM windows (both white and black pixels).
        /// 
        /// This uses an over-engineer set of algorithms that attempt to make this otherwise
        /// simple calculation as fast as possible.  Because M = 8 is a standard, this path
        /// has been optimized.
        /// 
        /// NOTE: DIBCO Metrics do not process partial windows
        /// NOTE: DRDM defaults to 8x8 windows, which DIBCO Metrics uses
        /// 
        /// </summary>
		static unsigned int NUBN(const Image& controlImage, const int M = 8)
		{
		    // Use optimized path for standard 8x8 blocks
            if (M == 8)
            {
                #if defined(DOXA_SIMD)
                    return NUBN_SIMD_8x8(controlImage);
                #else
                    return NUBN_STD_8x8(controlImage);
                #endif
            }
			
			return NUBN_STD(controlImage, M);
		}

        /// <summary>
        /// Calculate the number of non-uniform NxN windows (both white and black pixels).
        /// NOTE: DIBCO Metrics do not process partial windows
        /// 
        /// Algorithm
        /// This is a memory optimized algorithm that iterates through an image pixel by pixel
        /// not window by window.  It has many early exit optimizations.
        /// 
        /// To accomplish this it stores a special row for keeping track of the state of each
        /// window as we iterate across each window.
        /// 
        /// </summary>
        static int NUBN_STD(const Image& controlImage, int N)
        {
            const int numWindowCols = controlImage.width / N;
            const int numWindowRows = controlImage.height / N;
    
            if (numWindowCols == 0 || numWindowRows == 0)
            {
                return 0;
            }

            constexpr int MIXED = -1;  // Sentinel: valid sums are always >= 0
            const int whiteRowSum = 255 * N;
    
            std::vector<int> expected(numWindowCols);
            int totalMixed = 0;
    
            const uint8_t* bandPtr = controlImage.data;
            const int bandStride = N * controlImage.width;
    
            for (int wy = 0; wy < numWindowRows; ++wy)
            {
                int mixedCount = 0;
                const uint8_t* px = bandPtr;
        
                // === Row 0: Classify all windows ===
                for (int wx = 0; wx < numWindowCols; ++wx)
                {
                    int sum = 0;
                    for (int i = 0; i < N; ++i)
                    {
                        sum += px[i];
                    }
                    px += N;
            
                    if (sum == 0 || sum == whiteRowSum)
                    {
                        expected[wx] = sum;
                    } 
                    else
                    {
                        expected[wx] = MIXED;
                        ++mixedCount;
                    }
                }
        
                // === Rows 1 to N-1: Verify uniformity ===
                const Pixel8* rowPtr = bandPtr + controlImage.width;
                for (int localY = 1; localY < N; ++localY)
                {
                    if (mixedCount == numWindowCols) break;
            
                    px = rowPtr;
                    for (int wx = 0; wx < numWindowCols; ++wx)
                    {
                        const int exp = expected[wx];
                        if (exp == MIXED) {
                            px += N;
                            continue;
                        }
                
                        int sum = 0;
                        for (int i = 0; i < N; ++i)
                        {
                            sum += px[i];
                        }
                        px += N;
                
                        if (sum != exp)
                        {
                            expected[wx] = MIXED;
                            ++mixedCount;
                        }
                    }

                    rowPtr += controlImage.width;
                }
        
                totalMixed += mixedCount;
                bandPtr += bandStride;
            }
    
            return totalMixed;
        }

        /// <summary>
        /// Calculate the number of non-uniform 8x8 windows
        /// NOTE: DIBCO Metrics do not process partial windows
        /// 
        /// Algorithm
        /// This algorithm is identical to NUBN_STD, except we are able to further optimize it
        /// based on the known 8x8 window size, standard for DRDM.
        /// 
        /// These memory tricks get this implentation about as close to SIMD speed as possible.
        /// 
        /// </summary>
        static int NUBN_STD_8x8(const Image& controlImage)
        {
            constexpr uint64_t ALL_BLACK = 0x0000000000000000ULL;
            constexpr uint64_t ALL_WHITE = 0xFFFFFFFFFFFFFFFFULL;
            constexpr uint64_t MIXED = 1ULL;  // Sentinel: impossible for uniform row
            constexpr unsigned int N = 8;
    
            const int numWindowCols = controlImage.width / N;   // NOTE: Compiler will optimize to >> 3
            const int numWindowRows = controlImage.height / N;
            const int rowStride = controlImage.width;
            const int bandStride = rowStride * N;	            // NOTE: Compiler will optimize to << 3
    
            if (numWindowCols == 0 || numWindowRows == 0)
            {
                return 0;
            }
    
            std::vector<uint64_t> expected(numWindowCols);
            int totalMixed = 0;
    
            const Pixel8* bandPtr = controlImage.data;
    
            for (int wy = 0; wy < numWindowRows; ++wy)
            {
                int mixedCount = 0;
                const Pixel8* px = bandPtr;
        
                // Row 0: classify all windows (no branches for state check)
                for (int wx = 0; wx < numWindowCols; ++wx, px += N)
                {
                    uint64_t row;
                    std::memcpy(&row, px, N);
            
                    if (row == ALL_BLACK || row == ALL_WHITE)
                    {
                        expected[wx] = row;

                    } else
                    {
                        expected[wx] = MIXED;
                        ++mixedCount;
                    }
                }
        
                // Rows 1-7: verify uniformity (no UNCLASSIFIED check)
                const Pixel8* rowPtr = bandPtr + rowStride;
                for (int localY = 1; localY < N; ++localY)
                {
                    if (mixedCount == numWindowCols) break;
            
                    px = rowPtr;
                    for (int wx = 0; wx < numWindowCols; ++wx, px += N)
                    {
                        const uint64_t exp = expected[wx];
                        if (exp == MIXED) continue;
                
                        uint64_t row;
                        std::memcpy(&row, px, N);
                
                        if (row != exp)
                        {
                            expected[wx] = MIXED;
                            ++mixedCount;
                        }
                    }

                    rowPtr += rowStride;
                }
        
                totalMixed += mixedCount;
                bandPtr += bandStride;
            }
    
            return totalMixed;
        }

#if defined(DOXA_SIMD)

		/// <summary>
		/// SIMD implementation of NUBN for 8x8 blocks
		/// </summary>
        static unsigned int NUBN_SIMD_8x8(const Image& controlImage)
        {
            unsigned int nubn = 0;
            const int M = 8;
            const int stride = controlImage.width;
            const int columns = stride / M;
            const int rows = controlImage.height / M;
            const Pixel8* rowPtr = controlImage.data;

            for (int row = 0; row < rows; ++row)
            {
                const Pixel8* blockPtr = rowPtr;
                for (int column = 0; column < columns; ++column)
                {
                    if (!IsBlock8x8Uniform(blockPtr, stride))
                    {
                        ++nubn;
                    }

                    blockPtr += M;
                }

                rowPtr += stride * M;
            }

            return nubn;
        }

        /// <summary>
        /// Check if an 8x8 block is uniform (all pixels match reference value)
        /// SIMD Required
        /// </summary>
		static inline bool IsBlock8x8Uniform(const uint8_t* ptr, int stride)
		{
			SIMD::vec128 ref = VEC_SPLAT_U8(*ptr);

			for (int row = 0; row < 8; row += 2)
            {
				SIMD::vec128 rows = VEC_LOAD_2x64(ptr, ptr + stride);
				if (!VEC_ALL_EQ_U8(rows, ref)) return false;
				ptr += stride * 2;
			}

			return true;
		}

#endif // DOXA_SIMD
	};
}


#endif //DRDM_HPP
