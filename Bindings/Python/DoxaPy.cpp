#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/variant.h>

#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"

namespace nb = nanobind;
using namespace Doxa;

// Nanobind helper for converting from an array to a Doxa Image. This will reference the array, not create a copy.
Image ArrayToImage(const nb::ndarray<Pixel8, nb::ndim<2>>& imageArray)
{
	return Image::Reference(imageArray.shape(1), imageArray.shape(0), reinterpret_cast<Pixel8*>(imageArray.data()));
}

nb::dict CalculatePerformance(
	const nb::ndarray<Pixel8, nb::ndim<2>>& groundTruthImageArray, 
	const nb::ndarray<Pixel8, nb::ndim<2>>& binaryImageArray)
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = nb::dict();

	ClassifiedPerformance::Classifications classifications;
	ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
	// TODO: If this fails, we may want to 0 out the return values

	dict["accuracy"] = ClassifiedPerformance::CalculateAccuracy(classifications);
	dict["fm"] = ClassifiedPerformance::CalculateFMeasure(classifications);
	dict["mcc"] = ClassifiedPerformance::CalculateMCC(classifications);
	dict["psnr"] = ClassifiedPerformance::CalculatePSNR(classifications);
	dict["nrm"] = ClassifiedPerformance::CalculateNRM(classifications);

	dict["drdm"] = DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	return dict;
}

nb::dict CalculatePerformanceEx(
	const nb::ndarray<Pixel8, nb::ndim<2>>& groundTruthImageArray, 
	const nb::ndarray<Pixel8, nb::ndim<2>>& binaryImageArray,
	bool accuracy = false,
	bool fm = false,
	bool mcc = false,
	bool psnr = false,
	bool nrm = false,
	bool drdm = false)
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = nb::dict();

	if (accuracy || fm || mcc || psnr || nrm) 
	{
		ClassifiedPerformance::Classifications classifications;
		ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
		// TODO: If this fails, we may want to 0 out the return values

		if (accuracy)
			dict["accuracy"] = ClassifiedPerformance::CalculateAccuracy(classifications);

		if (fm)
			dict["fm"] = ClassifiedPerformance::CalculateFMeasure(classifications);

		if (mcc)
			dict["mcc"] = ClassifiedPerformance::CalculateMCC(classifications);

		if (psnr)
			dict["psnr"] = ClassifiedPerformance::CalculatePSNR(classifications);

		if (nrm)
			dict["nrm"] = ClassifiedPerformance::CalculateNRM(classifications);
	}

	if (drdm)
	{
		dict["drdm"] = DRDM::CalculateDRDM(groundTruthImage, binaryImage);
	}

	return dict;
}

/// <summary>
/// Binarization is a helper class to help interface the C++ Doxa framework with Python.
/// It exposes through enumeration all of the algorithms supported by the library.
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

	void Initialize(const nb::ndarray<Pixel8, nb::ndim<2>>& grayScaleImageArray)
	{
		Image image = ArrayToImage(grayScaleImageArray);
		algorithmPtr->Initialize(image);
	}

	void ToBinary(const nb::ndarray<Pixel8, nb::ndim<2>>& binaryImageArray, const ParameterMap& parameters={})
	{
		Image image = ArrayToImage(binaryImageArray);
		algorithmPtr->ToBinary(image, parameters);
	}

	static void UpdateToBinary(const Algorithms algorithm, const nb::ndarray<Pixel8, nb::ndim<2>>& imageArray, const ParameterMap& parameters={})
	{
		Binarization binAlg(algorithm);
		binAlg.Initialize(imageArray);
		binAlg.ToBinary(imageArray, parameters);
	}

	Algorithms CurrentAlgorithm() { return algorithm; }

protected:
	const Algorithms algorithm;
	IAlgorithm* algorithmPtr = nullptr;
}; // Class: Binarization

// Expose routines using the PEP8 style guide
NB_MODULE(doxapy, m) {
	m.doc() = "DoxaPy: Python bindings for the Doxa image binarization framework";

	m.def("calculate_performance", &CalculatePerformance, 
		"Obtain binarization performance information based on a Ground Truth.");
	
	m.def("calculate_performance_ex", &CalculatePerformanceEx, 
		nb::arg("groundTruthImageArray"), 
		nb::arg("binaryImageArray"),
		nb::arg("accuracy") = false,
		nb::arg("fm") = false,
		nb::arg("mcc") = false,
		nb::arg("psnr") = false,
		nb::arg("nrm") = false,
		nb::arg("drdm") = false,
		"Obtain specific binarization performance information based on a Ground Truth.");

	nb::class_<Binarization> binarization(m, "Binarization");

	binarization.def(nb::init<const Algorithms>())
		.def("initialize", &Binarization::Initialize)
		.def("to_binary", &Binarization::ToBinary, 
			nb::arg("binaryImageArray"), 
			nb::arg("parameters") = ParameterMap())
		.def("algorithm", &Binarization::CurrentAlgorithm)
		.def_static("update_to_binary", &Binarization::UpdateToBinary, 
			nb::arg("algorithm"), 
			nb::arg("imageArray"), 
			nb::arg("parameters") = ParameterMap());

	nb::enum_<Algorithms>(binarization, "Algorithms")
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
		.value("GATOS", Algorithms::GATOS)
		.value("ADOTSU", Algorithms::ADOTSU)
		.export_values();
}