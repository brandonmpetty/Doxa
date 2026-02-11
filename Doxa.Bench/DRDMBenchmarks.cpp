#include "pch.h"
#include "BenchmarkHarness.hpp"


namespace Doxa::Benchmarks
{
	static void BM_NUBN_STD(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image binaryImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			unsigned int count = DRDMBenchHarness::NUBN_STD(binaryImage, 8);
			benchmark::DoNotOptimize(count);
		}
	}
	BENCHMARK(BM_NUBN_STD);

	static void BM_NUBN_STD_8x8(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image binaryImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			unsigned int count = DRDMBenchHarness::NUBN_STD_8x8(binaryImage);
			benchmark::DoNotOptimize(count);
		}
	}
	BENCHMARK(BM_NUBN_STD_8x8);

	static void BM_SumDRDk(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image controlImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");
		Image experimentImage = PNM::Read(dir + "2JohnC1V3-Sauvola.pbm");

		for (auto _ : state) {
			uint64_t result = DRDMBenchHarness::SumDRDkForMismatchedPixels(controlImage, experimentImage);
			benchmark::DoNotOptimize(result);
		}
	}
	BENCHMARK(BM_SumDRDk);

	
#if defined(DOXA_SIMD)

	static void BM_NUBN_SIMD_8x8(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image binaryImage = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			unsigned int count = DRDMBenchHarness::NUBN_SIMD_8x8(binaryImage);
			benchmark::DoNotOptimize(count);
		}
	}
	BENCHMARK(BM_NUBN_SIMD_8x8);

#endif // DOXA_SIMD

} // namespace Doxa::Benchmarks
