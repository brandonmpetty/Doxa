#include "pch.h"
#include "BenchmarkHarness.hpp"


namespace Doxa::Benchmarks
{
	static void BM_CompareImages_Scalar(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image binaryImage = PNM::Read(dir + "2JohnC1V3-Sauvola.pbm");
		Image groundTruthImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			ClassifiedPerformance::Classifications classifications;
			ClassifiedPerformance::CompareImages_STD(classifications, groundTruthImage.data, binaryImage.data, groundTruthImage.size);
			benchmark::DoNotOptimize(classifications);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * groundTruthImage.size);
	}
	BENCHMARK(BM_CompareImages_Scalar);


#if defined(DOXA_SIMD)

	static void BM_CompareImages_SIMD(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image binaryImage = PNM::Read(dir + "2JohnC1V3-Sauvola.pbm");
		Image groundTruthImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			ClassifiedPerformance::Classifications classifications;
			ClassifiedPerformance::CompareImages_SIMD(classifications, groundTruthImage.data, binaryImage.data, groundTruthImage.size);
			benchmark::DoNotOptimize(classifications);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * groundTruthImage.size);
	}
	BENCHMARK(BM_CompareImages_SIMD);

#endif // DOXA_SIMD

} // namespace Doxa::Benchmarks
