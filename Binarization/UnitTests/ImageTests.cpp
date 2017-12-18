#include "CppUnitTest.h"
#include "../Image.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(ImageTests)
	{
	public:

		TEST_METHOD(ImageTest)
		{
			Image image(3, 2);

			// Set pixel values for image
			image.data[0] = 0xff0000;
			image.data[1] = 0x00ff00;
			image.data[2] = 0x0000ff;
			image.data[3] = 0x00ffff;
			image.data[4] = 0xff00ff;
			image.data[5] = 0xffff00;

			// Verify each pixel
			Assert::AreEqual(image.Pixel(0, 0), image.data[0]);
			Assert::AreEqual(image.Pixel(1, 0), image.data[1]);
			Assert::AreEqual(image.Pixel(2, 0), image.data[2]);
			Assert::AreEqual(image.Pixel(0, 1), image.data[3]);
			Assert::AreEqual(image.Pixel(1, 1), image.data[4]);
			Assert::AreEqual(image.Pixel(2, 1), image.data[5]);

			// Out of bounds pixel
			Assert::AreEqual(image.Pixel(0, 3, 0xf0f0f0), (Pixel32)0xf0f0f0);

			// Copy Image
			Image copy(image);
			Assert::AreEqual(copy.height, image.height);
			Assert::AreEqual(copy.width, image.width);
			Assert::IsNotNull(copy.data);

			// Create a scope to trigger the reference image destructor
			{
				// Create Image Reference
				Image reference = Image::Reference(image.width, image.height, image.data);
				Assert::AreEqual(reference.height, image.height);
				Assert::AreEqual(reference.width, image.width);
				Assert::AreEqual(reference.data, image.data);

				// Set pixel value from coordinate.
				image.Pixel(1, 1) = 0xf0f0f0;
				Assert::AreEqual(image.Pixel(1, 1), (Pixel32)0xf0f0f0);
				Assert::AreEqual(copy.Pixel(1, 1), (Pixel32)0xff00ff); // Copy should not change.
				Assert::AreEqual(reference.Pixel(1, 1), image.Pixel(1, 1)); // Reference should change

				// Copy a memory managed Image but no longer manage the memory
				Image deepReference = Image(reference, true);
				deepReference.Pixel(1, 1) = 0xffffff;
				Assert::AreEqual(reference.Pixel(1, 1), (Pixel32)0xf0f0f0); // Reference should not change
			}

			// Reference should not free our image storage
			Assert::AreEqual(image.Pixel(1, 1), (Pixel32)0xf0f0f0);
		}
	};
}
