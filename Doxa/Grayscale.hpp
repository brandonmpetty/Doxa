// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef GRAYSCALE_HPP
#define GRAYSCALE_HPP

#include <algorithm>
#include "Types.hpp"


namespace Doxa
{
	/// <summary>
	/// This entire class was greatly influenced by the Color-to-Grayscale article written by Christopher Kanan and 
	/// Garrison W. Cottrell.
	/// 
	/// With the PNM input format, despite the Ref 709 gamma correction scheme specified, there are many variants.
	/// The most important aspect to know, however, is not  the format of sRBG, 601, 709, etc, but if gamma correction
	/// has been applied in the first place.  Reading in a PNM color image, one should assume it is gamma corrected.
	/// 
	/// The top 2 grayscale formulas found by Kanan and Cottrell are Gleam and Intensity'.
	/// The great news is that these share the same formula which is very fast, referred to here as Mean(...).
	/// The bad news is that if you are given a Linear RGB set, your Intensity' is now just Intensity and drops you
	/// from 2nd place to 8th.  Luckily, for color images, you should safely assume you are recieving gamma corrected
	/// RGB values.
	/// 
	/// Because we should assume some form of gamma correction, we are also far more likely to get the result of Luma
	/// than Luminance (exact formula isn't as important), which should be reassuring as that would be a drop from 5th
	/// 10th.  But to show the power of correctly controlling your gamma conversion, if one applied that same formula to
	/// to Linear RGB values and then gamma corrected after the fact, you end up with the 3rd place finisher, Luminance'.
	/// Basically the same formula can take you from 3rd to 10th place, simply due to gamma correction!
	/// 
	/// It is therefore this naieve author's opinion that as long as you start with gamma corrected RGB values, you
	/// should be set regardless of your exact gamma compression scheme, or grayscale conversion formula you want to try.
	/// It is also recommended that when you finally do convert to Grayscale, that you apply your image processing 
	/// algorithms to an uncompressed, linear, grayscale image.
	/// 
	/// Also see:
	/// https://en.wikipedia.org/wiki/Grayscale
	/// https://blog.johnnovak.net/2016/09/21/what-every-coder-should-know-about-gamma/
	/// </summary>
	/// <remarks>"Color-to-Grayscale: Does the Method Matter in Image Recognition?", 2012.</remarks>
	class Grayscale
	{
	public:
		/// <summary>
		/// Linear Y value that will be sRGB gamma corrected
		/// </summary>
		static inline void LinearTosRgb(double& y)
		{
			y =  y <= 0.0031308 ? y * 12.92 : Gamma((1.055 * y - 0.055) / 1.055, 2.4);
		}

		static inline void LinearTo709(double& y)
		{
			y = y <= 0.0018 ? y * 4.5 : Gamma((1.099 * y - 0.099) / 1.055, 2.2);
		}


		/// <summary>
		/// RGB are sRGB Gamma Corrected values that will be turned Linear.
		/// </summary>
		static inline void sRgbToLinear(double& r, double& g, double& b)
		{
			auto toLinear = [&](const double channel)
			{
				return channel <= 0.04045 ? channel / 12.92 : std::pow((channel + 0.055) / 1.055, 2.4);
			};

			r = toLinear(r);
			g = toLinear(g);
			b = toLinear(b);
		}

		/// <summary>
		/// RGB are linear values that this function will gamma correct.
		/// </summary>
		static inline void Gamma(double& r, double& g, double& b, const double gamma = 2.2)
		{
			r = Gamma(r, gamma);
			g = Gamma(g, gamma);
			b = Gamma(b, gamma);
		}

		static inline double Gamma(const double channel, const double gamma = 2.2)
		{
			return std::pow(channel, 1 / gamma);
		}

		/// <summary>
		/// The formula used by the Qt framework which is used by our default.
		/// Note: There are serious unanswered questions around this formula.
		/// </summary>
		template<typename T>
		static inline constexpr T Qt(T r, T g, T b)
		{
			return (r * 11 + g * 16 + b * 5) / 32;
		}

		/// <summary>
		/// If RGB are Linear, this calculates the Intensity.
		/// If RGB are Gamma Corrected, this calculates Gleam.
		/// </summary>
		template<typename T>
		static inline constexpr T Mean(T r, T g, T b)
		{
			return (r + g + b) / 3;
		}

