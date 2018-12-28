// Δoxa Binarization Framework Demo
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#include <iostream>
#include "../../Doxa/Image.hpp"
#include "../../Doxa/PNM.hpp"
#include "../../Doxa/ClassifiedPerformance.hpp"
#include "../../Doxa/DRDM.hpp"

using namespace std;
using namespace Doxa;

// Forward Declarations
int Help(const int returnValue);
void DisplayMetrics(const double scoreAccuracy, const double scoreFM, const double scorePSNR, const double scoreNRM, const double scoreDRDM);


/// <summary>
/// PerformanceMetrics is a demo application providing binarization performance measures.
/// </summary>
int main(int argc, char* argv[])
{
	if (argc != 3) return Help(0);

	struct stat buffer;
	string groundTruthLocation = fs::absolute(argv[1]).string();
	string targetLocation = fs::absolute(argv[2]).string();

	// Check file existance
	if ((stat(groundTruthLocation.c_str(), &buffer) != 0) || (stat(targetLocation.c_str(), &buffer) != 0))
	{
		cout << "One or more files do not exist.  Check your arguments and file locations." << endl;
		return 1;
	}

	try
	{
		Image groundTruthImage = PNM::Read(groundTruthLocation);
		Image targetImage = PNM::Read(targetLocation);

		ClassifiedPerformance::Classifications classifications;
		bool canCompare = ClassifiedPerformance::CompareImages(classifications, groundTruthImage, targetImage);
		if (!canCompare)
		{
			cout << "Files cannot be compared.  Ensure both images have the same height and width." << endl;
			return 1;
		}

		double scoreAccuracy = ClassifiedPerformance::CalculateAccuracy(classifications);
		double scoreFM = ClassifiedPerformance::CalculateFMeasure(classifications);
		double scorePSNR = ClassifiedPerformance::CalculatePSNR(classifications);
		double scoreNRM = ClassifiedPerformance::CalculateNRM(classifications);
		double scoreDRDM = DRDM::CalculateDRDM(groundTruthImage, targetImage);

		DisplayMetrics(scoreAccuracy, scoreFM, scorePSNR, scoreNRM, scoreDRDM);
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
		return 1;
	}
	catch(...)
	{
		cout << "Error analyzing performance." << endl;
		return 1;
	}

	return 0;
}

int Help(const int returnValue)
{
	cout << endl
		<< "PerformanceMetrics v1.0" << endl
		<< endl
		<< "This application will display the binarization performance metrics for an image." << endl
		<< "For now, both the Ground Truth and Target Image must be Portable Any-Map files (.pbm, .pgm, .ppm, .pam)." << endl
		<< endl
		<< "Usage: PerformanceMetrics.exe <Ground Truth> <Target Image>" << endl
		<< endl
		<< endl
		<< "CC0 - Brandon M. Petty, 2018" << endl
		<< endl
		<< "To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide.  This software is distributed without any warranty."
		<< endl;

	return returnValue;
}

void DisplayMetrics(const double scoreAccuracy, const double scoreFM, const double scorePSNR, const double scoreNRM, const double scoreDRDM)
{
	cout << endl
		<< "Accuracy:\t"	<< scoreAccuracy << endl
		<< "F-Measure:\t"	<< scoreFM << endl
		<< "PSNR:\t\t"		<< scorePSNR << endl
		<< "NRM:\t\t"		<< scoreNRM << endl
		<< "DRDM:\t\t"		<< scoreDRDM << endl
		<< endl;
}
