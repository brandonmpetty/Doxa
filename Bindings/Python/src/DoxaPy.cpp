#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/variant.h>

#include "Doxa/BinarizationFactory.hpp"
#include "Doxa/ClassifiedPerformance.hpp"
#include "Doxa/DRDM.hpp"
#include "Doxa/DIBCOUtils.hpp"
#include "Doxa/Grayscale.hpp"

namespace nb = nanobind;
using namespace Doxa;

// Nanobind helper for converting from an array to a Doxa Image. This will reference the array, not create a copy.
Image ArrayToImage(const nb::ndarray<Pixel8, nb::ndim<2>>& imageArray)
{
	return Image::Reference(imageArray.shape(1), imageArray.shape(0), reinterpret_cast<Pixel8*>(imageArray.data()));
}

nb::dict CalculatePerformance(
	const nb::ndarray<Pixel8, nb::ndim<2>>& groundTruthImageArray,
	const nb::ndarray<Pixel8, nb::ndim<2>>& binaryImageArray,
	const std::vector<double>& precisionWeights = {},
	const std::vector<double>& recallWeights = {})
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = nb::dict();

	ClassifiedPerformance::Classifications classifications;

	if (!precisionWeights.empty() && !recallWeights.empty())
		ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage, precisionWeights, recallWeights);
	else
		ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);

	dict["accuracy"] = ClassifiedPerformance::CalculateAccuracy(classifications);
	dict["fm"] = ClassifiedPerformance::CalculateFMeasure(classifications);
	dict["recall"] = ClassifiedPerformance::CalculateRecall(classifications);
	dict["precision"] = ClassifiedPerformance::CalculatePrecision(classifications);
	dict["mcc"] = ClassifiedPerformance::CalculateMCC(classifications);
	dict["psnr"] = ClassifiedPerformance::CalculatePSNR(classifications);
	dict["nrm"] = ClassifiedPerformance::CalculateNRM(classifications);

	dict["drdm"] = DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	if (!precisionWeights.empty() && !recallWeights.empty())
	{
		dict["pseudo_fm"] = ClassifiedPerformance::CalculatePseudoFMeasure(classifications);
		dict["pseudo_precision"] = ClassifiedPerformance::CalculatePseudoPrecision(classifications);
		dict["pseudo_recall"] = ClassifiedPerformance::CalculatePseudoRecall(classifications);
	}

	return dict;
}

nb::dict CalculatePerformanceEx(
	const nb::ndarray<Pixel8, nb::ndim<2>>& groundTruthImageArray,
	const nb::ndarray<Pixel8, nb::ndim<2>>& binaryImageArray,
	bool accuracy = false,
	bool fm = false,
	bool recall = false,
	bool precision = false,
	bool mcc = false,
	bool psnr = false,
	bool nrm = false,
	bool drdm = false,
	bool pseudo_fm = false,
	bool pseudo_precision = false,
	bool pseudo_recall = false,
	const std::vector<double>& precisionWeights = {},
	const std::vector<double>& recallWeights = {})
{
	Image groundTruthImage = ArrayToImage(groundTruthImageArray);
	Image binaryImage = ArrayToImage(binaryImageArray);

	auto dict = nb::dict();

	const bool needsPseudo = (pseudo_fm || pseudo_precision || pseudo_recall)
		&& !precisionWeights.empty() && !recallWeights.empty();

	if (accuracy || fm || recall || precision || mcc || psnr || nrm || needsPseudo)
	{
		ClassifiedPerformance::Classifications classifications;

		if (needsPseudo)
			ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage, precisionWeights, recallWeights);
		else
			ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);

		if (accuracy)
			dict["accuracy"] = ClassifiedPerformance::CalculateAccuracy(classifications);

		if (fm)
			dict["fm"] = ClassifiedPerformance::CalculateFMeasure(classifications);

		if (recall)
			dict["recall"] = ClassifiedPerformance::CalculateRecall(classifications);

		if (precision)
			dict["precision"] = ClassifiedPerformance::CalculatePrecision(classifications);

		if (mcc)
			dict["mcc"] = ClassifiedPerformance::CalculateMCC(classifications);

		if (psnr)
			dict["psnr"] = ClassifiedPerformance::CalculatePSNR(classifications);

		if (nrm)
			dict["nrm"] = ClassifiedPerformance::CalculateNRM(classifications);

		if (needsPseudo)
		{
			if (pseudo_fm)
				dict["pseudo_fm"] = ClassifiedPerformance::CalculatePseudoFMeasure(classifications);

			if (pseudo_precision)
				dict["pseudo_precision"] = ClassifiedPerformance::CalculatePseudoPrecision(classifications);

			if (pseudo_recall)
				dict["pseudo_recall"] = ClassifiedPerformance::CalculatePseudoRecall(classifications);
		}
	}

	if (drdm)
	{
		dict["drdm"] = DRDM::CalculateDRDM(groundTruthImage, binaryImage);
	}

	return dict;
}

