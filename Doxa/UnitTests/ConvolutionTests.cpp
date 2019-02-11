#include "TestUtilities.hpp"
#include "../Convolution.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(ConvolutionTests)
	{
	public:
		TEST_METHOD(ConvolutionConvolve3x3Test)
		{
			// Setup
			const Pixel8 data[9] = {
				1, 1, 1,
				1, 1, 1,
				1, 1, 1
			};
			Image image(3, 3, data);

			const int kernel[9] = {
				1, 1, 1,
				1, 1, 1,
				1, 1, 1
			};

			// Test
			Convolution::ConvolutionImage convolutionImage(image.size);
			Convolution convolution;
			convolution.Convolve(convolutionImage, image, 3, kernel);

			// Ensure that all elements equal 9
			bool isMiscalculated = std::any_of(std::begin(convolutionImage), std::end(convolutionImage), [&](int value)
			{
				return value != 9;
			});
			Assert::IsFalse(isMiscalculated);
		}

		TEST_METHOD(ConvolutionConvolve5x5Test)
		{
			// Setup
			const Pixel8 data[9] = {
				1, 1, 1,
				1, 1, 1,
				1, 1, 1
			};
			Image image(3, 3, data);

			// Note:  Yes, the kernel is larger than our entire image.
			const int kernel[25] = {
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1
			};

			// Test
			Convolution::ConvolutionImage convolutionImage(image.size);
			Convolution convolution;
			convolution.Convolve(convolutionImage, image, 5, kernel);

			// Ensure that all elements equal 200
			bool isMiscalculated = std::any_of(std::begin(convolutionImage), std::end(convolutionImage), [&](int value)
			{
				return value != 25;
			});
			Assert::IsFalse(isMiscalculated);
		}
	};
}
