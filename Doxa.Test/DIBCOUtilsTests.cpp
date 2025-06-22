#include "pch.h"
#include <sstream>
#include <string>
#include "DIBCOUtils.hpp"


namespace Doxa::UnitTests
{
	TEST(DIBCOUtilsTests, ReadWeightsTest)
	{
		// Note: A sample copied from a DIBCO .dat file
		std::string weights = "0.000000  1.000000  0.750000  0.500000";
		std::stringstream stream(weights);

		auto result = DIBCOUtils::ReadWeights(stream, 4);

		EXPECT_EQ(result.size(), 4);
		EXPECT_EQ(result.at(0), 0.0);
		EXPECT_EQ(result.at(1), 1.0);
		EXPECT_EQ(result.at(2), 0.75);
		EXPECT_EQ(result.at(3), 0.5);
	}
}
