#ifndef TESTUTILITIES_HPP
#define TESTUTILITIES_HPP

#include "pch.h"


namespace Doxa::UnitTests
{
	class TestUtilities
	{
	public:
		static std::string ProjectFolder()
		{
			// GTest will work in the current directory, but IDEs will usually put it in a diff spot.
			// Make sure to set the current working directory to the Doxa.Test folder!
			auto folder = fs::current_path() / "Resources";

			if (!fs::exists(folder))
			{
				throw "Could not find resource folder.";
			}

			return folder.string() + "/";
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
			EXPECT_EQ(0, std::memcmp(image.data, data, sizeof(Pixel8) * image.size));
		}

		static void AssertImages(const Image& imageA, const Image& imageB)
		{
			EXPECT_EQ(imageA.size, imageB.size);

			EXPECT_EQ(0, std::memcmp(imageA.data, imageB.data, sizeof(Pixel8) * imageA.size));
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
				SUCCEED() << buffer;
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
				SUCCEED() << buffer;
			}

			return false;
		}
	};
}

#endif // TESTUTILITIES_HPP
