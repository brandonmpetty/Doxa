#include "pch.h"
#include "TestUtilities.hpp"
#include "ImageFixture.hpp"


namespace Doxa::UnitTests
{
	class BinarizationTests : public ImageFixture {};

	TEST_F(BinarizationTests, BinarizationSauvolaTest)
	{
		const Parameters parameters({ {"window", 27}, {"k", 0.10} });

		Image imageSauvola = Sauvola::ToBinaryImage(image, parameters);

		Image imageSauvola2(image);
		Sauvola::UpdateToBinary(imageSauvola2, parameters);

		TestUtilities::AssertImages(imageSauvola, imageSauvola2);
		TestUtilities::AssertImageFile(imageSauvola, projFolder + "2JohnC1V3-Sauvola.pbm");
	}

	TEST_F(BinarizationTests, BinarizationNiblackTest)
	{
		const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

		Image imageNiblack = Niblack::ToBinaryImage(image, parameters);

		Image imageNiblack2(image);
		Niblack::UpdateToBinary(imageNiblack2, parameters);

		TestUtilities::AssertImages(imageNiblack, imageNiblack2);
		TestUtilities::AssertImageFile(imageNiblack, projFolder + "2JohnC1V3-Niblack.pbm");
	}

	TEST_F(BinarizationTests, BinarizationWolfTest)
	{
		const Parameters parameters({ { "window", 21 }, { "k", 0.18 } });

		Image imageWolf = Wolf::ToBinaryImage(image, parameters);

		Image imageWolf2(image);
		Wolf::UpdateToBinary(imageWolf2, parameters);

		TestUtilities::AssertImages(imageWolf, imageWolf2);
		TestUtilities::AssertImageFile(imageWolf, projFolder + "2JohnC1V3-Wolf.pbm");
	}

	TEST_F(BinarizationTests, BinarizationNICKTest)
	{
		const Parameters parameters({ { "window", 45 }, { "k", -0.10 } });

		Image imageNICK = Nick::ToBinaryImage(image, parameters);

		Image imageNICK2(image);
		Nick::UpdateToBinary(imageNICK2, parameters);

		TestUtilities::AssertImages(imageNICK, imageNICK2);
		TestUtilities::AssertImageFile(imageNICK, projFolder + "2JohnC1V3-NICK.pbm");
	}

	TEST_F(BinarizationTests, BinarizationBernsenTest)
	{
		const Parameters parameters({ { "window", 61 }, { "threshold", 150 }, {"constrast-limit", 15} });

		Image imageBernsen = Bernsen::ToBinaryImage(image, parameters);

		Image imageBernsen2(image);
		Bernsen::UpdateToBinary(imageBernsen2, parameters);

		TestUtilities::AssertImages(imageBernsen, imageBernsen2);
		TestUtilities::AssertImageFile(imageBernsen, projFolder + "2JohnC1V3-Bensen.pbm");
	}

	TEST_F(BinarizationTests, BinarizationTRSinghTest)
	{
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		Image imageTRSingh = TRSingh::ToBinaryImage(image, parameters);

		Image imageTRSingh2(image);
		TRSingh::UpdateToBinary(imageTRSingh2, parameters);

		TestUtilities::AssertImages(imageTRSingh, imageTRSingh2);
		TestUtilities::AssertImageFile(imageTRSingh, projFolder + "2JohnC1V3-TRSingh.pbm");
	}

	TEST_F(BinarizationTests, BinarizationWANTest)
	{
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		Image imageWAN = Wan::ToBinaryImage(image, parameters);

		Image imageWAN2(image);
		Wan::UpdateToBinary(imageWAN2, parameters);

		TestUtilities::AssertImages(imageWAN, imageWAN2);
		TestUtilities::AssertImageFile(imageWAN, projFolder + "2JohnC1V3-WAN.pbm");
	}

	TEST_F(BinarizationTests, BinarizationGatosTest)
	{
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		Image imageGatos = Gatos::ToBinaryImage(image, parameters);

		Image imageGatos2(image);
		Gatos::UpdateToBinary(imageGatos2, parameters);

		TestUtilities::AssertImages(imageGatos, imageGatos2);
		TestUtilities::AssertImageFile(imageGatos, projFolder + "2JohnC1V3-Gatos.pbm");
	}

	TEST_F(BinarizationTests, BinarizationSuTest)
	{
		Image imageSu = Su::ToBinaryImage(image);

		Image imageSu2(image);
		Su::UpdateToBinary(imageSu2);

		TestUtilities::AssertImages(imageSu, imageSu2);
		TestUtilities::AssertImageFile(imageSu, projFolder + "2JohnC1V3-Su.pbm");
	}

	TEST_F(BinarizationTests, BinarizationISauvola)
	{
		const Parameters parameters({ {"window", 15}, {"k", 0.01} });

		Image imageISauvola = ISauvola::ToBinaryImage(image, parameters);

		Image imageISauvola2(image);
		ISauvola::UpdateToBinary(imageISauvola2, parameters);

		TestUtilities::AssertImages(imageISauvola, imageISauvola2);
		TestUtilities::AssertImageFile(imageISauvola, projFolder + "2JohnC1V3-ISauvola.pbm");
	}

	TEST_F(BinarizationTests, BinarizationOtsuTest)
	{
		Image imageOtsu = Otsu::ToBinaryImage(image);

		Image imageOtsu2(image);
		Otsu::UpdateToBinary(imageOtsu2);

		TestUtilities::AssertImages(imageOtsu, imageOtsu2);
		TestUtilities::AssertImageFile(imageOtsu, projFolder + "2JohnC1V3-Otsu.pbm");
	}

	TEST_F(BinarizationTests, BinarizationAdOtsuTest)
	{
		// DEMO!  Raw AdOtsu
		Image imageAdOtsu = AdOtsu::ToBinaryImage(image);
		PNM::Write(imageAdOtsu, projFolder + "2JohnC1V3-AdOtsu.pbm");

		// DEMO! AdOtsu /w Multi-Scale
		Image imageAdOtsuMSG = AdOtsuMS::ToBinaryImage(image);
		PNM::Write(imageAdOtsuMSG, projFolder + "2JohnC1V3-AdOtsuMS.pbm");
	}

	TEST_F(BinarizationTests, BinarizationBatainehTest)
	{
		Image imageBataineh = Bataineh::ToBinaryImage(image);

		Image imageBataineh2(image);
		Bataineh::UpdateToBinary(imageBataineh2);

		TestUtilities::AssertImages(imageBataineh, imageBataineh2);
		TestUtilities::AssertImageFile(imageBataineh, projFolder + "2JohnC1V3-Bataineh.pbm");
	}
}
