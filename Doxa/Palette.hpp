// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <cmath>
#include "Types.hpp"


namespace Doxa
{
	/// <summary>
	/// Palette provides many pixel manipulation routines for getting and setting colors.
	/// Note that it is tuned only for Little Endian systems.
	/// On Big Endian systems, make sure to avoid any methods taking a Pixel32.
	/// </summary>
	class Palette
	{
	public:
		// RGBA 32b Pixel Decoding
		static inline constexpr int Red(Pixel32 rgba) { return (rgba & 0xff); }
		static inline constexpr int Green(Pixel32 rgba) { return ((rgba >> 8) & 0xff); }
		static inline constexpr int Blue(Pixel32 rgba) { return ((rgba >> 16) & 0xff); }
		static inline constexpr int Alpha(Pixel32 rgba) { return rgba >> 24; }

		// RGBA to Pixel
		static inline constexpr Pixel32 RGB(int r, int g, int b)
		{
			return (0xffu << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
		}

		static inline constexpr Pixel32 RGBA(int r, int g, int b, int a)
		{
			return ((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
		}

		static inline constexpr Pixel32 UpdateAlpha(Pixel32 rgba, int a)
		{
			return (rgba & 0x00ffffff) | (a << 24);
		}

		/// <summary>
		/// Using the RGB color space, calculate the difference between two colors.
		/// The results should be very similar to equations using the more common L*u*v* color space.
		/// </summary>
		/// <remarks>https://www.compuphase.com/cmetric.htm</remarks>
		/// <returns></returns>
		static inline int ColorDistance(Pixel32 left, Pixel32 right)
		{
			const int rmean = (Red(left) + Red(right)) / 2;
			const int r = Red(left) - Red(right);
			const int g = Green(left) - Green(right);
			const int b = Blue(left) - Blue(right);

			return std::sqrt( ((2 + rmean/256) * r*r) + (4 * g*g) + ((2 + (255 - rmean)/256) * b*b) );
		}

		static inline constexpr bool IsGray(Pixel32 rgba)
		{
			return Blue(rgba) == Green(rgba) && Blue(rgba) == Red(rgba);
		}

		// Black and White
		static const Pixel8 Black = 0;
		static const Pixel8 White = 255;
	};
}


#endif // PALETTE_HPP
