#include <chrono>
#include <functional>
#include "../Image.hpp"
#include "../Palette.hpp"
#include "../PNM.hpp"
#include "CppUnitTest.h"

// Used for expanding macro based directives
#define STR(x) #x
#define EXPAND(x) STR(x)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Doxa::UnitTests
{
	class TestUtilities
	{
	public:
		static double Time(std::function<void()> predicate)
		{
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

			predicate();

			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

			return time_span.count(); // In Seconds
		}

		static void AssertImageData(const Image& image, const Pixel8* data)
		{
			Assert::AreEqual(0, std::memcmp(image.data, data, sizeof(Pixel8) * image.size));
		}

		static void AssertImages(const Image& imageA, const Image& imageB)
		{
			Assert::AreEqual(imageA.size, imageB.size);

			Assert::AreEqual(0, std::memcmp(imageA.data, imageB.data, sizeof(Pixel8) * imageA.size));
		}

		static void AssertImageFile(const Image& image, std::string filePath)
		{
			Image imageFromFile = PNM::Read(filePath);

			AssertImages(image, imageFromFile);
		}
	};
}
