#include "pch.h"
#include "BenchmarkHarness.hpp"
#include <PseudoWeights.hpp>


namespace Doxa::Benchmarks
{
	// PseudoWeights::Generate produces both DIBCO weight maps (GW for pseudo-Recall,
	// PW for pseudo-Precision) for a ground-truth page.  Generate is the end-to-end
	// cost; RecallWeights isolates the recall chain, so (Generate - Recall) is the
	// precision-specific work -- the split that tells us where to look before
	// optimizing anything.  The 2John page (707x441) is the shared benchmark fixture.
	static void BM_PseudoWeights_Generate(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image groundTruth = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			std::vector<double> gw, pw;
			PseudoWeights::Generate(gw, pw, groundTruth);
			benchmark::DoNotOptimize(gw.data());
			benchmark::DoNotOptimize(pw.data());
		}
	}
	BENCHMARK(BM_PseudoWeights_Generate);

	static void BM_PseudoWeights_Recall(benchmark::State& state)
	{
		const std::string dir = ResourcesDir();
		Image groundTruth = PNM::Read(dir + "2JohnC1V3-GroundTruth.pbm");

		for (auto _ : state) {
			std::vector<double> gw;
			PseudoWeights::RecallWeights(gw, groundTruth);
			benchmark::DoNotOptimize(gw.data());
		}
	}
	BENCHMARK(BM_PseudoWeights_Recall);

} // namespace Doxa::Benchmarks
