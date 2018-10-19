// Δoxa Binarization Framework Demo
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cassert>
#include <filesystem>
#include "../../Binarization/Algorithms.hpp"
#include "../../Binarization/DRDMPerformance.hpp"
#include "../../Binarization/Image.hpp"
#include "../../Binarization/PNM.hpp"
#include "../../Binarization/ShafaitCalculator.hpp"
#include "../../Binarization/Performance.hpp"
#include "../../Binarization/MetricUtils.hpp"

using namespace std;
using namespace Binarization;
namespace fs = std::experimental::filesystem;

// Forward Declarations
void CreateMeasureCSV(
	const std::string& csvFileLocation,
	const MetricUtils::Scores& scores,
	const int windowSizeStart,
	const int windowSizeStop,
	const double kStart,
	const double kStop,
	std::function<double(const MetricUtils::Score& score)> predicate);

void CreateCSVsForAllMeasures(
	const std::string& csvFileLocationBase,
	const MetricUtils::Scores& scores,
	const int windowSizeStart,
	const int windowSizeStop,
	const double kStart,
	const double kStop);

void DisplayPerformance(const MetricUtils::Scores& scores);

int Help(const int returnValue);


/// <summary>
/// Kumite is an underground tournament based application where each algorithm fights for the honor of being first place.
/// Each binarization algorithm will first battle itself in a challenge known as Death by 1000 Paper-cuts.
/// The best Window Size and K-Value permutation for each algorithm will be entered into the championship round... to see who is the best.
/// Who said Image Binarization couldn't be fun?
/// 
/// This demo application will produce multiple performance measure CSVs which can be analyzed later.
/// A simple rank-based result details analysis will be displayed on the screen to provide some insight into the data. 
/// </summary>
int main(int argc, char* argv[])
{
	if (argc < 3) return Help(0);

	bool niblack = false;
	bool sauvola = false;
	bool wolf = false;
	bool nick = false;

	std::string source;
	std::string groundtruth;
	std::string outputFolder;

	// These defaults produce a nice square matrix of 180x180
	int windowSizeStart = 7;
	int windowSizeStop = 187;
	double kStart = -0.90;
	double kStop = 0.90;

	for (int idx = 1; idx < argc; ++idx)
	{
		std::string arg = argv[idx];

		if (arg.compare("-niblack") == 0)
			niblack = true;
		else if (arg.compare("-sauvola") == 0)
			sauvola = true;
		else if (arg.compare("-wolf") == 0)
			wolf = true;
		else if (arg.compare("-nick") == 0)
			nick = true;
		else if (arg.compare("--source") == 0)
		{
			if (++idx >= argc) return Help(0);
			source = fs::absolute(argv[idx]).string();
		}
		else if (arg.compare("--groundtruth") == 0)
		{
			if (++idx >= argc) return Help(0);
			groundtruth = fs::absolute(argv[idx]).string();
		}
		else if (arg.compare("--output") == 0)
		{
			if (++idx >= argc) return Help(0);
			outputFolder = fs::absolute(argv[idx]).string();
		}
		else if (arg.compare("--w") == 0)
		{
			if (++idx >= argc) return Help(0);

			char* nextToken;
			windowSizeStart = stoi(strtok_s(argv[idx], ",", &nextToken));
			windowSizeStop = stoi(nextToken);
		}
		else if (arg.compare("--k") == 0)
		{
			if (++idx >= argc) return Help(0);

			char* nextToken;
			kStart = stod(strtok_s(argv[idx], ",", &nextToken));
			kStop = stod(nextToken);
		}
	}

	if (source == "") return Help(0);
	if (!niblack && !sauvola && !wolf && !nick)
	{
		niblack = sauvola = wolf = nick = true;
	}

	try
	{
		const Image image = PNM::Read(source);
		const Image groundTruthImage = PNM::Read(groundtruth);

		// Initialize our integral image calculator once, for all iterations.
		Shafait calculator;
		calculator.Initialize(image);

		const int challengerCount = ((windowSizeStop - windowSizeStart) + 1) * ((100 * (abs(kStop - kStart)) + 1));

		// Before one can win a fight with others, one must first win the fight with one's self. -- Sensei Petty

		MetricUtils::Scores topScores;

		if (niblack)
		{
			// Get all performance measures
			MetricUtils::Scores scores;
			scores.reserve(challengerCount);

			MetricUtils::DeathBy1000PaperCuts(scores, groundTruthImage, image, windowSizeStart, windowSizeStop, kStart, kStop,
				[calculator](Image& experimentImage, const Image& inputImage, const int ws, const double k) {
				Niblack::ToBinary(experimentImage, inputImage, calculator, ws, k);
			});

			// Write out all CSVs for a deeper analysis
			if (outputFolder != "")
			{
				CreateCSVsForAllMeasures(outputFolder + "/Niblack", scores, windowSizeStart, windowSizeStop, kStart, kStop);
			}

			// Provide a Rank based analysis
			MetricUtils::CalculateTopRank(scores);
			scores[0].ID = "Niblack";
			topScores.push_back(scores[0]);
		}

		if (sauvola)
		{
			// Get all performance measures
			MetricUtils::Scores scores;
			scores.reserve(challengerCount);
			
			MetricUtils::DeathBy1000PaperCuts(scores, groundTruthImage, image, windowSizeStart, windowSizeStop, kStart, kStop,
				[calculator](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
				Sauvola::ToBinary(expirementImage, inputImage, calculator, ws, k);
			});

			// Write out all CSVs for a deeper analysis
			if (outputFolder != "")
			{
				CreateCSVsForAllMeasures(outputFolder + "/Sauvola", scores, windowSizeStart, windowSizeStop, kStart, kStop);
			}

			// Provide a Rank based analysis
			MetricUtils::CalculateTopRank(scores);
			scores[0].ID = "Sauvola";
			topScores.push_back(scores[0]);
		}

		if (wolf)
		{
			// Get all performance measures
			MetricUtils::Scores scores;
			scores.reserve(challengerCount);
			
			MetricUtils::DeathBy1000PaperCuts(scores, groundTruthImage, image, windowSizeStart, windowSizeStop, kStart, kStop,
				[calculator](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
				Wolf::ToBinary(expirementImage, inputImage, calculator, ws, k);
			});

			// Write out all CSVs for a deeper analysis
			if (outputFolder != "")
			{
				CreateCSVsForAllMeasures(outputFolder + "/Wolf", scores, windowSizeStart, windowSizeStop, kStart, kStop);
			}

			// Provide a Rank based analysis
			MetricUtils::CalculateTopRank(scores);
			scores[0].ID = "Wolf";
			topScores.push_back(scores[0]);
		}

		if (nick)
		{
			// Get all performance measures
			MetricUtils::Scores scores;
			scores.reserve(challengerCount);
			
			MetricUtils::DeathBy1000PaperCuts(scores, groundTruthImage, image, windowSizeStart, windowSizeStop, kStart, kStop,
				[calculator](Image& expirementImage, const Image& inputImage, const int ws, const double k) {
				Nick::ToBinary(expirementImage, inputImage, calculator, ws, k);
			});

			// Write out all CSVs for a deeper analysis
			if (outputFolder != "")
			{
				CreateCSVsForAllMeasures(outputFolder + "/Nick", scores, windowSizeStart, windowSizeStop, kStart, kStop);
			}

			// Provide a Rank based analysis
			MetricUtils::CalculateTopRank(scores);
			scores[0].ID = "Nick";
			topScores.push_back(scores[0]);
		}

		// "There can be only one!" --Highlander
		MetricUtils::CalculateTopRank(topScores);
		DisplayPerformance(topScores);
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
		return 1;
	}
	catch (...)
	{
		cout << "Error running the match." << endl;
		return 1;
	}

	return 0;
}

