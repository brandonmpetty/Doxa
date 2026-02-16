#include "pch.h"
#include "BenchmarkHarness.hpp"


namespace Doxa::Benchmarks
{
	static Image ReadTestImage()
	{
		return PNM::Read(ResourcesDir() + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
	}

	// --- Global Thresholding ---

	static void BM_Otsu(benchmark::State& state)
	{
		const Image image = ReadTestImage();

		for (auto _ : state) {
			Image result = Otsu::ToBinaryImage(image);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Otsu);

	// --- Local Adaptive Thresholding ---

	static void BM_Niblack(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = Niblack::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Niblack);

	static void BM_Sauvola(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = Sauvola::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Sauvola);

	static void BM_Wolf(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = Wolf::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Wolf);

	static void BM_Nick(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", -0.2 } });

		for (auto _ : state) {
			Image result = Nick::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Nick);

	static void BM_Bernsen(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "threshold", 100 }, { "constrast-limit", 25 } });

		for (auto _ : state) {
			Image result = Bernsen::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Bernsen);

	static void BM_TRSingh(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = TRSingh::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_TRSingh);

	static void BM_Wan(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = Wan::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Wan);

	static void BM_Gatos(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = Gatos::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Gatos);

	static void BM_ISauvola(benchmark::State& state)
	{
		const Image image = ReadTestImage();
		const Parameters parameters({ { "window", 75 }, { "k", 0.2 } });

		for (auto _ : state) {
			Image result = ISauvola::ToBinaryImage(image, parameters);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_ISauvola);

	static void BM_Su(benchmark::State& state)
	{
		const Image image = ReadTestImage();

		for (auto _ : state) {
			Image result = Su::ToBinaryImage(image);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Su);

	static void BM_Bataineh(benchmark::State& state)
	{
		const Image image = ReadTestImage();

		for (auto _ : state) {
			Image result = Bataineh::ToBinaryImage(image);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Bataineh);

	static void BM_AdOtsu(benchmark::State& state)
	{
		const Image image = ReadTestImage();

		for (auto _ : state) {
			Image result = AdOtsu::ToBinaryImage(image);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_AdOtsu);

	static void BM_AdOtsuMS(benchmark::State& state)
	{
		const Image image = ReadTestImage();

		for (auto _ : state) {
			Image result = AdOtsuMS::ToBinaryImage(image);
			benchmark::DoNotOptimize(result.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_AdOtsuMS);

} // namespace Doxa::Benchmarks
