#ifndef BENCHMARKHARNESS_HPP
#define BENCHMARKHARNESS_HPP

#include "pch.h"
#include "config.hpp"


namespace Doxa::Benchmarks
{
	// Exposes GlobalThreshold internals for benchmarking
	class GlobalThresholdBenchHarness : public GlobalThreshold<GlobalThresholdBenchHarness>
	{
		Pixel8 Threshold(const Image& grayScaleImage, const Parameters& parameters = Parameters())
		{
			return 128;
		}
	};

	// Exposes DRDM internals for benchmarking
	class DRDMBenchHarness : public Doxa::DRDM
	{
	public:
		using DRDM::NUBN_STD;
		using DRDM::NUBN_STD_8x8;
		using DRDM::SumDRDkForMismatchedPixels;

		#if defined(DOXA_SIMD)
			using DRDM::NUBN_SIMD_8x8;
		#endif
	};

	// Switchable calculator backend for Niblack, used to benchmark calculators
	template<typename Calculator>
	class NiblackBase : public Algorithm<NiblackBase<Calculator>>, public Calculator
	{
	public:
		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			Calculator::Process(binaryImageOut, Algorithm<NiblackBase<Calculator>>::grayScaleImageIn, windowSize,
				[&](const double& mean, const double& variance, const int&) {

				const double stddev = std::sqrt(variance);

				return (mean + (k * stddev));
			});
		}
	};

	// Resource path helper
	inline std::string ResourcesDir()
	{
		return std::string(DOXA_BENCH_RESOURCES_DIR) + "/";
	}
}

#endif // BENCHMARKHARNESS_HPP
