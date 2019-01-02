#include <functional>
#include "CppUnitTest.h"
#include "../Parameters.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(ParametersTests)
	{
	public:
		TEST_METHOD(ParametersGetTest)
		{
			Parameters param({ {"x", 1}, {"y", 1.1 } });

			// Int Exists
			int x = param.Get("x", 4);
			Assert::AreEqual(1, x);

			// Double Exists
			double y = param.Get("y", 2.2);
			Assert::AreEqual(1.1, y, 0.0001);

			// Does not exist
			int z = param.Get("z", 4);
			Assert::AreEqual(4, z);
		}

		TEST_METHOD(ParametersSetTest)
		{
			Parameters param({ { "z", 4 } });

			// Set Int
			param.Set("x", 1);
			Assert::AreEqual(1, param.Get("x", 22));

			// Set Double
			param.Set("y", 1.1);
			Assert::AreEqual(1.1, param.Get("y", 22.22), 0.0001);

			// Set Existing Value
			param.Set("z", 5);
			Assert::AreEqual(5, param.Get("z", 22));
		}
	};
}

