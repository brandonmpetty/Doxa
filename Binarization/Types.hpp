// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

namespace Binarization
{
	// Forward Declarations
	struct Image;
	struct Region;

	// Type Definitions
	typedef uint32_t Pixel32;
	typedef uint8_t  Pixel8;

	namespace TupleTypes
	{
		static const std::string RGBA = "RGB_ALPHA";
	}
}

#endif // TYPES_HPP
