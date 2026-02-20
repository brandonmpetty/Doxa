// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Image.hpp"
#include "Parameters.hpp"
#include "Palette.hpp"
#include "SIMDOps.hpp"


namespace Doxa
{
	/// <summary>
	/// Algorithm Interface - Useful if you want to dynamically instantiate an algorithm.
	/// </summary>
	class IAlgorithm
	{
	public:
		virtual ~IAlgorithm() { /* Virtual DTOR */ };

		/// <summary>
		/// Sets the Gray Scale image that will later be used to generate a binary image.
		/// This allows the derived class to also initialize the image with any one time calculations.
		/// </summary>
		/// <param name="grayScaleImageIn">An Image object containing gray scale content</param>
		virtual void Initialize(const Image& grayScaleImageIn) = 0;

		/// <summary>
		/// Takes the initialized Gray Scale image and returns back a Binary image by reference.
		/// The Binary image memory should already be allocated before being passed by reference.
		/// This method was designed to be called repeatedly with different parameters.
		/// </summary>
		/// <param name="binaryImageOut">An Image object with preallocated memory which will store the output</param>
		/// <param name="parameters">Any parameters the algorithm may need</param>
		virtual void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters()) = 0;
	};


	/// <summary>
	/// This is a base class for all of our binarization algorithms.
	/// It uses the Curiously Recurring Template Pattern for compile time inheritance.
	/// </summary>
	template<typename BinaryAlgorithm>
	class Algorithm : public IAlgorithm
	{
	public:
		/// <summary>
		/// Sets the Gray Scale image that will later be used to generate a binary image.
		/// This allows the derived class to also initialize the image with any one time calculations.
		/// </summary>
		/// <param name="grayScaleImageIn">An Image object containing gray scale content</param>
		virtual void Initialize(const Image& grayScaleImageIn)
		{
			this->grayScaleImageIn = grayScaleImageIn.Reference();
		}

		/// <summary>
		/// A convenience method for taking in a Gray Scale image /w params and returning a Binary image.
		/// </summary>
		static Image ToBinaryImage(const Image& grayScaleImageIn, const Parameters& parameters = Parameters())
		{
			// Generate space for the binary image
			Image binaryImageOut(grayScaleImageIn.width, grayScaleImageIn.height);

			// Run Binarization Algorithm
			BinaryAlgorithm algorithm;
			algorithm.Initialize(grayScaleImageIn);
			algorithm.ToBinary(binaryImageOut, parameters);

			// The Move semantics allow this our underlying image to move without being copied
			return binaryImageOut;
		}

		/// <summary>
		/// A convenience method for safely converting a Gray Scale image to Binary.
		/// Note: You may need to create a temp image and copy it, depending on your algorithm.
		/// </summary>
		static void UpdateToBinary(Image& image, const Parameters& parameters = Parameters())
		{
			BinaryAlgorithm algorithm;
			algorithm.Initialize(image);
			algorithm.ToBinary(image, parameters);
		}

	protected:
		Image grayScaleImageIn;
	};


	/// <summary>
	/// The base class for all Global Thresholding algorithms.
	/// </summary>
	template<typename BinaryAlgorithm>
	class GlobalThreshold : public Algorithm<BinaryAlgorithm>
	{
	public:
		/// <summary>
		/// Calculates and returns the global threshold of the image.
		/// </summary>
		/// <returns>A global binarization threshold value</returns>
		virtual Pixel8 Threshold(const Image& grayScaleImage, const Parameters& parameters = Parameters()) = 0;

		/// <summary>
		/// Global binarization based on a single threshold
		/// </summary>
		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const Pixel8 threshold = Threshold(Algorithm<BinaryAlgorithm>::grayScaleImageIn, parameters);
			const int size = Algorithm<BinaryAlgorithm>::grayScaleImageIn.size;
			const Pixel8* input = Algorithm<BinaryAlgorithm>::grayScaleImageIn.data;
			Pixel8* output = binaryImageOut.data;

			#if defined(DOXA_SIMD)
				ToBinary_SIMD(input, output, size, threshold);
			#else
				ToBinary_STD(input, output, size, threshold);
			#endif
		}

		/// <summary>
		/// Scalar implementation of threshold binarization - always available
		/// </summary>
		static void ToBinary_STD(const Pixel8* input, Pixel8* output, int size, Pixel8 threshold)
		{
			for (int idx = 0; idx < size; ++idx) {
				output[idx] = input[idx] <= threshold ? Palette::Black : Palette::White;
			}
		}

#if defined(DOXA_SIMD)
		/// <summary>
		/// SIMD implementation of threshold binarization - only available when SIMD is enabled
		/// </summary>
		static void ToBinary_SIMD(const Pixel8* input, Pixel8* output, int size, Pixel8 threshold)
		{
			using namespace SIMD;

			int idx = 0;
			const int simd_end = size - (size % SIMD_WIDTH);
			vec128 threshold_vec = VEC_SPLAT_U8(threshold);

			for (; idx < simd_end; idx += SIMD_WIDTH) {
				vec128 pixels = VEC_LOAD(input + idx);

				// Compare: mask = (pixels <= threshold) -> 0xFF if true, 0x00 if false
				// Use min to implement <= comparison for unsigned bytes
				vec128 mask = VEC_CMPEQ_U8(VEC_MIN_U8(pixels, threshold_vec), pixels);

				// Since Black=0x00 and White=0xFF, result is simply NOT(mask)
				// mask=0xFF -> ~0xFF = 0x00 (black), mask=0x00 -> ~0x00 = 0xFF (white)
				VEC_STORE(output + idx, VEC_NOT(mask));
			}

			// Handle remaining pixels with scalar
			for (; idx < size; ++idx) {
				output[idx] = input[idx] <= threshold ? Palette::Black : Palette::White;
			}
		}
#endif // DOXA_SIMD
	};
}


#endif //ALGORITHMS_HPP
