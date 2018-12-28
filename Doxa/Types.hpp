// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

namespace Doxa
{
	// Forward Declarations
	struct Image;
	struct Region;

	// Type Definitions
	typedef uint32_t Pixel32;
	typedef uint8_t  Pixel8;

	namespace TupleTypes
	{
		static const std::string BLACK_WHITE = "BLACKANDWHITE";
		static const std::string GRAYSCALE = "GRAYSCALE";
		static const std::string RGB = "RGB";
		static const std::string RGBA = "RGB_ALPHA";
	}
}

#endif // TYPES_HPP
