// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef GRAYSCALE_HPP
#define GRAYSCALE_HPP

#include <algorithm>
#include <array>
#include <optional>
#include <type_traits>
#include <vector>
#include "Types.hpp"


namespace Doxa
{
	using GrayscaleFunc = Pixel8(*)(Pixel8, Pixel8, Pixel8);
	using XYZ = std::tuple<float, float, float>;
	using Lab = std::tuple<float, float, float>;

	enum GrayscaleAlgorithms
	{
		MEAN = 0,
		QT = 1,
		BT601 = 2,
		BT709 = 3,
		BT2100 = 4,
		VALUE = 5,
		LUSTER = 6,
		LIGHTNESS = 7,
		MINAVG = 8,
		LABDIST = 9
	};

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
	/// from 2nd place to 8th.  Luckily, for color images, you should safely assume you are receiving gamma corrected
	/// RGB values.
	/// 
	/// Because we should assume some form of gamma correction, we are also far more likely to get the result of Luma
	/// than Luminance (exact formula isn't as important), which should be reassuring as that would be a drop from 5th
	/// 10th.  But to show the power of correctly controlling your gamma conversion, if one applied that same formula to
	/// to Linear RGB values and then gamma corrected after the fact, you end up with the 3rd place finisher, Luminance'.
	/// Basically the same formula can take you from 3rd to 10th place, simply due to gamma correction!
	/// 
	/// It is therefore this naive author's opinion that as long as you start with gamma corrected RGB values, you
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
		/// Return a fast linear conversion LUT for uncompressing a color space
		/// </summary>
		static std::array<float, 256> LinearLUT()
		{
			std::array<float, 256> lut;
			
			for (int i = 0; i < 256; i++)
			{
				const float v = i / 255.0f;
				lut[i] = (v <= 0.04045f) ? v / 12.92f : powf((v + 0.055f) / 1.055f, 2.4f);
			}

			return lut;
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
		/// Ensure accuracy (round not truncate) when converting to an 8-bit Pixel value.
		/// truncation biases dark by ~0.5 LSB)
		/// </summary>
		template<typename T>
		static inline constexpr T Quantize(double value)
		{
			if constexpr (std::is_integral_v<T>)
			{
				return static_cast<T>(value + 0.5);
			}

			return static_cast<T>(value);
		}

		/// <summary>
		/// The formula used by the Qt framework which is used by our default.
		/// Note: There are serious unanswered questions around this formula.
		/// Deliberately truncates (integer math) to stay bit-exact with Qt's qGray.
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
			return Quantize<T>((r + g + b) / 3.0);
		}

		/// <summary>
		/// BT601 calculates the Luma when RGB are Gamma Corrected. The Y' from Y'UV & Y'IQ.
		/// When Linear, can generate the luminance Y from the CIE 1931 XYZ color space.
		/// Aka: NTSC RGB formula, with a White Point of "C".
		/// </summary>
		template<typename T>
		static inline constexpr T BT601(T r, T g, T b)
		{
			return Quantize<T>(0.299 * r + 0.587 * g + 0.114 * b);
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
			return Quantize<T>(0.2126 * r + 0.7152 * g + 0.0722 * b);
		}

		/// <summary>
		/// BT2100 calculates the Luma when RGB are Gamma Corrected. The Y' from Y'UV & Y'IQ.
		/// When Linear, can generate the luminance Y from the CIE 1931 XYZ color space.
		/// Has a White Point of "D65".
		/// </summary>
		template<typename T>
		static inline constexpr T BT2100(T r, T g, T b)
		{
			return Quantize<T>(0.2627 * r + 0.6780 * g + 0.0593 * b);
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
			return Quantize<T>((std::max({ r, g, b }) + std::min({ r, g, b })) / 2.0);
		}

		/// <summary>
		/// The purpose of MinAvg is to produce a grayscale image whose values are less sensitive to multi color text.
		/// It was introduced for the first AdOtsu algorithm.
		/// </summary>
		/// <remarks>"A multi-scale framework for adaptive binarization of degraded document images", 2010</remarks>
		template<typename T>
		static inline constexpr T MinAvg(T r, T g, T b)
		{
			return Quantize<T>((Mean(r, g, b) + std::min({ r, g, b })) / 2.0);
		}

		/// <summary>
		/// CIELAB & CIELUV L Value.  Calculates Lightness when RGB are Linear.
		/// Notice that this has built in gamma correction.
		/// Note: BT709 has a White Point of D65.  The ICC calls for D50.
		/// This is also known as a chromatic adaptation transformation (CAT).
		/// See:  https://drafts.csswg.org/css-color/#rgb-to-lab
		/// </summary>
		static inline constexpr float Lightness(float r, float g, float b)
		{
			const auto addGamma = [&](double y)
			{
				return y > 0.00885 ? Gamma(y, 3) : 7.78703 * y + 0.13793;
			};

			return 116 * addGamma(BT709(r, g, b)) - 16;
		}

