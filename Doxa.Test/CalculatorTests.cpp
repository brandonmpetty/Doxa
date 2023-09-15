#include "pch.h"
#include "ImageFixture.hpp"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class CalculatorTests : public ImageFixture {};

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


	TEST_F(CalculatorTests, CalculateIntegralImagesTest)
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
		EXPECT_TRUE(testIntegralImage == integralImage);
		EXPECT_TRUE(testIntegralSquareImage == integralSquareImage);
	}

	TEST_F(CalculatorTests, CalculateProcessMeanVarianceTest)
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
		EXPECT_NEAR(std::get<0>(meanVarianceII.at(4)), 29.44, 0.01);
		// Note: If you use Sample Variance the value will be 524.77.  We are using Population Variance.
		//EXPECT_NEAR(std::get<1>(meanVarianceII.at(4)), 524.77, 0.01);
		EXPECT_NEAR(std::get<1>(meanVarianceII.at(4)), 466.469, 0.01);
		EXPECT_TRUE(meanVarianceII == meanVarianceChan);
			
		for (int i = 0; i < image.size; ++i)
		{
			EXPECT_NEAR(std::get<0>(meanVarianceII.at(i)), std::get<0>(meanChan.at(i)), 0.01);
		}
	}

	TEST_F(CalculatorTests, CalculatorSpeedTest)
	{
		const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

		double niblackChanSpeed = TestUtilities::Time([&]() {
			Image imageNiblackChan = NiblackBase<ChanMeanVarianceCalc>::ToBinaryImage(image, parameters);
		});

		double niblackIISpeed = TestUtilities::Time([&]() {
			Image imageNiblackII = NiblackBase<IntegralImageMeanVarianceCalc>::ToBinaryImage(image, parameters);
		});

		SUCCEED() << "Niblack-Chan Speed: " << niblackChanSpeed;
		SUCCEED() << "Niblack-Integral Image Speed: " << niblackIISpeed;
	}

	TEST_F(CalculatorTests, CalculatorAlgorithmTest)
	{
		const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

		Image imageNiblackChan = NiblackBase<ChanMeanVarianceCalc>::ToBinaryImage(image, parameters);
		Image imageNiblackII = NiblackBase<IntegralImageMeanVarianceCalc>::ToBinaryImage(image, parameters);

		TestUtilities::AssertImagesWithDetails(imageNiblackChan, imageNiblackII);
	}
}
