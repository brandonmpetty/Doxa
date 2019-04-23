#include <emscripten/emscripten.h>
#include "../Doxa/Types.hpp"
#include "../Doxa/Palette.hpp"
#include "../Doxa/Image.hpp"
#include "../Doxa/Otsu.hpp"
#include "../Doxa/Niblack.hpp"
#include "../Doxa/Sauvola.hpp"
#include "../Doxa/ISauvola.hpp"
#include "../Doxa/Nick.hpp"
#include "../Doxa/TRSingh.hpp"
#include "../Doxa/Wan.hpp"
#include "../Doxa/Wolf.hpp"
#include "../Doxa/Su.hpp"

using namespace Doxa;


/// <summary>
/// DoxaWasm is a helper class to help interface the C++ Doxa framework with WebAssembly.
/// It exposes through enumeration all of the algorithms supported by the library.
/// The Doxa.js code wraps the exported symbols to make it easier to use in JavaScript.
/// </summary>
class DoxaWasm
{
public:
	enum Binarization
	{
		OTSU = 0,
		NIBLACK = 1,
		SAUVOLA = 2,
		WOLF = 3,
		NICK = 4,
		SU = 5,
		TRSINGH = 6,
		ISAUVOLA = 7,
		WAN = 8
	};
	
	void Initialize(const DoxaWasm::Binarization algorithm, Pixel8* data, const int width, const int height)
	{
		if (algorithmPtr != nullptr) delete algorithmPtr;
		
		switch (algorithm)
		{
			case OTSU:
				algorithmPtr = new Otsu();
				break;
			case NIBLACK:
				algorithmPtr = new Niblack();
				break;
			case SAUVOLA:
				algorithmPtr = new Sauvola();
				break;
			case NICK:
				algorithmPtr = new Nick();
				break;
			case WOLF:
				algorithmPtr = new Wolf();
				break;
			case SU:
				algorithmPtr = new Su();
				break;
			case TRSINGH:
				algorithmPtr = new TRSingh();
				break;
			case ISAUVOLA:
				algorithmPtr = new ISauvola();
				break;
			case WAN:
				algorithmPtr = new Wan();
				break;
		}
		
		// Set width and height
		this->width = width;
		this->height = height;
		
		Image image = Image::Reference(width, height, data);
		algorithmPtr->Initialize(image);
	} // Method: Initialize
	
	void ToBinary(Pixel8* data, const int windowSize = 0, const double kValue = 0.00)
	{
		if (algorithmPtr == nullptr) return;
		
		// Setup optional parameters
		Parameters params;
		if (windowSize > 0) params.Set("window", windowSize);
		if (kValue != 0.00) params.Set("k", kValue);
		
		Image image = Image::Reference(this->width, this->height, data);
		algorithmPtr->ToBinary(image, params);
	}
	
	static DoxaWasm& Instance()
	{
        static DoxaWasm singleton;
        return singleton;
	}
	
	/* Useful for debugging small test images
	void Debug(Pixel8* data, const int width, const int height)
	{
		std::cout << "Debug - start" << std::endl;
		const size_t size = width * height;

		for (size_t idx = 0; idx < size; ++idx)
		{
			const Pixel8 pixel = data[idx];
			
			std::cout 
				<< "Index: " << idx 
				<< " RGB: ("
				<< Palette::Red(pixel) << ","
				<< Palette::Green(pixel) << ","
				<< Palette::Blue(pixel) << ","
				<< Palette::Alpha(pixel)  << ")"
				<< std::endl;
		}
		
		data[0] = 42; // Verify the ability to set
		std::cout << "Debug - stop" << std::endl;
	}
	 */
protected:
	IAlgorithm* algorithmPtr = nullptr;
	int width = 0;
	int height = 0;
	
	// Ensure we only access this through our singleton instance
	DoxaWasm() {}
    DoxaWasm(const DoxaWasm&) = delete;
    DoxaWasm(DoxaWasm&&) = delete;
    DoxaWasm& operator=(const DoxaWasm&) = delete;
    DoxaWasm& operator=(DoxaWasm&&) = delete;
}; // Class: DoxaWasm


extern "C"
{
	/// <summary>
	/// Initializes the algorithm, typically building out integral images, etc.
	/// </summary>
	/// <param name="algorithm">Enum value representing the algorithm to use.</param>
	/// <param name="data">An 8b grayscale image.</param>
	/// <param name="width">The Width of the image.</param>
	/// <param name="height">The Height of the image.</param>
	void EMSCRIPTEN_KEEPALIVE Initialize(DoxaWasm::Binarization algorithm, Pixel8* data, const int width, const int height)
	{		
		DoxaWasm::Instance().Initialize(algorithm, data, width, height);
	}
	
	/// <summary>
	/// Converts an 8bit grayscale image into an 8bit binary image.
	/// Once initialized, this can be called over an over, typically without the initialization overhead.
	/// This allows one to provide different window-size and k-value parameters efficiently.
	/// </summary>
	/// <param name="data">Image storgage for binary output.</param>
	/// <param name="windowSize">The Width of the image.</param>
	/// <param name="kValue">The Height of the image.</param>
	void EMSCRIPTEN_KEEPALIVE ToBinary(Pixel8* data, const int windowSize, const double kValue)
	{		
		DoxaWasm::Instance().ToBinary(data, windowSize, kValue);
	}

} // Extern C
