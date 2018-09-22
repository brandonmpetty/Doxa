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
	/// <summary>
	/// WARNING!  The Gatos Workflow is highly experimental.
	/// None of these tests will run by default.  They are mostly, if not all, stubbed and make no real assertions.
	/// </summary>
	TEST_CLASS(GatosWorkflowTests)
	{
		static std::string projFolder;

	public:

		// Exposes protected methods for Unit Testing
		class GatosWorkflowTestharness : public GatosWorkflow
		{
		public:			
			using GatosWorkflow::WienerFilter;
			using GatosWorkflow::ExtractBackground;
			using GatosWorkflow::AverageBgTextValue;
			using GatosWorkflow::AverageFgBgDistance;
			using GatosWorkflow::Threshold;
		};

		TEST_CLASS_INITIALIZE(Initialize)
		{
			// Obtain the project folder
			// Note: Tests are to be ran in VS.  If this is not the case, change how this is being set.
			//       This was done to avoid baking in the images into the .exe, or copying them on build.
			projFolder = EXPAND(UNITTESTPRJ);
			projFolder.erase(0, 1); // Erase first quote
			projFolder.erase(projFolder.size() - 2); // Erase first quote and period, which is used to excape the trailing slash
		}

		TEST_METHOD(GatosWorkflowTest)
		{
			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.pam";
			Image image = PPM::Read(filePath);

			// Convert to Gray Scale
			// Note: Not a legitimate PAM image, so do not save this image.
			Preprocessor::ToGreyScale(image);

			Image binaryImage(image.width, image.height);

			// Run workflow
			GatosWorkflow gatos;
			gatos.ToBinary<Shafait>(binaryImage, image, 60, 40, 0.15);

			// TODO: Update this test to assert correctness
			Assert::IsNotNull(binaryImage.data);

			// Analyze the results outside of the test
			//PPM::Write(binaryImage, projFolder + "2JohnCV13-Gatos.pam");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowWienerFilterTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(GatosWorkflowWienerFilterTest)
		{
			Image inputImage;
			Image outputImage;

			GatosWorkflowTestharness gatos;
			gatos.WienerFilter<Shafait>(outputImage, inputImage);

			Assert::IsNotNull(outputImage.data);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowExtractBackgroundTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(GatosWorkflowExtractBackgroundTest)
		{
			Image backgroundImage;
			Image filteredImage;
			Image binaryImage;

			GatosWorkflowTestharness gatos;
			gatos.ExtractBackground(backgroundImage, filteredImage, binaryImage);

			Assert::IsNotNull(backgroundImage.data);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowAverageBgTextValueTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(GatosWorkflowAverageBgTextValueTest)
		{
			Image backgroundImage;
			Image binaryImage;

			GatosWorkflowTestharness gatos;
			double value = gatos.AverageBgTextValue(backgroundImage, binaryImage);

			Assert::AreEqual(0.0, value);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowAverageFgBgDistanceTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(GatosWorkflowAverageFgBgDistanceTest)
		{
			Image backgroundImage;
			Image filteredImage;
			Image binaryImage;

			GatosWorkflowTestharness gatos;
			double value = gatos.AverageFgBgDistance(backgroundImage, filteredImage, binaryImage);

			Assert::AreEqual(0.0, value);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(GatosWorkflowThresholdTest)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(GatosWorkflowThresholdTest)
		{
			int backgroundValue = 0;
			double d = 0;
			double b = 0;

			GatosWorkflowTestharness gatos;
			double value = gatos.Threshold(backgroundValue, d, b);

			Assert::AreEqual(0.0, value);
		}
	};

	// Static objects
	std::string UnitTests::GatosWorkflowTests::projFolder;
}
