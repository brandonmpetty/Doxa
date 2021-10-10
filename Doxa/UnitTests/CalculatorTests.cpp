#include "TestUtilities.hpp"
#include "../ChanMeanCalc.hpp"
#include "../ChanMeanVarianceCalc.hpp"
#include "../IntegralImageMeanVarianceCalc.hpp"
#include "../Grayscale.hpp"
#include "../Niblack.hpp"
#include <vector>
#include <tuple>


namespace Doxa::UnitTests
{
	TEST_CLASS(CalculatorTests)
	{
		// Initialized Objects
		static Image image;
		static std::string projFolder;

		// A sample algorithm that will allow us to switch out the calculator seemlessly
		// The library does not use this pattern because there is no reason to ever use Integral Images.
		template<typename Calculator>
		class NiblackBase : public Algorithm<NiblackBase<Calculator>>, public Calculator
		{
		public:

			void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
			{
				// Read parameters, utilizing defaults
				const int windowSize = parameters.Get("window", 75);
				const double k = parameters.Get("k", 0.2);

				Calculator::Process(binaryImageOut, Algorithm<NiblackBase<Calculator>>::grayScaleImageIn, windowSize, 
					[&](const double& mean, const double& variance, const int&) {

					const double stddev = std::sqrt(variance);

					return (mean + (k * stddev));
				});
			}
		};

	public:

		TEST_CLASS_INITIALIZE(Initialize)
		{
			projFolder = TestUtilities::ProjectFolder();

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.ppm";
			image = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
		}

		TEST_METHOD(CalculateIntegralImagesTest)
		{
			// Setup
			const Pixel8 bits[] = {
				Grayscale::Qt(10, 20, 30), Grayscale::Qt(40, 50, 60), Grayscale::Qt(70, 80, 90),
				Grayscale::Qt(30, 40, 50), Grayscale::Qt(50, 05, 05), Grayscale::Qt(50, 30, 10),
				Grayscale::Qt(03, 05, 07), Grayscale::Qt(11, 13, 17), Grayscale::Qt(00, 25, 12)
			};
			Image image(3, 3, bits);

			const IntegralImage integralImage = {
				18,  66, 144,
				56, 124, 235,
				60, 140, 265
			};

			const IntegralImage integralSquareImage = {
				324, 2628,  8712,
				1768, 4472, 11645,
				1784, 4632, 12001
			};

			// Test Integral and Squared Integral Image Creation
			IntegralImageMeanVarianceCalc meanVarianceCalculator;
			IntegralImage testIntegralImage(integralImage.size());
			IntegralImage testIntegralSquareImage(integralSquareImage);
			meanVarianceCalculator.BuildIntegralImages(testIntegralImage,testIntegralSquareImage, image);

			// Assert Single and Squared Integral Image Creation
			Assert::IsTrue(testIntegralImage == integralImage);
			Assert::IsTrue(testIntegralSquareImage == integralSquareImage);
		}

		TEST_METHOD(CalculateProcessMeanVarianceTest)
		{
			typedef std::vector< std::tuple<double, double> > meanVarianceVector;

			// Setup
			Pixel8 bits[] = {
				Grayscale::Qt(10, 20, 30), Grayscale::Qt(40, 50, 60), Grayscale::Qt(70, 80, 90),
				Grayscale::Qt(30, 40, 50), Grayscale::Qt(50, 05, 05), Grayscale::Qt(50, 30, 10),
				Grayscale::Qt(03, 05, 07), Grayscale::Qt(11, 13, 17), Grayscale::Qt(00, 25, 12)
			};
			Image image(3, 3, bits);
			Image output(3, 3);

			// Output variables
			meanVarianceVector meanVarianceII;
			meanVarianceVector meanChan;
			meanVarianceVector meanVarianceChan;

			// Integral Image Mean Variance
			IntegralImageMeanVarianceCalc meanVarianceCalculator;
			meanVarianceCalculator.Process(output, image, 3, [&](const double& mean, const double& variance, const int&) {
				meanVarianceII.push_back({ mean, variance });
				return 0.0;
			});

			// Chan Mean Variance
			ChanMeanVarianceCalc meanVarianceCalculatorChan;
			meanVarianceCalculatorChan.Process(output, image, 3, [&](const double& mean, const double& variance, const int&) {
				meanVarianceChan.push_back({ mean, variance });
				return 0.0;
			});

			// Chan Mean
			ChanMeanCalc meanCalculatorChan;
			meanCalculatorChan.Process(output, image, 3, [&](const double& mean, const int&) {
				meanChan.push_back({ mean, 0.0 });
				return 0.0;
			});

			// Assert
			Assert::AreEqual(std::get<0>(meanVarianceII.at(4)), 29.44, 0.01);
			// Note: If you use Sample Variance the value will be 524.77.  We are using Population Variance.
			//Assert::AreEqual(std::get<1>(meanVarianceII.at(4)), 524.77, 0.01);
			Assert::AreEqual(std::get<1>(meanVarianceII.at(4)), 466.469, 0.01);
			Assert::IsTrue(meanVarianceII == meanVarianceChan);
			
			for (int i = 0; i < image.size; ++i)
			{
				Assert::AreEqual(std::get<0>(meanVarianceII.at(i)), std::get<0>(meanChan.at(i)), 0.01);
			}
		}

		TEST_METHOD(CalculatorSpeedTest)
		{
			const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

			double niblackChanSpeed = TestUtilities::Time([&]() {
				Image imageNiblackChan = NiblackBase<ChanMeanVarianceCalc>::ToBinaryImage(image, parameters);
			});

			double niblackIISpeed = TestUtilities::Time([&]() {
				Image imageNiblackII = NiblackBase<IntegralImageMeanVarianceCalc>::ToBinaryImage(image, parameters);
			});

			Logger::WriteMessage(("Niblack-Chan Speed: " + std::to_string(niblackChanSpeed)).c_str());
			Logger::WriteMessage(("Niblack-Integral Image Speed: " + std::to_string(niblackIISpeed)).c_str());
		}

		TEST_METHOD(CalculatorAlgorithmTest)
		{
			const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

			Image imageNiblackChan = NiblackBase<ChanMeanVarianceCalc>::ToBinaryImage(image, parameters);
			Image imageNiblackII = NiblackBase<IntegralImageMeanVarianceCalc>::ToBinaryImage(image, parameters);

			TestUtilities::AssertImagesWithDetails(imageNiblackChan, imageNiblackII);
		}
	};

	// Static objects
	Image CalculatorTests::image;
	std::string CalculatorTests::projFolder;
}
