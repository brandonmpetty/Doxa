#include "TestUtilities.hpp"
#include "../PNM.hpp"
#include "../Otsu.hpp"
#include "../AdOtsu.hpp"
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
#include "../Bataineh.hpp"


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
			image = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
		}

		TEST_METHOD(AlgorithmsSauvolaTest)
		{
			const Parameters parameters({ {"window", 27}, {"k", 0.10} });

			Image imageSauvola = Sauvola::ToBinaryImage(image, parameters);

			Image imageSauvola2(image);
			Sauvola::UpdateToBinary(imageSauvola2, parameters);

			TestUtilities::AssertImages(imageSauvola, imageSauvola2);
			TestUtilities::AssertImageFile(imageSauvola, projFolder + "2JohnC1V3-Sauvola.pbm");
		}

		TEST_METHOD(AlgorithmsNiblackTest)
		{
			const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

			Image imageNiblack = Niblack::ToBinaryImage(image, parameters);

			Image imageNiblack2(image);
			Niblack::UpdateToBinary(imageNiblack2, parameters);

			TestUtilities::AssertImages(imageNiblack, imageNiblack2);
			TestUtilities::AssertImageFile(imageNiblack, projFolder + "2JohnC1V3-Niblack.pbm");
		}

		TEST_METHOD(AlgorithmsWolfTest)
		{
			const Parameters parameters({ { "window", 21 }, { "k", 0.18 } });

			Image imageWolf = Wolf::ToBinaryImage(image, parameters);

			Image imageWolf2(image);
			Wolf::UpdateToBinary(imageWolf2, parameters);

			TestUtilities::AssertImages(imageWolf, imageWolf2);
			TestUtilities::AssertImageFile(imageWolf, projFolder + "2JohnC1V3-Wolf.pbm");
		}

		TEST_METHOD(AlgorithmsNICKTest)
		{
			const Parameters parameters({ { "window", 45 }, { "k", -0.10 } });

			Image imageNICK = Nick::ToBinaryImage(image, parameters);

			Image imageNICK2(image);
			Nick::UpdateToBinary(imageNICK2, parameters);

			TestUtilities::AssertImages(imageNICK, imageNICK2);
			TestUtilities::AssertImageFile(imageNICK, projFolder + "2JohnC1V3-NICK.pbm");
		}

		TEST_METHOD(AlgorithmsBernsenTest)
		{
			const Parameters parameters({ { "window", 61 }, { "threshold", 150 }, {"constrast-limit", 15} });

			Image imageBernsen = Bernsen::ToBinaryImage(image, parameters);

			Image imageBernsen2(image);
			Bernsen::UpdateToBinary(imageBernsen2, parameters);

			TestUtilities::AssertImages(imageBernsen, imageBernsen2);
			TestUtilities::AssertImageFile(imageBernsen, projFolder + "2JohnC1V3-Bensen.pbm");
		}

		TEST_METHOD(AlgorithmsTRSinghTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageTRSingh = TRSingh::ToBinaryImage(image, parameters);

			Image imageTRSingh2(image);
			TRSingh::UpdateToBinary(imageTRSingh2, parameters);

			TestUtilities::AssertImages(imageTRSingh, imageTRSingh2);
			TestUtilities::AssertImageFile(imageTRSingh, projFolder + "2JohnC1V3-TRSingh.pbm");
		}

		TEST_METHOD(AlgorithmsWANTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageWAN = Wan::ToBinaryImage(image, parameters);

			Image imageWAN2(image);
			Wan::UpdateToBinary(imageWAN2, parameters);

			TestUtilities::AssertImages(imageWAN, imageWAN2);
			TestUtilities::AssertImageFile(imageWAN, projFolder + "2JohnC1V3-WAN.pbm");
		}

		TEST_METHOD(AlgorithmsGatosTest)
		{
			const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

			Image imageGatos = Gatos::ToBinaryImage(image, parameters);

			Image imageGatos2(image);
			Gatos::UpdateToBinary(imageGatos2, parameters);

			TestUtilities::AssertImages(imageGatos, imageGatos2);
			TestUtilities::AssertImageFile(imageGatos, projFolder + "2JohnC1V3-Gatos.pbm");
		}

		TEST_METHOD(AlgorithmsSuTest)
		{
			Image imageSu = Su::ToBinaryImage(image);

			Image imageSu2(image);
			Su::UpdateToBinary(imageSu2);

			TestUtilities::AssertImages(imageSu, imageSu2);
			TestUtilities::AssertImageFile(imageSu, projFolder + "2JohnC1V3-Su.pbm");
		}

		TEST_METHOD(AlgorithmsISauvola)
		{
			const Parameters parameters({ {"window", 15}, {"k", 0.01} });

			Image imageISauvola = ISauvola::ToBinaryImage(image, parameters);

			Image imageISauvola2(image);
			ISauvola::UpdateToBinary(imageISauvola2, parameters);

			TestUtilities::AssertImages(imageISauvola, imageISauvola2);
			TestUtilities::AssertImageFile(imageISauvola, projFolder + "2JohnC1V3-ISauvola.pbm");
		}

		TEST_METHOD(AlgorithmsOtsuTest)
		{
			Image imageOtsu = Otsu::ToBinaryImage(image);

			Image imageOtsu2(image);
			Otsu::UpdateToBinary(imageOtsu2);

			TestUtilities::AssertImages(imageOtsu, imageOtsu2);
			TestUtilities::AssertImageFile(imageOtsu, projFolder + "2JohnC1V3-Otsu.pbm");
		}

		TEST_METHOD(AlgorithmsAdOtsuTest)
		{
			Image imageAdOtsu = AdOtsu::ToBinaryImage(image);
			PNM::Write(imageAdOtsu, projFolder + "2JohnC1V3-AdOtsu.pbm");

			//Image imageAdOtsu2(image);
			//AdOtsu::UpdateToBinary(imageAdOtsu2);

			//TestUtilities::AssertImages(imageAdOtsu, imageAdOtsu2);
			//TestUtilities::AssertImageFile(imageAdOtsu, projFolder + "2JohnC1V3-AdOtsu.pbm");
		}

		TEST_METHOD(AlgorithmsAdOtsuMSGTest)
		{
			Image imageAdOtsuMSG = AdOtsuMS::ToBinaryImage(image);
			PNM::Write(imageAdOtsuMSG, projFolder + "2JohnC1V3-AdOtsuMS2.pbm");

			//Image imageAdOtsu2(image);
			//AdOtsu::UpdateToBinary(imageAdOtsu2);

			//TestUtilities::AssertImages(imageAdOtsu, imageAdOtsu2);
			//TestUtilities::AssertImageFile(imageAdOtsu, projFolder + "2JohnC1V3-AdOtsuMSG.pbm");
		}

		TEST_METHOD(AlgorithmsBatainehTest)
		{
			Image imageBataineh = Bataineh::ToBinaryImage(image);

			Image imageBataineh2(image);
			Bataineh::UpdateToBinary(imageBataineh2);

			TestUtilities::AssertImages(imageBataineh, imageBataineh2);
			TestUtilities::AssertImageFile(imageBataineh, projFolder + "2JohnC1V3-Bataineh.pbm");
		}
	};

	// Static objects
	Image BinarizationTests::image;
	std::string BinarizationTests::projFolder;
}
