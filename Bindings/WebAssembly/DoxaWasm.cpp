#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
//#include <iostream>

#include "../../Doxa/BinarizationFactory.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"
#include "../../Doxa/Grayscale.hpp"
#include "../../Doxa/PseudoWeights.hpp"

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
	double Recall;
	double Precision;
	double MCC;
	double PSNR;
	double NRM;
	double DRDM;
};

/// <summary>
/// Structure for measuring pseudo performance characteristics, including standard and pseudo metrics
/// </summary>
struct PseudoPerformance
{
	double Accuracy;
	double FM;
	double Recall;
	double Precision;
	double MCC;
	double PSNR;
	double NRM;
	double DRDM;
	double PseudoFM;
	double PseudoPrecision;
	double PseudoRecall;
};

/// <summary>
/// Copy a weight map into a newly allocated, JS-owned Float64Array.
/// typed_memory_view is a transient view over the vector; Float64Array.set copies
/// the bytes out before the vector is destroyed, so the returned array owns its data.
/// </summary>
val ToFloat64Array(const std::vector<double>& weights)
{
	val array = val::global("Float64Array").new_(weights.size());
	array.call<void>("set", val(typed_memory_view(weights.size(), weights.data())));
	return array;
}

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
	perf.Recall = ClassifiedPerformance::CalculateRecall(classifications);
	perf.Precision = ClassifiedPerformance::CalculatePrecision(classifications);
	perf.MCC = ClassifiedPerformance::CalculateMCC(classifications);
	perf.PSNR = ClassifiedPerformance::CalculatePSNR(classifications);
	perf.NRM = ClassifiedPerformance::CalculateNRM(classifications);
	perf.DRDM = DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	return perf;
}


PseudoPerformance CalculatePseudoPerformance(
	intptr_t groundTruthData, intptr_t binaryData,
	const int width, const int height,
	val precisionWeights,
	val recallWeights)
{
	Image groundTruthImage = Image::Reference(width, height, reinterpret_cast<Pixel8*>(groundTruthData));
	Image binaryImage = Image::Reference(width, height, reinterpret_cast<Pixel8*>(binaryData));

	// Weights are optional. When not supplied, generate them on the spot from the ground
	// truth so the image-sized maps never have to cross the JS boundary just to come back.
	std::vector<double> precision, recall;
	if (precisionWeights.isUndefined() || recallWeights.isUndefined())
	{
		PseudoWeights::Generate(recall, precision, groundTruthImage);
	}
	else
	{
		precision = convertJSArrayToNumberVector<double>(precisionWeights);
		recall = convertJSArrayToNumberVector<double>(recallWeights);
	}

	// Compute weighted classifications
	ClassifiedPerformance::Classifications classifications;
	ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage, precision, recall);

	PseudoPerformance perf;
	perf.Accuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
	perf.FM = ClassifiedPerformance::CalculateFMeasure(classifications);
	perf.Recall = ClassifiedPerformance::CalculateRecall(classifications);
	perf.Precision = ClassifiedPerformance::CalculatePrecision(classifications);
	perf.MCC = ClassifiedPerformance::CalculateMCC(classifications);
	perf.PSNR = ClassifiedPerformance::CalculatePSNR(classifications);
	perf.NRM = ClassifiedPerformance::CalculateNRM(classifications);
	perf.DRDM = DRDM::CalculateDRDM(groundTruthImage, binaryImage);
	perf.PseudoFM = ClassifiedPerformance::CalculatePseudoFMeasure(classifications);
	perf.PseudoPrecision = ClassifiedPerformance::CalculatePseudoPrecision(classifications);
	perf.PseudoRecall = ClassifiedPerformance::CalculatePseudoRecall(classifications);

	return perf;
}


