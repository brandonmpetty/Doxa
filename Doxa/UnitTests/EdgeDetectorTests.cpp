#include "TestUtilities.hpp"
#include "../EdgeDetector.hpp"


namespace Doxa::UnitTests
{
	TEST_CLASS(EdgeDetectorTests)
	{
	public:
		// Initialized Objects
		static Image image;
		static std::string projFolder;

		TEST_CLASS_INITIALIZE(Initialize)
		{
			projFolder = TestUtilities::ProjectFolder();

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.ppm";
			image = PNM::Read(filePath);
		}

		TEST_METHOD(EdgeDetectorLaplacianTest)
		{
			Image laplacianImage(image.width, image.height);
			EdgeDetector::Laplacian(laplacianImage, image);

			// TODO: Assert
			PNM::Write(laplacianImage, projFolder + "2JohnC1V3-LaplacianEdgeDetector.ppm");
		}

		TEST_METHOD(EdgeDetectorSobelTest)
		{
			Image sobelImage(image.width, image.height);
			EdgeDetector::Sobel(sobelImage, image);

			// TODO: Assert
			PNM::Write(sobelImage, projFolder + "2JohnC1V3-SobelEdgeDetector.ppm");
		}
	};

	// Static objects
	Image EdgeDetectorTests::image;
	std::string EdgeDetectorTests::projFolder;
}
