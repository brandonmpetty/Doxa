#include <opencv2/opencv.hpp>
#include "../../Doxa/Sauvola.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"

// Visual C++ Compiler:
//cl /EHsc /std:c++17 /O2 /I"%OPENCV_DIR%\include" "%OPENCV_DIR%\x64\vc15\lib\opencv_world451.lib"  demoOpenCV.cpp


Doxa::Image ToDoxaImageReference(const cv::Mat& gsImage)
{
	assert(gsImage.channels() == 1);
	return Doxa::Image::Reference(gsImage.cols, gsImage.rows, (Doxa::Pixel8*)gsImage.data);
}

cv::Mat FromDoxaImage(const Doxa::Image& binaryImage)
{
	return cv::Mat(binaryImage.height, binaryImage.width, CV_8UC1, binaryImage.data);
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
	// Read image and turn it into an 8bit grayscale.  This should be a CV_8UC1 structure.
	cv::Mat cvGsImage = cv::imread(R"(2JohnC1V3.png)", cv::IMREAD_GRAYSCALE);
	
	// Create a reference to the cv::Mat image.
	// Not only is this effecient, but any changes made by our algorithm apply directly
	// to the image being referenced.
	Doxa::Image doxaGsImage = ToDoxaImageReference(cvGsImage);

	// Use a binarization algorithm to convert it into black and white
	const Doxa::Parameters parameters({ {"window", 25}, {"k", 0.10} });
	Doxa::Sauvola::UpdateToBinary(doxaGsImage, parameters);
	
	// If you want to store the binary image in a new object, run this:
	//Doxa::Image doxaBinImage = Doxa::Sauvola::ToBinaryImage(doxaGsImage, parameters);
	//cv::Mat cvBinImage = FromDoxaImage(doxaBinImage);

	// Load the ground truth image
	cv::Mat cvGtImage = cv::imread(R"(2JohnC1V3-GroundTruth.png)", cv::IMREAD_GRAYSCALE);
	Doxa::Image doxaGtImage = ToDoxaImageReference(cvGtImage);
	
	// Get Performance information
	DisplayPerformance(doxaGtImage, doxaGsImage);

	// Save the processed image
	cv::imwrite(R"(binary.png)", cvGsImage);
	
	return 0;
}