nb::ndarray<nb::numpy, Pixel8, nb::ndim<2>> ToGrayscale(
	GrayscaleAlgorithms algorithm,
	const nb::ndarray<Pixel8, nb::ndim<3>>& colorImageArray)
{
	const int height = colorImageArray.shape(0);
	const int width = colorImageArray.shape(1);
	const int channels = colorImageArray.shape(2);

	Pixel8* output = new Pixel8[width * height];

	Grayscale::ToGrayscale(
		output,
		reinterpret_cast<const Pixel8*>(colorImageArray.data()),
		width, height, channels, algorithm);

	// Return an ND Array that will correctly manage the allocated memory
	const size_t shape[2] = { (size_t)height, (size_t)width };
	nb::capsule owner(output, [](void* p) noexcept { delete[] static_cast<Pixel8*>(p); });
	return nb::ndarray<nb::numpy, Pixel8, nb::ndim<2>>(output, 2, shape, owner);
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

	Algorithms CurrentAlgorithm() { return algorithm; }

protected:
	const Algorithms algorithm;
	IAlgorithm* algorithmPtr = nullptr;
}; // Class: Binarization

nb::ndarray<nb::numpy, Pixel8, nb::ndim<2>> ToBinary(
	const Algorithms algorithm,
	const nb::ndarray<Pixel8, nb::ndim<2>>& grayImage,
	const ParameterMap& parameters = {})
{
	const int height = grayImage.shape(0);
	const int width = grayImage.shape(1);

	// Allocate new memory for the image data
	Pixel8* binaryImage = new Pixel8[width * height];

	// Apply the algorithm
	const Image grayImageRef = ArrayToImage(grayImage);
	Image binaryImageRef = Image::Reference(width, height, binaryImage);

	IAlgorithm* algorithmPtr = BinarizationFactory::Algorithm(algorithm);
	algorithmPtr->Initialize(grayImageRef);
	algorithmPtr->ToBinary(binaryImageRef, parameters);
	delete algorithmPtr;

	// Return an ND Array that will correctly manage the allocated memory
	const size_t shape[2] = { (size_t)height, (size_t)width };
	nb::capsule owner(binaryImage, [](void* p) noexcept { delete[] static_cast<Pixel8*>(p); });
	return nb::ndarray<nb::numpy, Pixel8, nb::ndim<2>>(binaryImage, 2, shape, owner);
}

void UpdateToBinary(
	const Algorithms algorithm,
	const nb::ndarray<Pixel8, nb::ndim<2>>& imageArray,
	const ParameterMap& parameters = {})
{
	Binarization binAlg(algorithm);
	binAlg.Initialize(imageArray);
	binAlg.ToBinary(imageArray, parameters);
}

// Expose routines using the PEP8 style guide
NB_MODULE(doxapy, m) {
	m.doc() = "DoxaPy: Python bindings for the Doxa image binarization framework";

	m.def("calculate_performance", &CalculatePerformance,
		nb::arg("groundTruthImageArray"),
		nb::arg("binaryImageArray"),
		nb::arg("precision_weights") = std::vector<double>{},
		nb::arg("recall_weights") = std::vector<double>{},
		"Obtain binarization performance information based on a Ground Truth. "
		"Optionally pass precision and recall weight arrays for pseudo-metrics.");

	m.def("calculate_performance_ex", &CalculatePerformanceEx,
		nb::arg("groundTruthImageArray"),
		nb::arg("binaryImageArray"),
		nb::arg("accuracy") = false,
		nb::arg("fm") = false,
		nb::arg("recall") = false,
		nb::arg("precision") = false,
		nb::arg("mcc") = false,
		nb::arg("psnr") = false,
		nb::arg("nrm") = false,
		nb::arg("drdm") = false,
		nb::arg("pseudo_fm") = false,
		nb::arg("pseudo_precision") = false,
		nb::arg("pseudo_recall") = false,
		nb::arg("precision_weights") = std::vector<double>{},
		nb::arg("recall_weights") = std::vector<double>{},
		"Obtain specific binarization performance information based on a Ground Truth. "
		"Pseudo-metrics require precision and recall weight arrays.");

	nb::enum_<GrayscaleAlgorithms>(m, "GrayscaleAlgorithms")
		.value("MEAN", GrayscaleAlgorithms::MEAN)
		.value("QT", GrayscaleAlgorithms::QT)
		.value("BT601", GrayscaleAlgorithms::BT601)
		.value("BT709", GrayscaleAlgorithms::BT709)
		.value("BT2100", GrayscaleAlgorithms::BT2100)
		.value("VALUE", GrayscaleAlgorithms::VALUE)
		.value("LUSTER", GrayscaleAlgorithms::LUSTER)
		.value("LIGHTNESS", GrayscaleAlgorithms::LIGHTNESS)
		.value("MINAVG", GrayscaleAlgorithms::MINAVG)
		.export_values();

	m.def("to_grayscale", &ToGrayscale,
		nb::arg("algorithm"),
		nb::arg("color_image"),
		"Convert an RGB or RGBA image to 8-bit grayscale.");

	m.def("to_binary", &ToBinary,
		nb::arg("algorithm"),
		nb::arg("image"),
		nb::arg("parameters") = ParameterMap(),
		"Convert a grayscale image to binary, returning a new image.");

	m.def("update_to_binary", &UpdateToBinary,
		nb::arg("algorithm"),
		nb::arg("image"),
		nb::arg("parameters") = ParameterMap(),
		"Convert a grayscale image to binary in-place.");

	nb::class_<Binarization> binarization(m, "Binarization");

	binarization.def(nb::init<const Algorithms>())
		.def("initialize", &Binarization::Initialize)
		.def("to_binary", &Binarization::ToBinary,
			nb::arg("binaryImageArray"),
			nb::arg("parameters") = ParameterMap())
		.def("algorithm", &Binarization::CurrentAlgorithm);

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