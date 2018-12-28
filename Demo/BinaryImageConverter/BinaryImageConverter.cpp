// Δoxa Binarization Framework Demo
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#include <iostream>
#include "../../Doxa/Image.hpp"
#include "../../Doxa/PNM.hpp"
#include "../../Doxa/KitchenSinkCalculator.hpp"
#include "../../Doxa/Otsu.hpp"
#include "../../Doxa/Bernsen.hpp"
#include "../../Doxa/Niblack.hpp"
#include "../../Doxa/Sauvola.hpp"
#include "../../Doxa/Wolf.hpp"
#include "../../Doxa/Nick.hpp"
#include "../../Doxa/Gatos.hpp"
#include "../../Doxa/Su.hpp"
#include "../../Doxa/TRSing.hpp"
#include "../../Doxa/Wan.hpp"

using namespace std;
using namespace Doxa;

// Forward Declarations
int Help(const int returnValue);


/// <summary>
/// BinaryImageConverter is a demo application allowing one to easily create binary images to compare algorithms.
/// </summary>
int main(int argc, char* argv[])
{
	if (argc < 3) return Help(0);

	bool otsu = false;
	bool bernsen = false;
	bool niblack = false;
	bool sauvola = false;
	bool wolf = false;
	bool nick = false;
	bool gatos = false;
	bool su = false;
	bool trsing = false;
	bool wan = false;

	std::string source;
	int g = 0;
	int w = 0;
	double k = 0.0;

	for (int idx = 1; idx < argc; ++idx)
	{
		std::string arg = argv[idx];

		if (arg.compare("-otsu") == 0)
			otsu = true;
		else if (arg.compare("-bernsen") == 0)
			bernsen = true;
		else if (arg.compare("-niblack") == 0)
			niblack = true;
		else if (arg.compare("-sauvola") == 0)
			sauvola = true;
		else if (arg.compare("-wolf") == 0)
			wolf = true;
		else if (arg.compare("-nick") == 0)
			nick = true;
		else if (arg.compare("-gatos") == 0)
			gatos = true;
		else if (arg.compare("-su") == 0)
			su = true;
		else if (arg.compare("-trsing") == 0)
			trsing = true;
		else if (arg.compare("-wan") == 0)
			wan = true;
		else if (arg.compare("--source") == 0)
		{
			if (++idx >= argc) return Help(0);
			source = fs::absolute(argv[idx]).string();
		}
		else if (arg.compare("--w") == 0)
		{
			if (++idx >= argc) return Help(0);
			w = std::stoi(argv[idx]);
		}
		else if (arg.compare("--k") == 0)
		{
			if (++idx >= argc) return Help(0);
			k = std::stod(argv[idx]);
		}
		else if (arg.compare("--g") == 0)
		{
			if (++idx >= argc) return Help(0);
			g = std::stoi(argv[idx]);
		}
	}

	if (source == "") return Help(0);
	if (!otsu && !bernsen && !niblack && !sauvola && !wolf && !nick && !gatos && !su && !trsing && !wan) 
		return Help(0);

	try
	{
		const Image image = PNM::Read(source);

		// Remove extension from source
		std::string output = source.erase(source.find_last_of("."), string::npos);

		// Setup base params
		Parameters parameters({ { "window", w == 0 ? 75 : w } });

		if (otsu)
		{
			Image binaryImage = Otsu::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Otsu.pbm");
		}

		if (bernsen)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = Bernsen::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Bernsen.pbm");
		}

		if (niblack)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = Niblack::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Niblack.pbm");
		}

		if (sauvola)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = Sauvola::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Sauvola.pbm");
		}

		if (wolf)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = Wolf::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Wolf.pbm");
		}

		if (nick)
		{
			parameters.Set("k", k == 0.0 ? -0.2 : k);
			Image binaryImage = Nick::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Nick.pbm");
		}

		if (gatos)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			parameters.Set("glyph", g == 0 ? 60 : g);

			Image binaryImage = Gatos::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Gatos.pbm");
		}

		if (su)
		{
			Image binaryImage = Su::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Su.pbm");
		}

		if (trsing)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = TRSing::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-TRSing.pbm");
		}

		if (wan)
		{
			parameters.Set("k", k == 0.0 ? 0.2 : k);
			Image binaryImage = Wan::ToBinaryImage(image, parameters);
			PNM::Write(binaryImage, output + "-Wan.pbm");
		}
	}
	catch (const char* error)
	{
		cout << "Error: " << error << endl;
		return 1;
	}
	catch (...)
	{
		cout << "Error converting image to binary." << endl;
		return 1;
	}

	return 0;
}

int Help(const int returnValue)
{
	cout << endl
		<< "BinaryImageConverter v1.0" << endl
		<< endl
		<< "This application will convert a color or greyscale image into a black and white binary image." << endl
		<< "For now, the source must be a Portable Any-Map files (.pgm, .ppm, .pam)." << endl
		<< endl
		<< "Usage: BinaryImageConverter.exe --source <image location> [-<algorithm>] [--w <window size>] [--k <k value>]" << endl
		<< endl
		<< "Algorithms: otsu, bernsen, niblack, sauvola, wolf, nick, gatos, su, trsing, wan" << endl
		<< endl
		<< "Multiple algorithms can be specified at once.  Defaults: w = 75, k = 0.2 (Nick's k = -0.2), g = 60" << endl
		<< "Example: BinaryImageConverter.exe --source c:\\image.pam -wolf -sauvola --w 23 --k 0.15" << endl
		<< "Output:  c:\\image-Wolf.pam, c:\\image-Sauvola.pam" << endl
		<< endl
		<< "Note: Gatos is only partially implemented and can take in an optional glyph size, [--g <glyph size>]."
		<< endl
		<< endl
		<< "CC0 - Brandon M. Petty, 2018" << endl
		<< endl
		<< "To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide.  This software is distributed without any warranty."
		<< endl;

	return returnValue;
}