		/// <summary>
		/// BT601 calculates the Luma when RGB are Gamma Corrected. The Y' from Y'UV & Y'IQ.
		/// When Linear, can generate the luminance Y from the CIE 1931 XYZ color space.
		/// Aka: NTSC RGB formula, with a White Point of "C".
		/// </summary>
		template<typename T>
		static inline constexpr T BT601(T r, T g, T b)
		{
			return 0.2989 * r + 0.5865 * g + 0.1144 * b;
		}

		/// <summary>
		/// BT709 calculates the Luma when RGB are Gamma Corrected. The Y' from Y'UV & Y'IQ.
		/// When Linear, can generate the luminance Y from the CIE 1931 XYZ color space.
		/// Aka sRGB formula, with a White Point of "D65".
		/// The D50 weights, for ICC, are: 0.2225045  0.7168786  0.0606169
		/// </summary>
		template<typename T>
		static inline constexpr T BT709(T r, T g, T b)
		{
			return 0.2126 * r + 0.7152 * g + 0.0722 * b;
		}

		/// <summary>
		/// BT2100 calculates the Luma when RGB are Gamma Corrected. The Y' from Y'UV & Y'IQ.
		/// When Linear, can generate the luminance Y from the CIE 1931 XYZ color space.
		/// Has a White Point of "D65".
		/// </summary>
		template<typename T>
		static inline constexpr T BT2100(T r, T g, T b)
		{
			return 0.2627 * r + 0.6780 * g + 0.0593 * b;
		}

		/// <summary>
		/// HSV V Value.  Calculates Value when RGB are Linear.
		/// Gamma Corrected RGB values produce the same result as a Gamma Corrected Value.
		/// </summary>
		template<typename T>
		static inline constexpr T Value(T r, T g, T b)
		{
			return std::max({ r, g, b });
		}

		/// <summary>
		/// HLS L Value.  Calculates Lightness when RGB are Linear.
		/// </summary>
		/// <remarks>Named Luster as to not be confused by CIE Lightness</remarks>
		template<typename T>
		static inline constexpr T Luster(T r, T g, T b)
		{
			return (std::max({ r, g, b }) + std::min({ r, g, b })) / 2;
		}

		/// <summary>
		/// The purpose of MinAvg is to produce a grayscale image whose values are less sensitive to multi color text.
		/// It was introduced for the first AdOtsu algorithm.
		/// </summary>
		/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010</remarks>
		template<typename T>
		static inline constexpr T MinAvg(T r, T g, T b)
		{
			return (Mean(r, g, b) + std::min({ r, g, b })) / 2;
		}

		/// <summary>
		/// CIELAB & CIELUV L Value.  Calculates Lightness when RGB are Linear.
		/// Notice that this has built in gamma correction.
		/// Note: BT709 has a White Point of D65.  The ICC calls for D50.
		/// This is also known as a chromatic adaptation transformation (CAT).
		/// See:  https://drafts.csswg.org/css-color/#rgb-to-lab
		/// </summary>
		template<typename T>
		static inline constexpr T Lightness(T r, T g, T b)
		{
			const auto addGamma = [&](double y)
			{
				return y > 0.00885 ? Gamma(y, 3) : 7.78703 * y + 0.13793;
			};

			return (1.0 / 100) * (116 * addGamma(BT709(r, g, b)) - 16);
		}

		/// <summary>
		/// CIELAB & CIELUV L Value.  Calculates Lightness when RGB are non-linear
		/// sRGB values.  Since almost every RGB color value we will see is sRGB,
		/// this formula should be used instead of Lightness(r,g,b).
		/// </summary>
		static inline Pixel8 sRgbToLightness(Pixel8 r, Pixel8 g, Pixel8 b)
		{
			// These are sRGB values
			double red = (double)r / 255;
			double green = (double)g / 255;
			double blue = (double)b / 255;

			// Convert to Linear
			Grayscale::sRgbToLinear(red, green, blue);

			// Convert to CIE L - Lightness
			const double y = Grayscale::Lightness(red, green, blue);

			// Return normalized Y value
			return y * 255;
		}
	};

	/// <summary>
	/// A normalized implementation since we are usually not working with decimal.
	/// This assumes that RGB are Linear values.  It is unlike you will use this
	/// since 709 or sRGB to Linear will give you a 0 to 1 decimal value.
	/// 
	/// C++ Note: Some compilers do not like template specialization defined in the class.
	/// </summary>
	template<>
	inline constexpr Pixel8 Grayscale::Lightness(Pixel8 r, Pixel8 g, Pixel8 b)
	{
		return Lightness((double)r / 255, (double)g / 255, (double)b / 255) * 255;
	}
}


#endif // GRAYSCALE_HPP
