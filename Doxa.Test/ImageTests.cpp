#include "pch.h"


namespace Doxa::UnitTests
{
	class ImageTest : public ::testing::Test
	{
	protected:
		Image image;

		void SetUp() override
		{
			image = Image(3, 2);

			// Set pixel values for image
			image.data[0] = 0xF0;
			image.data[1] = 0xF1;
			image.data[2] = 0xF2;
			image.data[3] = 0xF3;
			image.data[4] = 0xF4;
			image.data[5] = 0xF5;
		}
	};

	TEST_F(ImageTest, ImagePixelTest)
	{
		// Verify each pixel
		EXPECT_EQ(image.Pixel(0, 0), image.data[0]);
		EXPECT_EQ(image.Pixel(1, 0), image.data[1]);
		EXPECT_EQ(image.Pixel(2, 0), image.data[2]);
		EXPECT_EQ(image.Pixel(0, 1), image.data[3]);
		EXPECT_EQ(image.Pixel(1, 1), image.data[4]);
		EXPECT_EQ(image.Pixel(2, 1), image.data[5]);

		// Out of bounds pixel
		EXPECT_EQ(image.Pixel(0, 3, 0xF6), (Pixel8)0xF6);
	}

	TEST_F(ImageTest, ImageCopyCTORTest)
	{
		// Copy Image using Copy CTOR
		Image copy(image);
		EXPECT_FALSE(copy.managedExternally);
		EXPECT_EQ(copy.height, image.height);
		EXPECT_EQ(copy.width, image.width);
		EXPECT_NE(nullptr, copy.data);
		EXPECT_NE(copy.data, image.data);

		// Copy Image using Copy CTOR - Identical to above due to direct instantiation
		Image copy2 = copy;
		EXPECT_FALSE(copy2.managedExternally);
		EXPECT_NE(copy.data, copy2.data);
	}

	TEST_F(ImageTest, ImageMoveCTORTest)
	{
		Image move = std::invoke([]() {
			Image iLiveOnTheStack;
			return iLiveOnTheStack; // Triggers our Move CTOR
		});

		EXPECT_FALSE(move.managedExternally);
	}

	TEST_F(ImageTest, ImageExternalReferenceTest)
	{
		// Copy Image using Copy CTOR
		Image copy(image);

		// Create a scope to trigger the reference image destructor
		{
			// Create Image Reference
			Image reference = Image::Reference(image.width, image.height, image.data);
			EXPECT_TRUE(reference.managedExternally);
			EXPECT_EQ(reference.height, image.height);
			EXPECT_EQ(reference.width, image.width);
			EXPECT_EQ(reference.data, image.data);

			// Set pixel value from coordinate.
			image.Pixel(1, 1) = 0xFA;
			EXPECT_EQ(image.Pixel(1, 1), (Pixel8)0xFA);
			EXPECT_EQ(copy.Pixel(1, 1), (Pixel8)0xF4); // Copy should not change.
			EXPECT_EQ(reference.Pixel(1, 1), image.Pixel(1, 1)); // Reference should change

			// Copy a memory managed Image but no longer manage the memory
			Image deepReference = Image(reference);
			EXPECT_FALSE(deepReference.managedExternally);
			EXPECT_NE(image.data, deepReference.data);

			// Reference should not change
			deepReference.Pixel(1, 1) = 0xFF;
			EXPECT_EQ(reference.Pixel(1, 1), (Pixel8)0xFA);
		}

		// Reference should not free our image storage
		EXPECT_EQ(image.Pixel(1, 1), (Pixel8)0xFA);
	}

	TEST_F(ImageTest, ImageReferenceTest)
	{
		// Create a reference from an Image object
		Image reference = image.Reference();
		EXPECT_EQ(reference.data, image.data);
		EXPECT_TRUE(reference.managedExternally);
	}

	TEST_F(ImageTest, ImageCopyAssignmentOperatorTest)
	{
		// Create a reference from an Image object
		Image reference = image.Reference();

		// Ensure our Copy Assignment Operator issues a deep copy
		Image copy;
		copy = reference;
		EXPECT_FALSE(copy.managedExternally);

		// Copy should now be a deep copy of image
		EXPECT_EQ(image.width, copy.width);
		EXPECT_NE(image.data, copy.data);
		EXPECT_EQ(copy.Pixel(1, 1), (Pixel8)0xF4);
	}
}
