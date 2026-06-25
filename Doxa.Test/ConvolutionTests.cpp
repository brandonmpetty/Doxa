#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class ConvolutionTests : public ::testing::Test
	{
	protected:
		// 5x5 with a non-trivial pattern, so an "identity" kernel actually has
		// something to preserve.  Values picked to span interior and border.
		static constexpr int kW = 5;
		static constexpr int kH = 5;
		const Pixel8 kData[25] = {
			 10,  20,  30,  40,  50,
			 60,  70,  80,  90, 100,
			110, 120, 130, 140, 150,
			160, 170, 180, 190, 200,
			210, 220, 230, 240, 250,
		};
	};

	TEST_F(ConvolutionTests, Stencil3x3CenterOpEqualsInput)
	{
		// An op that returns the center pixel reproduces the input exactly --
		// the cheapest way to confirm the stencil hits every pixel and the
		// clamp-to-edge border code is wired up correctly.
		const Image in(kW, kH, kData);
		Image out(kW, kH);

		Convolution::Stencil3x3<Pixel8>(out.data, in,
			[](int, int, int,
			   int, int p11, int,
			   int, int, int) -> Pixel8 {
				return static_cast<Pixel8>(p11);
			});

		TestUtilities::AssertImageData(out, kData);
	}

	TEST_F(ConvolutionTests, Apply3x3IdentityKernelEqualsInput)
	{
		// Identity 3x3 kernel: only the center weight is 1.
		const int kernel[9] = {
			0, 0, 0,
			0, 1, 0,
			0, 0, 0,
		};

		const Image in(kW, kH, kData);
		Image out(kW, kH);

		Convolution::Apply3x3<int>(out, in, kernel);

		TestUtilities::AssertImageData(out, kData);
	}

	TEST_F(ConvolutionTests, ApplyIdentityKernelEqualsInput)
	{
		// Identity 5x5 kernel exercises the variable-size code path and its
		// 2-pixel-wide border strip.
		int kernel[25] = {};
		kernel[12] = 1; // center of a 5x5 kernel

		const Image in(kW, kH, kData);
		Image out(kW, kH);

		Convolution::Apply<int>(out, in, 5, kernel);

		TestUtilities::AssertImageData(out, kData);
	}

	TEST_F(ConvolutionTests, ApplySeparableIdentityKernelEqualsInput)
	{
		// Identity separable kernel: 1D [0, 1, 0] applied horizontally and
		// then vertically is still identity.  Exercises both passes and the
		// scratch buffer plumbing.
		const double kernel1D[3] = { 0.0, 1.0, 0.0 };

		const Image in(kW, kH, kData);
		Image out(kW, kH);

		Convolution::ApplySeparable<double>(out, in, 3, kernel1D);

		TestUtilities::AssertImageData(out, kData);
	}
}
