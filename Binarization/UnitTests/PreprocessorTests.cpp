#include "CppUnitTest.h"
#include "../Preprocessor.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(PreprocessorTests)
	{
	public:

		TEST_METHOD(ToGreyScaleTest)
		{
			Image image(3, 2);

			// Set pixel values for image
			image.data[0] = 0xff0000;
			image.data[1] = 0x00ff00;
			image.data[2] = 0x0000ff;
			image.data[3] = 0x00ffff;
			image.data[4] = 0xff00ff;
			image.data[5] = 0xffff00;

			// Turn image into grayscale
			Preprocessor::ToGreyScale(image);

			// Assert all pixels are gray
			for (auto i = 0; i < image.size; ++i)
			{
				Assert::IsTrue(image.data[i] <= 255);
			}
		}
	};
}
