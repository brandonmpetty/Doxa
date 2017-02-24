#include "CppUnitTest.h"
#include "../Palette.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{		
	TEST_CLASS(PaletteTests)
	{
	public:
		
		TEST_METHOD(PaletteTest)
		{
			const Pixel32 rgb = Palette::RGB(10, 21, 32);
			const Pixel32 rgba = Palette::RGBA(10, 21, 32, 43);
			const int gray = Palette::Gray(rgba);

			// Compaire that the colors are equivolent
			Assert::AreEqual(Palette::Red(rgb), Palette::Red(rgba));
			Assert::AreEqual(Palette::Green(rgb), Palette::Green(rgba));
			Assert::AreEqual(Palette::Blue(rgb), Palette::Blue(rgba));

			// Get individual colors from Pixel
			Assert::AreEqual(Palette::Red(rgba), 10);
			Assert::AreEqual(Palette::Green(rgba), 21);
			Assert::AreEqual(Palette::Blue(rgba), 32);

			// Update Alpha
			Assert::AreEqual(Palette::Alpha(rgb), 255);
			Assert::AreEqual(Palette::Alpha(rgba), 43);
			Assert::AreEqual(Palette::UpdateAlpha(rgb, 43), rgba);

			// Gray Values
			Assert::IsFalse(Palette::IsGray(rgba));
			Assert::IsTrue(gray <= 255);
		}

		TEST_METHOD(PaletteGrayTest)
		{
			for (int r = 0; r <= 255; ++r)
				for (int g = 0; g <= 255; ++g)
					for (int b = 0; b <= 255; ++b)
						Assert::IsTrue(Palette::Gray(r, g, b) <= 255);
		}

	};
}
