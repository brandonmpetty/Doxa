# Δoxa Binarization Framework

[![codecov](https://codecov.io/gh/brandonmpetty/Doxa/graph/badge.svg?token=XMG2X9KQKJ)](https://codecov.io/gh/brandonmpetty/Doxa)

<p align="center">
	<img src="/README/2JohnC1V3.png" width="45%" height="45%"/>
	<img src="/README/2JohnC1V3-GroundTruth.png" width="45%" height="45%"/>
</p>

## Introduction
ΔBF is an image binarization framework which focuses primarily on local adaptive thresholding algorithms.
In English, this means that it has the ability to turn a color or gray scale image into a black and white image.
It is written in C++ but supports multiple language bindings.

**Algorithms**
* Otsu - "A threshold selection method from gray-level histograms", 1979.
* Bernsen - "Dynamic thresholding of gray-level images", 1986.
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Wellner - "Interacting with Paper on the DigitalDesk", 1994.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* Feng - "Adaptive Binarization Method for Document Image Analysis", 2004.
* Gatos - "Adaptive degraded document image binarization", 2006. (Partial)
* Bradley - "Adaptive Thresholding Using the Integral Image", 2007.
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.
* AdOtsu - "A multi-scale framework for adaptive binarization of degraded document images", 2010.
* Su - "Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.
* T.R. Singh - "A New local Adaptive Thresholding Technique in Binarization", 2011.
* Bataineh - "An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows", 2011. (unreproducible)
* Phansalkar - "Adaptive Local Thresholding for Detection of Nuclei in Diversely Stained Cytology Images", 2011.
* XDoG - "XDoG: An eXtended difference-of-Gaussians compendium including advanced image stylization", 2012.
* ISauvola - "ISauvola: Improved Sauvola’s Algorithm for Document Image Binarization", 2016.
* WAN - "Binarization of Document Image Using Optimum Threshold Modification", 2018.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Petty - An algorithm for efficiently calculating the min and max of a local window.  Unpublished, 2019.
* Chan - "Memory-efficient and fast implementation of local adaptive binarization methods", 2019.
* SIMD - Supporting: SSE2, ARM NEON, WASM SIMD128

**Performance Metrics**
* Overall Accuracy
* F-Measure, Precision, Recall
* Pseudo F-Measure, Precision, Recall - "Performance Evaluation Methodology for Historical Document Image Binarization", 2013.
* Peak Signal-To-Noise Ratio (PSNR)
* Negative Rate Metric (NRM)
* Matthews Correlation Coefficient (MCC)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Any-Map: PBM (P4), 8-bit PGM (P5), PPM (P6), PAM (P7)

## Overview
The goal of this library is to provide the building blocks one might use to advance the state of handwritten manuscript binarization.
What sets this binarization library apart is that it is intended to be used by those interested in experimenting with their own algorithms and enhancements.
Instead of being relegated to MATLAB, or obfuscated by mathematics in a research paper, a lot of effort has gone into exposing these binarization techniques in an open and transparent way.
A key objective in designing this framework was to make it modular and as easy to use as possible, without sacrificing speed and without depending heavily on 3rd party frameworks.
This library is also heavily unit tested to help ensure quality, and to quickly spot problems after experimenting with the codebase.

### ✨ New in v0.9.8 — BinBench CLI

📊 **BinBench** is a command-line swiss army knife for binarization research — binarize, convert grayscale, score against ground truth, and generate pseudo-F weight maps, all from one small, open, cross-platform script powered by ΔBF.

BinBench was built to be **bit-exact**<sup>1</sup> with `DIBCO_metrics.exe` and `BinEvalWeights.exe`, so the community's standard metrics run anywhere Python does — no closed source Windows binary required. Thanks to the ΔBF, BinBench is so well optimized it can calculate all metrics faster than DIBCO_metrics can with pre-computed weights!

```
python binbench.py evaluate gt.bmp binary.bmp -m accuracy,fm,pseudo-fm,drdm,psnr

image       accuracy↑      fm↑  pseudo-fm↑   drdm↓    psnr↑
----------  ---------  -------  ----------  ------  -------
binary.bmp    97.6715  93.2047     93.3930  1.9519  16.3292
```

👉 See **[CLI/README.md](CLI/README.md)** for the full tour: 18 algorithms, 10 grayscale conversions, and 11 metrics.

<small>1. *Slight floating point drift was found in DIBCO_metrics's DRDM.  BinBench is not bit-exact here as it strives to be as accurate as possible.*</small>

### Example
This short example shows you how easy it is to use ΔBF to process an image.

```cpp
// Read a 32-bit color image and automatically convert to 8-bit gray scale
Image image = PNM::Read(R"(C:\MyImage.pam)");

// Use a binarization algorithm to convert it into black and white
const Parameters parameters({ {"window", 25}, {"k", 0.10} });
Image imageSauvola = Sauvola::ToBinaryImage(image, parameters);

// Save the processed image
PNM::Write(imageSauvola, R"(C:\MyImage-Sauvola.pam)");
```

ΔBF is incredibly light weight, being a header-only library.  It can integrate easily with other 3rd party C++ frameworks like OpenCV and Qt.  Examples can be found under the Demo folder.

### Building and Testing

The core library is header-only and requires no build. For bindings and tests, use CMake presets:

```bash
# Build everything (C++ Tests, Python, WASM, MATLAB)
cmake --preset all
cmake --build build --config Release
ctest --test-dir build -C Release

# Build and run performance benchmarks (Google Benchmark)
cmake --preset benchmarks
cmake --build build-bench --config Release
./build-bench/Doxa.Bench/doxa_bench              # Linux/Mac
.\build-bench\Doxa.Bench\Release\doxa_bench.exe  # Windows

# Build and run C++ unit tests
cmake --preset cpp-tests
cmake --build build-cpp-tests --config Release
ctest --test-dir build-cpp-tests -C Release

# Build and test Python bindings (requires Python 3.12+, nanobind)
cmake --preset python
cmake --build build-python --config Release
ctest --test-dir build-python -C Release

# Build and test WebAssembly (requires Emscripten in PATH)
cmake --preset wasm
cmake --build build-wasm --config Release
ctest --test-dir build-wasm -C Release

# Build and test MATLAB bindings (requires MATLAB)
cmake --preset matlab
cmake --build build-matlab --config Release
ctest --test-dir build-matlab -C Release
```

### Language Bindings
* Javascript / WASM
* Python
* Matlab

Examples of how to use each binding are provided in the Demo folder.

See [Bindings/Python/README.md](Bindings/Python/README.md), [Bindings/WebAssembly/README.md](Bindings/WebAssembly/README.md), and [Bindings/Matlab/README.md](Bindings/Matlab/README.md) for detailed instructions.

A [Live Demo](https://brandonmpetty.github.io/Doxa/WebAssembly) has been created to highlight some of what ΔBF is capable of on the web.

### Benchmarks
The project uses [Google Benchmark](https://github.com/google/benchmark) for measuring runtime performance of SIMD optimizations, calculator backends, and core operations. Benchmarks are separate from unit tests to keep correctness and runtime performance concerns independent.

```bash
# Run benchmarks long enough to lower CV %
./build-bench/Doxa.Bench/doxa_bench --benchmark_min_time=1s --benchmark_repetitions=10 --benchmark_report_aggregates_only=true

# Compare two runs (e.g., before/after a change, or across platforms)
# Requires running doxa_bench with: --benchmark_out=results.json --benchmark_out_format=json
python build-bench/_deps/googlebenchmark-src/tools/compare.py benchmarks before.json after.json
```

### Performance Analysis
Another thing that sets ΔBF apart is its focus on binarization performance.  This makes it incredibly simple to see how your changes affect the overall quality of an algorithm.  All DIBCO metric algorithms, past and present, are provided.  ΔBF's metrics are significantly faster than calling DIBCO_metrics.exe directly.

**NOTE** - DIBCO pseudo-Recall / pseudo-Precision weight maps are now generated natively by ΔBF and are bit-exact with the reference BinEvalWeights.exe - no external tool required!

## License
CC0 - Brandon M. Petty, 2026

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8