#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
//#include <iostream>

#include "../Doxa/Types.hpp"
#include "../Doxa/Palette.hpp"
#include "../Doxa/Image.hpp"

#include "../Doxa/Otsu.hpp"
#include "../Doxa/Bernsen.hpp"
#include "../Doxa/Niblack.hpp"
#include "../Doxa/Sauvola.hpp"
#include "../Doxa/ISauvola.hpp"
#include "../Doxa/Nick.hpp"
#include "../Doxa/TRSingh.hpp"
#include "../Doxa/Wan.hpp"
#include "../Doxa/Wolf.hpp"
#include "../Doxa/Su.hpp"

#include "../Doxa/ClassifiedPerformance.hpp"
#include "../Doxa/DRDM.hpp"

//#include "../Doxa/PNM.hpp"
using namespace Doxa;
using namespace emscripten;

/// <summary>
/// Structure for measuring performance characteristics of the different algorithms
/// </summary>
struct Performance
{
	double Accuracy;
	double FM;
	double PSNR;
	double NRM;
	double DRDM;
};

Performance CalculatePerformance(intptr_t groundTruthData, intptr_t binaryData, const int width, const int height)
{
	Image groundTruthImage = Image::Reference(width, height, reinterpret_cast<Pixel8*>(groundTruthData));
	Image binaryImage = Image::Reference(width, height, reinterpret_cast<Pixel8*>(binaryData));
	
	ClassifiedPerformance::Classifications classifications;
	ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
	// TODO: Right now this should never fail, aka: return false.

	Performance perf;
	perf.Accuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
	perf.FM = ClassifiedPerformance::CalculateFMeasure(classifications);
	perf.PSNR = ClassifiedPerformance::CalculatePSNR(classifications);
	perf.NRM = ClassifiedPerformance::CalculateNRM(classifications);
	perf.DRDM = DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	return perf;
}


/// <summary>
/// Binarization is a helper class to help interface the C++ Doxa framework with WebAssembly.
/// It exposes through enumeration all of the algorithms supported by the library.
/// The Doxa.js code wraps the exported symbols to make it easier to use in JavaScript.
/// </summary>
class Binarization
{
public:
	enum Algorithms
	{
		OTSU = 0,
		BERNSEN = 1,
		NIBLACK = 2,
		SAUVOLA = 3,
		WOLF = 4,
		NICK = 5,
		SU = 6,
		TRSINGH = 7,
		ISAUVOLA = 8,
		WAN = 9
	};
	
	Binarization(const Algorithms algorithm)
	: algorithm(algorithm)
	{
		switch (algorithm)
		{
			case OTSU:
				algorithmPtr = new Otsu();
				break;
			case BERNSEN:
				algorithmPtr = new Bernsen();
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
	}
	
	~Binarization()
	{
		delete algorithmPtr;
	}
	
	void Initialize(intptr_t data, const int width, const int height)
	{		
		// Set width and height
		this->width = width;
		this->height = height;
		
		Image image = Image::Reference(width, height, reinterpret_cast<Pixel8*>(data));
		algorithmPtr->Initialize(image);
	}
	
	void ToBinary(intptr_t data, const std::string& params)
	{
		Image image = Image::Reference(this->width, this->height, reinterpret_cast<Pixel8*>(data));
		algorithmPtr->ToBinary(image, params);
	}
	
	Algorithms CurrentAlgorithm() { return algorithm; }

/*
	static void Debug(Pixel8* data, const int width, const int height)
	{
		std::cout << "Debug - start (" << width << "x" << height << ")" << std::endl;
		const size_t size = width * height;

		for (size_t idx = 0; idx < size; ++idx)
		{
			const Pixel8 pixel = data[idx];
			
			std::cout 
				<< "Index: " << idx << " Value: " << std::to_string(pixel) << std::endl;
		}
		
		data[0] = 42; // Verify the ability to set
		std::cout << "Debug - stop" << std::endl;
	}
*/
protected:
	const Algorithms algorithm;
	IAlgorithm* algorithmPtr = nullptr;
	int width = 0;
	int height = 0;
}; // Class: Binarization


/*	Uncomment for FileSystem Access.  Note: this will more than double the output size.
extern "C"
{
	/// <summary>
	/// Reads a native PNM file inside the WASM virtual filesystem.
	/// </summary>
	/// <param name="width">A ptr that will return back the image width</param>
	/// <param name="height">A ptr that will return back the image height</param>
	/// <param name="height">A c-string representing the file location to open</param>
	Pixel8* EMSCRIPTEN_KEEPALIVE ReadPNM(int* width, int* height, const char* location)
	{
		// Read in any supported PNM format and return an 8bit linear RGB grayscale representation
		Image image = PNM::Read(location);
		
		// Our calling code will be responsible for freeing this memory
		image.managedExternally = true;
		
		*width = image.width;
		*height = image.height;

		return image.data;
	}
} // Extern C
*/


EMSCRIPTEN_BINDINGS(doxa_wasm) {
	class_<Binarization>("Binarization")
		.constructor<Binarization::Algorithms>()
		.function("initialize", &Binarization::Initialize, allow_raw_pointers())
		.function("toBinary", &Binarization::ToBinary, allow_raw_pointers())
		.function("currentAlgorithm", &Binarization::CurrentAlgorithm);
	enum_<Binarization::Algorithms>("Binarization.Algorithms")
		.value("OTSU", Binarization::Algorithms::OTSU)
		.value("BERNSEN", Binarization::Algorithms::BERNSEN)
		.value("NIBLACK", Binarization::Algorithms::NIBLACK)
		.value("SAUVOLA", Binarization::Algorithms::SAUVOLA)
		.value("WOLF", Binarization::Algorithms::WOLF)
		.value("NICK", Binarization::Algorithms::NICK)
		.value("SU", Binarization::Algorithms::SU)
		.value("TRSINGH", Binarization::Algorithms::TRSINGH)
		.value("ISAUVOLA", Binarization::Algorithms::ISAUVOLA)
		.value("WAN", Binarization::Algorithms::WAN)
	;
    EM_ASM(
        Module['Binarization']['Algorithms'] = Module['Binarization.Algorithms'];
        delete Module['Binarization.Algorithms'];
    );

	value_object<Performance>("Performance")
		.field("accuracy", &Performance::Accuracy)
		.field("fm", &Performance::FM)
		.field("psnr", &Performance::PSNR)
		.field("nrm", &Performance::NRM)
		.field("drdm", &Performance::DRDM);
	function("calculatePerformance", &CalculatePerformance, allow_raw_pointers());
	;
};