void CreateMeasureCSV(
	const std::string& csvFileLocation, 
	const MetricUtils::Scores& scores, 
	const int windowSizeStart, 
	const int windowSizeStop, 
	const double kStart, 
	const double kStop,
	std::function<double(const MetricUtils::Score& score)> predicate)
{
	const double kStopCorrection = kStop + 0.001;
	int index = 0;

	// Open all of our files at once
	ofstream csv;
	csv.open(csvFileLocation);

	// Write the column header
	for (double k = kStart; k <= kStopCorrection; k += 0.01)
	{
		csv << "," << k;
	}

	// Write row by row
	for (int ws = windowSizeStart; ws <= windowSizeStop; ++ws)
	{
		csv << endl << ws;

		for (double k = kStart; k <= kStopCorrection; k += 0.01)
		{
			assert(k == scores[index].k);
			assert(ws == scores[index].windowSize);

			csv << "," << predicate(scores[index]);
			
			index++;
		}
	}

	csv.close();
}

void CreateCSVsForAllMeasures(
	const std::string& csvFileLocationBase,
	const MetricUtils::Scores& scores,
	const int windowSizeStart,
	const int windowSizeStop,
	const double kStart,
	const double kStop)
{
	CreateMeasureCSV(csvFileLocationBase + "-Accuracy.csv", scores, windowSizeStart, windowSizeStop, kStart, kStop, [](const MetricUtils::Score& score) { 
		return score.accuracy; 
	});

	CreateMeasureCSV(csvFileLocationBase + "-FMeasure.csv", scores, windowSizeStart, windowSizeStop, kStart, kStop, [](const MetricUtils::Score& score) { 
		return score.fmeasure; 
	});

	CreateMeasureCSV(csvFileLocationBase + "-PSNR.csv", scores, windowSizeStart, windowSizeStop, kStart, kStop, [](const MetricUtils::Score& score) { 
		return score.psnr; 
	});

	CreateMeasureCSV(csvFileLocationBase + "-DRDM.csv", scores, windowSizeStart, windowSizeStop, kStart, kStop, [](const MetricUtils::Score& score) { 
		return score.drdm; 
	});

	CreateMeasureCSV(csvFileLocationBase + "-Time.csv", scores, windowSizeStart, windowSizeStop, kStart, kStop, [](const MetricUtils::Score& score) { 
		return score.time; 
	});
}

