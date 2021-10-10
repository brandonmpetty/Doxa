#include <QImage>
#include <iostream>
#include <cassert>
#include "../../Doxa/Sauvola.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"

// Build Instructions - Windows
// qmake
// nmake


Doxa::Image ToDoxaImageReference(const QImage& gsImage)
{
	assert(gsImage.format() == QImage::Format_Grayscale8);
	return Doxa::Image::Reference(gsImage.width(), gsImage.height(), (Doxa::Pixel8*)gsImage.bits());
}

QImage FromDoxaImage(const Doxa::Image& binaryImage)
{
	// This QImage object does not contain a copy of the image memory, but a reference to it.
	return QImage(binaryImage.data, binaryImage.width, binaryImage.height, binaryImage.width, QImage::Format_Grayscale8);
}

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
	double scoreMCC = Doxa::ClassifiedPerformance::CalculateMCC(classifications);
	double scorePSNR = Doxa::ClassifiedPerformance::CalculatePSNR(classifications);
	double scoreNRM = Doxa::ClassifiedPerformance::CalculateNRM(classifications);
	double scoreDRDM = Doxa::DRDM::CalculateDRDM(groundTruthImage, binaryImage);
	
	std::cout << std::endl
		<< "Accuracy:\t"	<< scoreAccuracy << std::endl
		<< "F-Measure:\t"	<< scoreFM << std::endl
		<< "MCC:\t\t"		<< scoreMCC << std::endl
		<< "PSNR:\t\t"		<< scorePSNR << std::endl
		<< "NRM:\t\t"		<< scoreNRM << std::endl
		<< "DRDM:\t\t"		<< scoreDRDM << std::endl
		<< std::endl;
}

int main()
{
	// Read image and turn it into an 8bit grayscale.
	QImage qtGsImage(R"(2JohnC1V3.png)");
	qtGsImage = qtGsImage.convertToFormat(QImage::Format_Grayscale8);
	
	// Create a reference to the QImage.
	// Not only is this effecient, but any changes made by our algorithm apply directly
	// to the image being referenced.
	Doxa::Image doxaGsImage = ToDoxaImageReference(qtGsImage);

	// Use a binarization algorithm to convert it into black and white
	const Doxa::Parameters parameters({ {"window", 25}, {"k", 0.10} });
	Doxa::Sauvola::UpdateToBinary(doxaGsImage, parameters);
	
	// If you want to store the binary image in a new object, run this:
	//Doxa::Image doxaBinImage = Doxa::Sauvola::ToBinaryImage(doxaGsImage, parameters);
	//QImage qtBinImage = FromDoxaImage(doxaBinImage);

	// Load the ground truth image
	QImage qtGtImage(R"(2JohnC1V3-GroundTruth.png)");
	qtGtImage = qtGtImage.convertToFormat(QImage::Format_Grayscale8);
	Doxa::Image doxaGtImage = ToDoxaImageReference(qtGtImage);
	
	// Get Performance information
	DisplayPerformance(doxaGtImage, doxaGsImage);

	// Save the processed image
	qtGsImage.save(R"(binary.png)");
	
	return 0;
}
