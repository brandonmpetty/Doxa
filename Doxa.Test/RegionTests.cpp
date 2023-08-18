#include "pch.h"


namespace Doxa::UnitTests
{
	TEST(RegionTests, RegionConstructorTest)
	{
		Region::Point upperLeft(0, 0);
		Region::Point bottomRight(10, 15);
		Region regionPoints(upperLeft, bottomRight);

		Region regionCoords(0, 0, 10, 15);

		Region regionWH(11, 16);

		Region regionWindow(0, 0, 15);

		EXPECT_TRUE(regionPoints == regionCoords);
		EXPECT_TRUE(regionCoords == regionWH);
		EXPECT_EQ(15 * 15, regionWindow.Area());
	}

	TEST(RegionTests, RegionTest)
	{
		Region region(10, 20, 30, 40);

		EXPECT_EQ(region.Height(), 21);
		EXPECT_EQ(region.Width(), 21);
		EXPECT_EQ(region.Area(), 441);
	}

	TEST(RegionTests, RegionInRegionTest)
	{
		Region regionParent(10, 10, 50, 50);
		Region regionChild(20, 20, 40, 40);
		Region regionNeighbor(50, 10, 100, 50);
		Region regionThirdCousin(40, 15, 60, 45);

		EXPECT_TRUE(regionParent.InRegion(regionParent));
		EXPECT_TRUE(regionParent.InRegion(regionChild));
		EXPECT_FALSE(regionParent.InRegion(regionNeighbor));
		EXPECT_FALSE(regionParent.InRegion(regionThirdCousin));
	}

	TEST(RegionTests, RegionPointTest)
	{
		Region region1(0, 0, 10, 10);
		Region region2(10, 10, 20, 20);

		EXPECT_FALSE(region1.upperLeft == region1.bottomRight);
		EXPECT_FALSE(region1.upperLeft == region2.upperLeft);
		EXPECT_FALSE(region1.upperLeft == region2.bottomRight);
		EXPECT_TRUE(region1.bottomRight == region2.upperLeft);
	}
}
