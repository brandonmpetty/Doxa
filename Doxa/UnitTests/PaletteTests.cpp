#include "CppUnitTest.h"
#include "../Palette.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{		
	TEST_CLASS(PaletteTests)
	{
	public:
		
		TEST_METHOD(PaletteTest)
		{
			const Pixel32 rgb = Palette::RGB(10, 21, 32);
			const Pixel32 rgba = Palette::RGBA(10, 21, 32, 43);
			const Pixel32 gray = Palette::RGB(124, 124, 124);

			// Verify Endian
			Assert::AreEqual((Pixel32)0xFF20150A, rgb); // 0A = 10, 15 = 21, 20 = 32
			Assert::AreEqual((Pixel32)0x2B20150A, rgba); // 2B = 43

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
			Assert::IsTrue(Palette::IsGray(gray));
		}
	};
}
