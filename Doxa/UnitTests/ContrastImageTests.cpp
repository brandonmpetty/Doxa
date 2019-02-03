#include "TestUtilities.hpp"
#include "../PNM.hpp"
#include "../ContrastImage.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(ContrastImageTests)
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

		TEST_METHOD(GenerateContrastImageTest)
		{
			Image contrastImage(image.width, image.height);
			ContrastImage::GenerateContrastImage(contrastImage, image);

			PNM::Write(contrastImage, projFolder + "2JohnC1V3-ContrastImage.ppm");
		}

		TEST_METHOD(GenerateHighContrastImageTest)
		{
			Image highContrastImage(image.width, image.height);
			ContrastImage::GenerateHighContrastImage(highContrastImage, image);

			PNM::Write(highContrastImage, projFolder + "2JohnC1V3-HighContrastImage.pbm");
		}
	};

	// Static objects
	Image ContrastImageTests::image;
	std::string ContrastImageTests::projFolder;
}
