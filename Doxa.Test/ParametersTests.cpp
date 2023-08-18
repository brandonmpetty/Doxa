#include "pch.h"


namespace Doxa::UnitTests
{
	TEST(ParametersTests, ParametersGetTest)
	{
		Parameters param({ {"x", 1}, {"y", 1.1 } });

		// Int Exists
		int x = param.Get("x", 4);
		EXPECT_EQ(1, x);

		// Double Exists
		double y = param.Get("y", 2.2);
		EXPECT_NEAR(1.1, y, 0.0001);

		// Does not exist
		int z = param.Get("z", 4);
		EXPECT_EQ(4, z);
	}

	TEST(ParametersTests, ParametersSetTest)
	{
		Parameters param({ { "z", 4 } });

		// Verify it was initialized
		EXPECT_EQ(param.Get("z", 0), 4);

		// Set Int
		param.Set("x", 1);
		EXPECT_EQ(1, param.Get("x", 22));

		// Set Double
		param.Set("y", 1.1);
		EXPECT_NEAR(1.1, param.Get("y", 22.22), 0.0001);

		// Set Existing Value
		param.Set("z", 5);
		EXPECT_EQ(5, param.Get("z", 22));
	}

	TEST(ParametersTests, ParametersParser)
	{
		// Parsed as a JSON string
		Parameters params = Parameters::FromJson(R"({"window": 75, "custom": "test", "k": -0.01})");

		EXPECT_EQ(params.Get("window", 0), 75);
		EXPECT_NEAR(params.Get("k", 0.0), -0.01, 0.0001);
	}
}