/// <summary>
/// Generate the pseudo precision and recall weight maps from a Ground Truth image,
/// returned as a { precision, recall } pair of Float64Arrays. Pass the object straight
/// to calculatePseudoPerformance to reuse one ground truth's maps across many images.
/// </summary>
val GeneratePseudoWeights(intptr_t groundTruthData, const int width, const int height)
{
	Image groundTruthImage = Image::Reference(width, height, reinterpret_cast<Pixel8*>(groundTruthData));

	std::vector<double> gw, pw;
	PseudoWeights::Generate(gw, pw, groundTruthImage);

	val weights = val::object();
	weights.set("precision", ToFloat64Array(pw));
	weights.set("recall", ToFloat64Array(gw));
	return weights;
}


void ToGrayscale(intptr_t outputData, intptr_t inputData,
	int width, int height, int channels, GrayscaleAlgorithms algorithm)
{
	Grayscale::ToGrayscale(
		reinterpret_cast<Pixel8*>(outputData),
		reinterpret_cast<const Pixel8*>(inputData),
		width, height, channels, algorithm);
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
		.value("ADOTSU", Algorithms::ADOTSU)
		.value("SU", Algorithms::SU)
		.value("TRSINGH", Algorithms::TRSINGH)
		.value("BATAINEH", Algorithms::BATAINEH)
		.value("ISAUVOLA", Algorithms::ISAUVOLA)
		.value("WAN", Algorithms::WAN)
		.value("GATOS", Algorithms::GATOS)
		.value("PHANSALKAR", Algorithms::PHANSALKAR)
		.value("WELLNER", Algorithms::WELLNER)
		.value("BRADLEY", Algorithms::BRADLEY)
		.value("FENG", Algorithms::FENG)
		.value("XDOG", Algorithms::XDOG);
    EM_ASM(
        Module['Binarization']['Algorithms'] = Module['Binarization.Algorithms'];
        delete Module['Binarization.Algorithms'];
    );

	value_object<Performance>("Performance")
		.field("accuracy", &Performance::Accuracy)
		.field("fm", &Performance::FM)
		.field("recall", &Performance::Recall)
		.field("precision", &Performance::Precision)
		.field("mcc", &Performance::MCC)
		.field("psnr", &Performance::PSNR)
		.field("nrm", &Performance::NRM)
		.field("drdm", &Performance::DRDM);
	function("calculatePerformance", &CalculatePerformance, allow_raw_pointers());

	value_object<PseudoPerformance>("PseudoPerformance")
		.field("accuracy", &PseudoPerformance::Accuracy)
		.field("fm", &PseudoPerformance::FM)
		.field("recall", &PseudoPerformance::Recall)
		.field("precision", &PseudoPerformance::Precision)
		.field("mcc", &PseudoPerformance::MCC)
		.field("psnr", &PseudoPerformance::PSNR)
		.field("nrm", &PseudoPerformance::NRM)
		.field("drdm", &PseudoPerformance::DRDM)
		.field("pseudoFM", &PseudoPerformance::PseudoFM)
		.field("pseudoPrecision", &PseudoPerformance::PseudoPrecision)
		.field("pseudoRecall", &PseudoPerformance::PseudoRecall);
	function("calculatePseudoPerformance", &CalculatePseudoPerformance, allow_raw_pointers());

	function("generatePseudoWeights", &GeneratePseudoWeights, allow_raw_pointers());

	enum_<GrayscaleAlgorithms>("Grayscale.Algorithms")
		.value("MEAN", GrayscaleAlgorithms::MEAN)
		.value("QT", GrayscaleAlgorithms::QT)
		.value("BT601", GrayscaleAlgorithms::BT601)
		.value("BT709", GrayscaleAlgorithms::BT709)
		.value("BT2100", GrayscaleAlgorithms::BT2100)
		.value("VALUE", GrayscaleAlgorithms::VALUE)
		.value("LUSTER", GrayscaleAlgorithms::LUSTER)
		.value("LIGHTNESS", GrayscaleAlgorithms::LIGHTNESS)
		.value("MINAVG", GrayscaleAlgorithms::MINAVG)
		.value("LABDIST", GrayscaleAlgorithms::LABDIST);
	EM_ASM(
		Module['Grayscale'] = { 'Algorithms': Module['Grayscale.Algorithms'] };
		delete Module['Grayscale.Algorithms'];
	);
	function("toGrayscale", &ToGrayscale, allow_raw_pointers());
};