/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cmath>
#include "Types.hpp"


namespace Binarization
{
	class Palette
	{
	public:
		// ARGB 32b Pixel Decoding
		static inline constexpr int Alpha(Pixel32 rgba) { return rgba >> 24; }
		static inline constexpr int Red(Pixel32 rgba) { return ((rgba >> 16) & 0xff); }
		static inline constexpr int Green(Pixel32 rgba) { return ((rgba >> 8) & 0xff); }
		static inline constexpr int Blue(Pixel32 rgba) { return (rgba & 0xff); }

		// ARGB to Pixel
		static inline constexpr Pixel32 RGB(int r, int g, int b)
		{
			return (0xffu << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
		}

		static inline constexpr Pixel32 RGBA(int r, int g, int b, int a)
		{
			return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
		}

		static inline constexpr Pixel32 UpdateAlpha(Pixel32 rgba, int a)
		{
			return (rgba & 0x00ffffff) | (a << 24);
		}

		// Gray Scale Helpers
		static inline constexpr int Gray(int r, int g, int b)
		{
			return (r * 11 + g * 16 + b * 5) / 32;
		}

		static inline constexpr int Gray(Pixel32 rgba)
		{
			return Gray(Red(rgba), Green(rgba), Blue(rgba));
		}

		static inline constexpr bool IsGray(Pixel32 rgba)
		{
			return Blue(rgba) == Green(rgba) && Blue(rgba) == Red(rgba);
		}

		// Black and White
		static const Pixel32 Black = 4278190080; //RGB(0, 0, 0);
		static const Pixel32 White = 4294967295; //RGB(255, 255, 255);
		static const Pixel32 BlackGrayScale = 0;
		static const Pixel32 WhiteGrayScale = 255;
	};
}


#endif // PIXEL_HPP
