/// Δoxa Binarization Framework
/// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Types.hpp"
#include "LocalWindow.hpp"


namespace Binarization
{
	class Algorithms
	{
	public:

		template<typename Calculator>
		static void Niblack(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize = 75, const double k = 0.2)
		{
			Calculator calculator(grayScaleImageIn);
			calculator.Initialize();

			double mean, stddev;

			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window) {
				calculator.CalculateMeanStdDev(mean, stddev, window);

				return (mean + (k * stddev));
			});
		}

		template<typename Calculator>
		static void Sauvola(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize = 75, const double k = 0.2)
		{
			Calculator calculator(grayScaleImageIn);
			calculator.Initialize();

			double mean, stddev;

			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window) {
				calculator.CalculateMeanStdDev(mean, stddev, window);

				return mean * (1 + k * ((stddev / 128) - 1));
			});
		}

		template<typename Calculator>
		static void Wolf(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize = 75, const double k = 0.2)
		{
			Calculator calculator(grayScaleImageIn);
			calculator.Initialize();

			double mean, stddev;
			double min = std::numeric_limits<double>::max();
			double maxStdDev = std::numeric_limits<double>::min();

			LocalWindow::Iterate(grayScaleImageIn, windowSize, [&](const Region& window, const int& position) {
				calculator.CalculateMeanStdDev(mean, stddev, window);
				if (stddev > maxStdDev) maxStdDev = stddev;

				const double tmpMin = grayScaleImageIn.data[position];
				if (tmpMin < min) min = tmpMin;
			});

			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window) {
				calculator.CalculateMeanStdDev(mean, stddev, window);

				return mean - k * (1 - (stddev / maxStdDev)) * (mean - min);
			});
		}

		template<typename Calculator>
		static void Nick(Image& binaryImageOut, const Image& grayScaleImageIn, const int windowSize = 75, const double k = -0.2)
		{
			Calculator calculator(grayScaleImageIn);
			calculator.Initialize();

			double mean, variance;

			LocalWindow::Process(binaryImageOut, grayScaleImageIn, windowSize, [&](const Region& window) {
				calculator.CalculateMeanVariance(mean, variance, window);

				return mean + (k * sqrt(variance + (mean*mean)));
			});
		}
	};
}


#endif //ALGORITHMS_HPP
