#include "pch.h"
#include "BenchmarkHarness.hpp"
#include <Morphology.hpp>


namespace Doxa::Benchmarks
{
	static Image ReadMorphologyTestImage()
	{
		return PNM::Read(ResourcesDir() + "2JohnC1V3.ppm", ParameterMap{ {"grayscale", GrayscaleAlgorithms::QT} });
	}

	// vHGW runs in near-constant time across window sizes; a regression that reintroduces
	// window-size sensitivity will show up in the larger arguments.
	static void BM_Dilate(benchmark::State& state)
	{
		const Image image = ReadMorphologyTestImage();
		Image morphedImage(image.width, image.height);
		const int windowSize = static_cast<int>(state.range(0));

		for (auto _ : state) {
			Morphology::Dilate(morphedImage, image, windowSize);
			benchmark::DoNotOptimize(morphedImage.data);
		}

		state.SetBytesProcessed(int64_t(state.iterations()) * image.size);
	}
	BENCHMARK(BM_Dilate)->Arg(3)->Arg(75)->Arg(255);

} // namespace Doxa::Benchmarks
