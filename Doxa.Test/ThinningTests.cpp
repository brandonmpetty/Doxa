#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class ThinningTests : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			projFolder = TestUtilities::ProjectFolder();
			gt = PNM::Read(projFolder + "2JohnC1V3-GroundTruth.pbm");

			// Thinning expects 1 = foreground, 0 = background.  In the GT,
			// text is Palette::Black (0) and paper is Palette::White (255).
			mask.assign(gt.size, 0);
			for (int i = 0; i < gt.size; ++i)
				if (gt.data[i] == Palette::Black) mask[i] = 1;
		}

		static Image MaskToImage(const std::vector<uint8_t>& m, int w, int h)
		{
			Image out(w, h);
			for (int i = 0; i < out.size; ++i)
				out.data[i] = m[i] ? Palette::Black : Palette::White;
			return out;
		}

		Image gt;
		std::vector<uint8_t> mask;
		std::string projFolder;
	};

	TEST_F(ThinningTests, ThinningZhangSuenTest)
	{
		std::vector<uint8_t> skeleton;
		ZhangSuenThinning::Skeletonize(skeleton, mask, gt.width, gt.height);

		Image out = MaskToImage(skeleton, gt.width, gt.height);
		TestUtilities::AssertImageFile(out, projFolder + "2JohnC1V3-ZhangSuen.pbm");
	}

	TEST_F(ThinningTests, ThinningChenHsuTest)
	{
		std::vector<uint8_t> skeleton;
		ChenHsuThinning::Skeletonize(skeleton, mask, gt.width, gt.height);

		Image out = MaskToImage(skeleton, gt.width, gt.height);
		TestUtilities::AssertImageFile(out, projFolder + "2JohnC1V3-ChenHsu.pbm");
	}

	TEST_F(ThinningTests, ThinningLeeChenTest)
	{
		std::vector<uint8_t> skeleton;
		LeeChenThinning::Skeletonize(skeleton, mask, gt.width, gt.height);

		Image out = MaskToImage(skeleton, gt.width, gt.height);
		TestUtilities::AssertImageFile(out, projFolder + "2JohnC1V3-LeeChen.pbm");
	}
}
