#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "../../Doxa/BinarizationFactory.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"

namespace py = pybind11;
using namespace Doxa;


// Pybind helper for converting from an array to a Doxa Image.  This will reference the array, not create a copy.
Image ArrayToImage(const py::array_t<Doxa::Pixel8>& image)
{
	return Image::Reference(image.shape(1), image.shape(0), reinterpret_cast<Pixel8*>(image.request().ptr));
}

struct Performance
{
	double Accuracy;
	double FM;
	double PSNR;
	double NRM;
	double DRDM;
};

double CalculatePerformance(const py::array_t<Pixel8>& groundTruthArray, const py::array_t<Pixel8>& binaryArray)
{
	Image groundTruthImage = ArrayToImage(groundTruthArray);
	Image binaryImage = ArrayToImage(binaryArray);

	ClassifiedPerformance::Classifications classifications;
	ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
	// TODO: If this fails, we may want to 0 out the return values

	Performance perf;
	perf.Accuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
	perf.FM = ClassifiedPerformance::CalculateFMeasure(classifications);
	perf.PSNR = ClassifiedPerformance::CalculatePSNR(classifications);
	perf.NRM = ClassifiedPerformance::CalculateNRM(classifications);
	perf.DRDM = DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	return perf.Accuracy;
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

	void Initialize(const py::array_t<Pixel8>& grayScaleArray)
	{
		Image image = ArrayToImage(grayScaleArray);
		algorithmPtr->Initialize(image);
	}

	void ToBinary(const py::array_t<Pixel8>& binaryArray)
	{
		Image image = ArrayToImage(binaryArray);
		algorithmPtr->ToBinary(image);
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
}; // Class: Binarization


PYBIND11_MODULE(DoxaPy, m) {
	m.doc() = "DoxaPy: Python bindings for the Doxa image binarization framework";

	m.def("CalculatePerformance", &CalculatePerformance, "Obtain binarization performance information based on a Ground Truth.");

	py::class_<Binarization> binarization(m, "Binarization");

	binarization.def(py::init<const Algorithms>())
		.def("Initialize", &Binarization::Initialize)
		.def("ToBinary", &Binarization::ToBinary);

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