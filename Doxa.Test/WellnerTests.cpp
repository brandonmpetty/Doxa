#include "pch.h"
#include "ImageFixture.hpp"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class WellnerTests : public ImageFixture {};

	// Exposes the protected template helper so we can drive the shift and
	// divide implementations directly, side by side.
	class WellnerTestHarness : public Wellner
	{
	public:
		WellnerTestHarness() : Wellner() {}
		using Wellner::Process;
	};

	// When 's' is a power of two, `sum >> log2(s)` and `sum / s` are the
	// same arithmetic expression -- the shift is purely an optimization
	// the compiler can't make for us at runtime.  The two specializations
	// of Process<UseShift> must therefore produce byte-identical output
	// for every pixel.  Any divergence between them is an implementation
	// bug, so we sweep a handful of representative powers of two against
	// the test image and require an exact match.
	TEST_F(WellnerTests, WellnerShiftMatchesDivide)
	{
		const int t = 15;

		for (int s : { 4, 16, 64, 256 })
		{
			SCOPED_TRACE("s = " + std::to_string(s));

			Image outputShift(image.width, image.height);
			Image outputDivide(image.width, image.height);

			WellnerTestHarness::Process<true>(outputShift, image, s, t);
			WellnerTestHarness::Process<false>(outputDivide, image, s, t);

			TestUtilities::AssertImages(outputShift, outputDivide);
		}
	}
}
