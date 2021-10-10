#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
//#include <iostream>

#include "../../Doxa/BinarizationFactory.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"

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
	double MCC;
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
	// TODO: If this fails, we may want to 0 out the return values

	Performance perf;
	perf.Accuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
	perf.FM = ClassifiedPerformance::CalculateFMeasure(classifications);
	perf.MCC = ClassifiedPerformance::CalculateMCC(classifications);
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
	
	Binarization(const Algorithms algorithm)
	: algorithm(algorithm)
	{
		algorithmPtr = BinarizationFactory::Algorithm(algorithm);
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
		algorithmPtr->ToBinary(image, Parameters::FromJson(params));
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



EMSCRIPTEN_BINDINGS(doxa_wasm) {
	class_<Binarization>("Binarization")
		.constructor<Algorithms>()
		.function("initialize", &Binarization::Initialize, allow_raw_pointers())
		.function("toBinary", &Binarization::ToBinary, allow_raw_pointers())
		.function("currentAlgorithm", &Binarization::CurrentAlgorithm);
	enum_<Algorithms>("Binarization.Algorithms")
		.value("OTSU", Algorithms::OTSU)
		.value("BERNSEN", Algorithms::BERNSEN)
		.value("NIBLACK", Algorithms::NIBLACK)
		.value("SAUVOLA", Algorithms::SAUVOLA)
		.value("WOLF", Algorithms::WOLF)
		.value("NICK", Algorithms::NICK)
		.value("SU", Algorithms::SU)
		.value("TRSINGH", Algorithms::TRSINGH)
		.value("BATAINEH", Algorithms::BATAINEH)
		.value("ISAUVOLA", Algorithms::ISAUVOLA)
		.value("WAN", Algorithms::WAN)
		.value("GATOS", Algorithms::GATOS);
    EM_ASM(
        Module['Binarization']['Algorithms'] = Module['Binarization.Algorithms'];
        delete Module['Binarization.Algorithms'];
    );

	value_object<Performance>("Performance")
		.field("accuracy", &Performance::Accuracy)
		.field("fm", &Performance::FM)
		.field("mcc", &Performance::MCC)
		.field("psnr", &Performance::PSNR)
		.field("nrm", &Performance::NRM)
		.field("drdm", &Performance::DRDM);
	function("calculatePerformance", &CalculatePerformance, allow_raw_pointers());
};