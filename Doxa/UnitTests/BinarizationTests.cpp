#include "CppUnitTest.h"
#include "../Otsu.hpp"
#include "../Bernsen.hpp"
#include "../Niblack.hpp"
#include "../Sauvola.hpp"
#include "../Wolf.hpp"
#include "../Gatos.hpp"
#include "../Nick.hpp"
#include "../TRSingh.hpp"
#include "../Wan.hpp"
#include "../Su.hpp"
#include "../KitchenSinkCalculator.hpp"
#include "../PNM.hpp"

// Used for expanding macro based directives
#define STR(x) #x
#define EXPAND(x) STR(x)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Doxa::UnitTests
{
	TEST_CLASS(BinarizationTests)
	{
		// Utilities
		void Compare(const Image& imageA, const Image& imageB)
		{
			Assert::AreEqual(imageA.size, imageB.size);

			const int result = std::memcmp(imageA.data, imageB.data, sizeof(Pixel8) * imageA.size);
			Assert::AreEqual(0, result);
		}

		void Compare(const Image& experement, std::string filePath)
		{
			Image control = PNM::Read(filePath);

			Compare(control, experement);
		}

		// Initialized Objects
		static Image image;
		static std::string projFolder;

	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			// Obtain the project folder
			// Note: Tests are to be ran in VS.  If this is not the case, change how this is being set.
			//       This was done to avoid baking in the images into the .exe, or copying them on build.
			projFolder = EXPAND(UNITTESTPRJ);
			projFolder.erase(0, 1); // Erase first quote
			projFolder.erase(projFolder.size() - 2); // Erase first quote and period, which is used to excape the trailing slash

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.ppm";
			image = PNM::Read(filePath);
		}

		TEST_METHOD(AlgorithmsSauvolaTest)
		{
			const Parameters parameters({ {"window", 26}, {"k", 0.10} });

			Image imageSauvola = Sauvola::ToBinaryImage(image, parameters);

			Compare(imageSauvola, projFolder + "2JohnC1V3-Sauvola.pbm");
		}

		TEST_METHOD(AlgorithmsNiblackTest)
		{
			const Parameters parameters({ { "window", 223 },{ "k", -0.61 } });

			Image imageNiblack = Niblack::ToBinaryImage(image, parameters);

			Compare(imageNiblack, projFolder + "2JohnC1V3-Niblack.pbm");
		}

		TEST_METHOD(AlgorithmsWolfTest)
		{
			const Parameters parameters({ { "window", 20 },{ "k", 0.18 } });

			Image imageWolf = Wolf::ToBinaryImage(image, parameters);

			Compare(imageWolf, projFolder + "2JohnC1V3-Wolf.pbm");
		}

		TEST_METHOD(AlgorithmsNICKTest)
		{
			const Parameters parameters({ { "window", 44 },{ "k", -0.10 } });

			Image imageNICK = Nick::ToBinaryImage(image, parameters);

			Compare(imageNICK, projFolder + "2JohnC1V3-NICK.pbm");
		}

		TEST_METHOD(AlgorithmsBernsenTest)
		{
			const Parameters parameters({ { "window", 60 },{ "threshold", 150 }, {"constrast-limit", 15} });

			Image imageBernsen = Bernsen::ToBinaryImage(image, parameters);

			Compare(imageBernsen, projFolder + "2JohnC1V3-Bensen.pbm");
		}

		TEST_METHOD(AlgorithmsTRSinghTest)
		{
			const Parameters parameters({ { "window", 75 },{ "k", 0.2 } });

			Image imageTRSing = TRSingh::ToBinaryImage(image, parameters);

			Compare(imageTRSing, projFolder + "2JohnC1V3-TRSing.pbm");
		}

		TEST_METHOD(AlgorithmsWANTest)
		{
			const Parameters parameters({ { "window", 75 },{ "k", 0.2 } });

			Image imageWAN = Wan::ToBinaryImage(image, parameters);

			Compare(imageWAN, projFolder + "2JohnC1V3-WAN.pbm");
		}

		TEST_METHOD(AlgorithmsGatosTest)
		{
			const Parameters parameters({ { "window", 75 },{ "k", 0.2 } });

			Image imageGatos = Gatos::ToBinaryImage(image, parameters);

			Compare(imageGatos, projFolder + "2JohnC1V3-Gatos.pbm");
		}

		TEST_METHOD(AlgorithmsSuTest)
		{
			Image imageSu = Su::ToBinaryImage(image, Parameters());

			Compare(imageSu, projFolder + "2JohnC1V3-Su.pbm");
		}

		TEST_METHOD(AlgorithmsOtsuTest)
		{
			Image imageOtsu = Otsu::ToBinaryImage(image, Parameters());

			Compare(imageOtsu, projFolder + "2JohnC1V3-Otsu.pbm");
		}
	};

	// Static objects
	Image BinarizationTests::image;
	std::string BinarizationTests::projFolder;
}
