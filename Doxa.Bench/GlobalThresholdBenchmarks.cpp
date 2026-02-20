#include "pch.h"
#include "BenchmarkHarness.hpp"


namespace Doxa::Benchmarks
{
	static void BM_GlobalThreshold_Scalar(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image image = PNM::Read(dir + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", GrayscaleAlgorithms::QT} });
		Image binary(image.width, image.height);
		const Pixel8 threshold = 128;

		for (auto _ : state) {
			GlobalThresholdBenchHarness::ToBinary_STD(image.data, binary.data, image.size, threshold);
			benchmark::DoNotOptimize(binary.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_GlobalThreshold_Scalar);

	
#if defined(DOXA_SIMD)

	static void BM_GlobalThreshold_SIMD(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image image = PNM::Read(dir + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", GrayscaleAlgorithms::QT} });
		Image binary(image.width, image.height);
		const Pixel8 threshold = 128;

		for (auto _ : state) {
			GlobalThresholdBenchHarness::ToBinary_SIMD(image.data, binary.data, image.size, threshold);
			benchmark::DoNotOptimize(binary.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_GlobalThreshold_SIMD);

#endif // DOXA_SIMD

} // namespace Doxa::Benchmarks
