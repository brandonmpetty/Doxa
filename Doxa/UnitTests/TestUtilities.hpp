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
		static std::string ProjectFolder()
		{
			// Obtain the project folder
			// Note: Tests are to be ran in VS.  If this is not the case, change how this is being set.
			//       This was done to avoid baking in the images into the .exe, or copying them on build.
			std::string projFolder = EXPAND(UNITTESTPRJ);
			projFolder.erase(0, 1); // Erase first quote
			projFolder.erase(projFolder.size() - 2); // Erase first quote and period, which is used to excape the trailing slash

			return projFolder;
		}

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

		static bool AssertImagesWithDetails(const Image& imageA, const Image& imageB)
		{
			char buffer[100];

			if (imageA.height != imageB.height || imageA.width != imageB.width)
			{
				std::snprintf(buffer, 100, "Image dimensions do not match.  %dx%d vs %dx%d", imageA.width, imageA.height, imageB.width, imageB.height);
				Logger::WriteMessage(buffer);
			}
			else
			{
				bool diffFound = false;
				int firstHeight = 0;
				int firstWidth = 0;
				int firstIndex = 0;
				int count = 0;

				for (int index = 0; index < imageA.size; index++)
				{
					if (imageA.data[index] != imageB.data[index])
					{
						if (!diffFound)
						{
							firstIndex = index;
							firstHeight = index / imageA.width;
							firstWidth = index % imageA.width;
							diffFound = true;
						}

						++count;
					}
				}

				// No differences found!
				if (!diffFound) return true;

				std::snprintf(buffer, 100, "%d difference(s) found. Example: Index %d, Width %d, Height %d.", count, firstIndex, firstWidth, firstHeight);
				Logger::WriteMessage(buffer);
			}

			return false;
		}
	};
}