		/// <summary>
		/// Linear sRGB to XYZ color space with a D65 white point
		/// </summary>
		static constexpr inline XYZ RGBToXYZ(float r, float g, float b)
		{
			return {
				0.4124564f * r + 0.3575761f * g + 0.1804375f * b,
				0.2126729f * r + 0.7151522f * g + 0.0721750f * b,
				0.0193339f * r + 0.1191920f * g + 0.9503041f * b
			};
		}

		/// <summary>
		/// XYZ to L* a* b* color space with D65 whitepoint tristimulus values
		/// </summary>
		static inline Lab XYZToLab(float X, float Y, float Z)
		{
			const auto f = [](float t) {
				return (t > 0.008856f) ? cbrtf(t) : (7.787037f * t + 0.137931f);
			};

			// D65 Tristimulus Values - D50: [0.96422, 1, 0.82521]
			const auto fx = f(X / 0.95047f);
			const auto fy = f(Y / 1.0f);
			const auto fz = f(Z / 1.08883f);

			return {
				116.0f * fy - 16.0f,
				500.0f * (fx - fy),
				200.0f * (fy - fz)
			};
		}	

		/// <summary>
		/// L* a* b* Euclidean Distance
		/// Takes into account chromatic spearation, not just Lightness.
		/// All input parameters are linear and must be uncompressed.
		/// Source: Used by Phansalkar
		/// </summary>
		static inline float LABDist(float red, float green, float blue)
		{
			const auto [X, Y, Z] = RGBToXYZ(red, green, blue);
			const auto [L, a, b] = XYZToLab(X, Y, Z);

			return sqrtf(L * L + a * a + b * b);
		}

		/// <summary>
		/// Convert an RGB/RGBA buffer to 8-bit grayscale.
		/// </summary>
		static void ToGrayscale(
			Pixel8* output,
			const uint8_t* input,
			int width, int height, int channels,
			GrayscaleAlgorithms algorithm = GrayscaleAlgorithms::MEAN)
		{
			const int size = width * height;

			switch (algorithm)
			{
				case GrayscaleAlgorithms::QT:
					GrayscaleConverter<Qt<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::BT601:
					GrayscaleConverter<BT601<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::BT709:
					GrayscaleConverter<BT709<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::BT2100:
					GrayscaleConverter<BT2100<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::VALUE:
					GrayscaleConverter<Value<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::LUSTER:
					GrayscaleConverter<Luster<Pixel8>>(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::MINAVG:
					GrayscaleConverter<MinAvg<Pixel8>>(output, input, size, channels);
					break;

				// Linear Algorithms - Assumes we are working in a compressed sRGB colorspace
				case GrayscaleAlgorithms::LIGHTNESS:
					GrayscaleConverterLightness(output, input, size, channels);
					break;
				case GrayscaleAlgorithms::LABDIST:
					GrayscaleConverterLABDist(output, input, size, channels);
					break;

				// Default - The Mean algorithm is safe, efficient, and effective
				default:
					GrayscaleConverter<Mean<Pixel8>>(output, input, size, channels);
					break;
			}
		}

	private:

		static inline std::optional<std::array<float, 256>> m_lut;

		/// <summary>
		/// An optimized grayscale conversion loop where all algs are inlined
		/// </summary>
		template<auto Algorithm>
		static void GrayscaleConverter(
			Pixel8* output,
			const uint8_t* input,
			int size,
			int channels)
		{
			for (int i = 0, offset = 0; i < size; ++i, offset += channels)
			{
				output[i] = Algorithm(input[offset], input[offset + 1], input[offset + 2]);
			}
		}

		/// <summary>
		/// Lightness has a known range of 0-100, allowing a single-pass conversion.
		/// </summary>
		static void GrayscaleConverterLightness(
			Pixel8* output,
			const uint8_t* input,
			int size,
			int channels)
		{
			if (!m_lut) m_lut = LinearLUT();
			const float scale = 255.0f / 100.0f;

			for (int i = 0, offset = 0; i < size; ++i, offset += channels)
			{
				output[i] = Quantize<Pixel8>(
					Lightness((*m_lut)[input[offset]], (*m_lut)[input[offset + 1]], (*m_lut)[input[offset + 2]]) * scale);
			}
		}

		/// <summary>
		/// LABDist has an unknown range requiring two passes: compute values, then normalize.
		/// </summary>
		static void GrayscaleConverterLABDist(
			Pixel8* output,
			const uint8_t* input,
			int size,
			int channels)
		{
			if (!m_lut) m_lut = LinearLUT();

			std::vector<float> values(size);

			for (int i = 0, offset = 0; i < size; ++i, offset += channels)
			{
				values[i] = LABDist((*m_lut)[input[offset]], (*m_lut)[input[offset + 1]], (*m_lut)[input[offset + 2]]);
			}

			auto [mn, mx] = std::minmax_element(values.data(), values.data() + size);
			const float min = *mn;
			const float scale = 255.0f / std::max(*mx - *mn, 1.0f);

			for (int i = 0; i < size; ++i)
			{
				output[i] = Quantize<Pixel8>((values[i] - min) * scale);
			}
		}
	};
}


#endif // GRAYSCALE_HPP
