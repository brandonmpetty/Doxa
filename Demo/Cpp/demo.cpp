#include <iostream>
#include "../../../Doxa/Sauvola.hpp"
#include "../../../Doxa/ClassifiedPerformance.hpp"
#include "../../../Doxa/DRDM.hpp"
#include "../../../Doxa/PNM.hpp"

// Visual C++ Compiler:
//cl /EHsc /std:c++17 /O2 demo.cpp


void DisplayPerformance(const Doxa::Image& groundTruthImage, const Doxa::Image& binaryImage)
{
	Doxa::ClassifiedPerformance::Classifications classifications;
	bool canCompare = Doxa::ClassifiedPerformance::CompareImages(classifications, groundTruthImage, binaryImage);
	if (!canCompare)
	{
		std::cout << "Files cannot be compared.  Ensure both images have the same height and width." << std::endl;
		return;
	}

	double scoreAccuracy = Doxa::ClassifiedPerformance::CalculateAccuracy(classifications);
	double scoreFM = Doxa::ClassifiedPerformance::CalculateFMeasure(classifications);
	double scorePSNR = Doxa::ClassifiedPerformance::CalculatePSNR(classifications);
	double scoreNRM = Doxa::ClassifiedPerformance::CalculateNRM(classifications);
	double scoreDRDM = Doxa::DRDM::CalculateDRDM(groundTruthImage, binaryImage);

	std::cout << std::endl
		<< "Accuracy:\t" << scoreAccuracy << std::endl
		<< "F-Measure:\t" << scoreFM << std::endl
		<< "PSNR:\t\t" << scorePSNR << std::endl
		<< "NRM:\t\t" << scoreNRM << std::endl
		<< "DRDM:\t\t" << scoreDRDM << std::endl
		<< std::endl;
}

int main()
{
	// Read image and turn it into an 8bit grayscale.
	// The PNM reader is obviously limiting, but does offer 8 different color to grayscale algorithms.
	Doxa::Image doxaGsImage = Doxa::PNM::Read(R"(2JohnC1V3.ppm)", 
		Doxa::Parameters({{"grayscale", Doxa::PNM::GrayscaleConversion::Mean}})); // Optional

	// Use a binarization algorithm to convert it into black and white
	const Doxa::Parameters parameters({ {"window", 25}, {"k", 0.10} });
	Doxa::Sauvola::UpdateToBinary(doxaGsImage, parameters);

	// If you want to store the binary image in a new object, run this:
	//Doxa::Image doxaBinImage = Doxa::Sauvola::ToBinaryImage(doxaGsImage, parameters);

	// Load the ground truth image
	Doxa::Image doxaGtImage = Doxa::PNM::Read(R"(2JohnC1V3-GroundTruth.pbm)");

	// Get Performance information
	DisplayPerformance(doxaGtImage, doxaGsImage);

	// Save the processed image
	Doxa::PNM::Write(doxaGsImage, R"(binary.pbm)");

	return 0;
}
