#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"

namespace py = pybind11;
using namespace Doxa;


// Pybind helper for converting from an array to a Doxa Image.  This will reference the array, not create a copy.
Image ArrayToImage(const py::array_t<Doxa::Pixel8>& imageArray)
{
	return Image::Reference(imageArray.shape(1), imageArray.shape(0), reinterpret_cast<Pixel8*>(imageArray.request().ptr));
}

py::dict CalculatePerformance(
	const py::array_t<Pixel8>& groundTruthImageArray, 
	const py::array_t<Pixel8>& binaryImageArray)
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = py::dict();

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

py::dict CalculatePerformanceEx(
	const py::array_t<Pixel8>& groundTruthImageArray, 
	const py::array_t<Pixel8>& binaryImageArray,
	bool accuracy = false,
	bool fm = false,
	bool mcc = false,
	bool psnr = false,
	bool nrm = false,
	bool drdm = false)
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = py::dict();

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

	void Initialize(const py::array_t<Pixel8>& grayScaleImageArray)
	{
		Image image = ArrayToImage(grayScaleImageArray);
		algorithmPtr->Initialize(image);
	}

	void ToBinary(const py::array_t<Pixel8>& binaryImageArray, const ParameterMap& parameters={})
	{
		Image image = ArrayToImage(binaryImageArray);
		algorithmPtr->ToBinary(image, parameters);
	}

	static void UpdateToBinary(const Algorithms algorithm, const py::array_t<Pixel8>& imageArray, const ParameterMap& parameters={})
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
PYBIND11_MODULE(doxapy, m) {
	m.doc() = "DoxaPy: Python bindings for the Doxa image binarization framework";

	m.def("calculate_performance", &CalculatePerformance, 
		"Obtain binarization performance information based on a Ground Truth.");
	
	m.def("calculate_performance_ex", &CalculatePerformanceEx, 
		py::arg("groundTruthImageArray"), 
		py::arg("binaryImageArray"),
		py::kw_only(),
		py::arg("accuracy") = false,
		py::arg("fm") = false,
		py::arg("mcc") = false,
		py::arg("psnr") = false,
		py::arg("nrm") = false,
		py::arg("drdm") = false,
		"Obtain specific binarization performance information based on a Ground Truth.");

	py::class_<Binarization> binarization(m, "Binarization");

	binarization.def(py::init<const Algorithms>())
		.def("initialize", &Binarization::Initialize)
		.def("to_binary", &Binarization::ToBinary, 
			py::arg("binaryImageArray"), 
			py::arg("parameters") = ParameterMap())
		.def("algorithm", &Binarization::CurrentAlgorithm)
		.def_static("update_to_binary", &Binarization::UpdateToBinary, 
			py::arg("algorithm"), 
			py::arg("imageArray"), 
			py::arg("parameters") = ParameterMap());

	py::enum_<Algorithms>(binarization, "Algorithms")
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
		.export_values();
}