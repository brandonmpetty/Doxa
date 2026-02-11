#include "pch.h"
#include "BenchmarkHarness.hpp"


namespace Doxa::Benchmarks
{
	static void BM_Niblack_Chan(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image image = PNM::Read(dir + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
		const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

		for (auto _ : state) {
			Image result = NiblackBase<ChanMeanVarianceCalc>::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Niblack_Chan);

	static void BM_Niblack_IntegralImage(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image image = PNM::Read(dir + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
		const Parameters parameters({ { "window", 223 }, { "k", -0.61 } });

		for (auto _ : state) {
			Image result = NiblackBase<IntegralImageMeanVarianceCalc>::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Niblack_IntegralImage);

} // namespace Doxa::Benchmarks
