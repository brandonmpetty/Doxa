#include "CppUnitTest.h"
#include "../Region.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(RegionTests)
	{
	public:

		TEST_METHOD(RegionConstructorTest)
		{
			Region::Point upperLeft(0, 0);
			Region::Point bottomRight(10, 15);
			Region regionPoints(upperLeft, bottomRight);

			Region regionCoords(0, 0, 10, 15);

			Region regionWH(11, 16);

			Region regionWindow(0, 0, 15);

			Assert::IsTrue(regionPoints == regionCoords);
			Assert::IsTrue(regionCoords == regionWH);
			Assert::AreEqual(15 * 15, regionWindow.Area());
		}

		TEST_METHOD(RegionTest)
		{
			Region region(10, 20, 30, 40);

			Assert::AreEqual(region.Height(), 21);
			Assert::AreEqual(region.Width(), 21);
			Assert::AreEqual(region.Area(), 441);
		}

		TEST_METHOD(RegionInRegionTest)
		{
			Region regionParent(10, 10, 50, 50);
			Region regionChild(20, 20, 40, 40);
			Region regionNeighbor(50, 10, 100, 50);
			Region regionThirdCousin(40, 15, 60, 45);

			Assert::IsTrue(regionParent.InRegion(regionParent));
			Assert::IsTrue(regionParent.InRegion(regionChild));
			Assert::IsFalse(regionParent.InRegion(regionNeighbor));
			Assert::IsFalse(regionParent.InRegion(regionThirdCousin));
		}

		TEST_METHOD(RegionPointTest)
		{
			Region region1(0, 0, 10, 10);
			Region region2(10, 10, 20, 20);

			Assert::IsFalse(region1.upperLeft == region1.bottomRight);
			Assert::IsFalse(region1.upperLeft == region2.upperLeft);
			Assert::IsFalse(region1.upperLeft == region2.bottomRight);
			Assert::IsTrue(region1.bottomRight == region2.upperLeft);
		}
	};
}
