#include "CppUnitTest.h"
#include "../Image.hpp"
#include "../GatosWorkflow.hpp"
#include "../PPM.hpp"
#include "../ShafaitCalculator.hpp"

// Used for expanding macro based directives
#define STR(x) #x
#define EXPAND(x) STR(x)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	// This code is still experimental
	TEST_CLASS(GatosWorkflowTests)
	{
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
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(GatosWorkflowTest)
		{
			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.pam";
			Image image;
			PPM::Read(filePath, image);

			// Convert to Gray Scale
			// Note: Not a legitimate PAM image, so do not save this image.
			Preprocessor::ToGreyScale(image);

			Image binaryImage(image.width, image.height);

			// Run workflow
			GatosWorkflow gatos;
			gatos.Run<Shafait>(binaryImage, image);

			// TODO: Update this test to assert correctness
			Assert::IsNotNull(binaryImage.data);
		}
	};

	// Static objects
	std::string UnitTests::GatosWorkflowTests::projFolder;
}