void DisplayPerformance(const MetricUtils::Scores& scores)
{
	cout << left
		<< setw(15) << "Algorithm"
		<< setw(15) << "Window"
		<< setw(15) << "K"
		<< setw(15) << "Accuracy"
		<< setw(15) << "F-Measure"
		<< setw(15) << "PSNR"
		<< setw(15) << "DRDM"
		<< setw(15) << "Time"
		<< endl;

	for (auto score : scores)
	{
		cout << left 
			<< setw(15) << score.ID 
			<< setw(15) << score.windowSize
			<< setw(15) << score.k
			<< setw(15) << score.accuracy
			<< setw(15) << score.fmeasure
			<< setw(15) << score.psnr
			<< setw(15) << score.drdm
			<< setw(15) << score.time
			<< endl;
	}
}

int Help(const int returnValue)
{
	cout << endl
		<< "Kumite v1.0" << endl
		<< endl
		<< "Kumite, where your binarization algorithms come to fight." << endl
		<< "Performance is calculated for every K and Window Size perumation, for each image." << endl
		<< "For now, both the Ground Truth and Source Image must be Portable Any-Map files (.pbm, .pgm, .ppm, .pam)." << endl
		<< endl
		<< "Usage: Kumite.exe --source <image location> --groundtruth <image location> [--output <folder location>] [-<algorithm>] [--w <min>,<max>] [--k <min>,<max>]" << endl
		<< endl
		<< "Algorithms: niblack, sauvola, wolf, nick" << endl
		<< endl
		<< "Defaults: All algorithms, w = 7,187, k = -0.90,0.90" << endl
		<< "If an output folder is specified, all data will be written to CSVs in the folder."
		<< endl
		<< endl
		<< "CC0 - Brandon M. Petty, 2018" << endl
		<< endl
		<< "To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide.  This software is distributed without any warranty."
		<< endl;

	return returnValue;
}
