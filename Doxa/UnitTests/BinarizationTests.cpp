#include "TestUtilities.hpp"
#include "../PNM.hpp"
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
#include "../ISauvola.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(BinarizationTests)
	{
		// Initialized Objects
		static Image image;
		static std::string projFolder;

	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			projFolder = TestUtilities::ProjectFolder();

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.ppm";
			image = PNM::Read(filePath);
		}

		TEST_METHOD(AlgorithmsSauvolaTest)
		{
			const Parameters parameters({ {"window", 27}, {"k", 0.10} });

			Image imageSauvola = Sauvola::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageSauvola, projFolder + "2JohnC1V3-Sauvola.pbm");
		}

		TEST_METHOD(AlgorithmsNiblackTest)
		{
			const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

			Image imageNiblack = Niblack::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageNiblack, projFolder + "2JohnC1V3-Niblack.pbm");
		}

		TEST_METHOD(AlgorithmsWolfTest)
		{
			const Parameters parameters({ { "window", 21 }, { "k", 0.18 } });

			Image imageWolf = Wolf::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageWolf, projFolder + "2JohnC1V3-Wolf.pbm");
		}

		TEST_METHOD(AlgorithmsNICKTest)
		{
			const Parameters parameters({ { "window", 45 }, { "k", -0.10 } });

			Image imageNICK = Nick::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageNICK, projFolder + "2JohnC1V3-NICK.pbm");
		}

		TEST_METHOD(AlgorithmsBernsenTest)
		{
			const Parameters parameters({ { "window", 61 }, { "threshold", 150 }, {"constrast-limit", 15} });

			Image imageBernsen = Bernsen::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageBernsen, projFolder + "2JohnC1V3-Bensen.pbm");
		}

		TEST_METHOD(AlgorithmsTRSinghTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageTRSing = TRSingh::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageTRSing, projFolder + "2JohnC1V3-TRSing.pbm");
		}

		TEST_METHOD(AlgorithmsWANTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageWAN = Wan::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageWAN, projFolder + "2JohnC1V3-WAN.pbm");
		}

		TEST_METHOD(AlgorithmsGatosTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageGatos = Gatos::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageGatos, projFolder + "2JohnC1V3-Gatos.pbm");
		}

		TEST_METHOD(AlgorithmsSuTest)
		{
			Image imageSu = Su::ToBinaryImage(image, Parameters());

			TestUtilities::AssertImageFile(imageSu, projFolder + "2JohnC1V3-Su.pbm");
		}

		TEST_METHOD(AlgorithmsISauvola)
		{
			const Parameters parameters({ {"window", 15}, {"k", 0.01} });

			Image imageISauvola = ISauvola::ToBinaryImage(image, parameters);

			TestUtilities::AssertImageFile(imageISauvola, projFolder + "2JohnC1V3-ISauvola.pbm");
		}

		TEST_METHOD(AlgorithmsOtsuTest)
		{
			Image imageOtsu = Otsu::ToBinaryImage(image, Parameters());

			TestUtilities::AssertImageFile(imageOtsu, projFolder + "2JohnC1V3-Otsu.pbm");
		}
	};

	// Static objects
	Image BinarizationTests::image;
	std::string BinarizationTests::projFolder;
}
