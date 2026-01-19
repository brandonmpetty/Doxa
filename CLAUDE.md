# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

Doxa is a **header-only C++ image binarization framework** that converts grayscale images to binary (black and white). The core library has zero external dependencies and is designed to be lightweight and easy to integrate with other frameworks (OpenCV, Qt, etc.). Language bindings exist for Python and WebAssembly/JavaScript.

## Build and Test Commands

The project uses CMake presets for unified builds. All commands run from the project root.

### Quick Start (CMake Presets)

```bash
# Build and run C++ unit tests
cmake --preset release
cmake --build build --config Release
ctest --test-dir build -C Release

# Build and test Python bindings
cmake --preset python
cmake --build build-python --config Release
ctest --test-dir build-python -C Release

# Build and test WebAssembly (requires Emscripten in PATH)
cmake --preset wasm
cmake --build build-wasm --config Release
ctest --test-dir build-wasm -C Release

# Build everything (C++, Python, WASM)
cmake --preset all
cmake --build build --config Release
ctest --test-dir build -C Release
```

**Note:** On Windows with Visual Studio (multi-config generator), `--config Release` and `-C Release` are required. On Linux/Mac with single-config generators (Make, Ninja), these flags are optional.

### C++ Unit Tests

The C++ test suite uses Google Test (fetched automatically via CMake).

```bash
# Using preset (recommended)
cmake --preset release
cmake --build build --config Release
ctest --test-dir build -C Release

# Or build directly from Doxa.Test
cd Doxa.Test
cmake -S . -B ./build
cmake --build ./build --config Release
ctest --test-dir ./build -C Release  # Or run directly:
./build/doxa_test  # Linux/Mac
./build/Release/doxa_test.exe  # Windows
```

### Python Bindings (DoxaPy)

DoxaPy requires Python 3.12+ and uses nanobind for C++ interop.

```bash
# Using preset (recommended)
cmake --preset python
cmake --build build-python --config Release
ctest --test-dir build-python -C Release

# Or build from Bindings/Python directory
cd Bindings/Python
pip install -r requirements.txt
python copy-cpp-files.py
cmake -S . -B ./build
cmake --build ./build --config Release
python test/test_doxa.py

# Build distributable wheel (uses cibuildwheel)
python -m build
```

### WebAssembly Bindings (DoxaJs)

DoxaJs uses CMake with Emscripten toolchain.

```bash
# Using preset (recommended, requires emcmake in PATH)
cmake --preset wasm
cmake --build build-wasm --config Release
ctest --test-dir build-wasm -C Release

# Or build directly with emcmake
emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release
cmake --build build-wasm --config Release
cd Bindings/WebAssembly && npm test

# Output: ./dist/doxaWasm.js and ./dist/doxaWasm.wasm
```

## Architecture

### Header-Only Core Library

The entire core library is in `Doxa/*.hpp` files. There is no build step for the core library - just include the headers.

**Key Files:**
- `Doxa/Image.hpp` - Core 8-bit image data structure with move semantics
- `Doxa/Algorithm.hpp` - Base algorithm interface using CRTP (Curiously Recurring Template Pattern)
- `Doxa/Parameters.hpp` - Key-value parameter system (supports `{"window": 75, "k": 0.2}`)
- `Doxa/PNM.hpp` - Image I/O for Portable Any-Map formats (PBM, PGM, PPM, PAM)
- `Doxa/BinarizationFactory.hpp` - Factory pattern for algorithm instantiation
- `Doxa/ClassifiedPerformance.hpp` - Performance metrics (Accuracy, F-Measure, Precision, Recall, MCC, PSNR, NRM)
- `Doxa/DRDM.hpp` - Distance-Reciprocal Distortion Measure metric

### Algorithm Organization

All binarization algorithms inherit from `Algorithm<T>` base class (CRTP pattern):

**Global Thresholding:**
- `Otsu.hpp` - Histogram-based single threshold

**Local Adaptive Thresholding:**
- `Sauvola.hpp`, `Niblack.hpp`, `Wolf.hpp`, `Nick.hpp`, `TRSingh.hpp`, `Bernsen.hpp`, `ISauvola.hpp`, `Wan.hpp`, `Su.hpp`, `Gatos.hpp`, `Bataineh.hpp`, `AdOtsu.hpp`

Each algorithm can be called statically via:
```cpp
Image binaryImage = Sauvola::ToBinaryImage(grayImage, parameters);
```

Or instantiated for reuse:
```cpp
Sauvola sauvola;
sauvola.Initialize(grayImage);
sauvola.ToBinary(binaryImage, parameters);
```

### Calculation Optimizations

The framework includes multiple optimization strategies for local window operations:

- `ChanMeanVarianceCalc.hpp` - Memory-efficient sliding window (Chan 2019)
- `IntegralImageMeanVarianceCalc.hpp` - Integral image acceleration (Shafait 2008)
- `LocalWindow.hpp` - Generic window iteration template
- `GridCalc.hpp` - Grid-based calculations

Algorithms use these via template inheritance to avoid virtual function overhead.

### Language Bindings Architecture

**Python (DoxaPy):**
- `Bindings/Python/src/DoxaPy.cpp` - nanobind wrapper exposing all 13 algorithms
- Converts NumPy arrays ↔ Doxa Image objects
- Usage pattern:
  ```python
  sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
  sauvola.initialize(grayscale_image)  # NumPy array
  sauvola.to_binary(binary_image, {"window": 75, "k": 0.2})
  ```
- Build system: scikit-build-core + cibuildwheel for cross-platform wheels
- Published to PyPI as `doxapy`

**WebAssembly (DoxaJs):**
- `Bindings/WebAssembly/DoxaWasm.cpp` - Emscripten bindings
- `Bindings/WebAssembly/doxa.js` - JavaScript convenience wrapper
- Works with raw memory pointers (WASM memory model)
- Build output: `./dist/doxaWasm.js` and `./dist/doxaWasm.wasm`
- Live demo: https://brandonmpetty.github.io/Doxa/WebAssembly

### Integration with External Libraries

The `Image` class supports external memory management via `Image::Reference()`, allowing zero-copy integration with:
- OpenCV (see `Demo/Cpp/demoOpenCV.cpp`)
- Qt (see `Demo/Cpp/demoQt.cpp`)
- PIL/Pillow (see `Demo/Python/demo.py`)

## Testing Structure

**C++ Tests (`Doxa.Test/`):**
- Uses Google Test framework (fetched via CMake FetchContent)
- Test files mirror the module structure: `ImageTests.cpp`, `BinarizationTests.cpp`, `CalculatorTests.cpp`, etc.
- `ImageFixture.hpp` provides test utilities and sample images
- `Resources/` contains ground truth images for validation
- Requires C++17 standard

**Python Tests:**
- `Bindings/Python/test/test_doxa.py` - Basic functionality and performance tests
- Run with: `python test/test_doxa.py`

## Key Design Patterns

1. **CRTP (Curiously Recurring Template Pattern)**: `Algorithm<T>` base class provides static polymorphism without virtual function overhead

2. **Template-Based Calculators**: Algorithms inherit from calculator classes (e.g., `ChanMeanVarianceCalc`) using templates for zero-cost abstractions

3. **Factory Pattern**: `BinarizationFactory` enables dynamic algorithm selection at runtime

4. **Parameter Variant System**: `Parameters` class uses variant<int, double> for flexible, serializable configuration

5. **Move Semantics**: `Image` class uses move constructors/assignment for efficient memory management

## Common Development Workflows

### Adding a New Binarization Algorithm

1. Create `Doxa/MyAlgorithm.hpp`
2. Inherit from `Algorithm<MyAlgorithm>` (CRTP pattern)
3. Choose appropriate calculator base class (e.g., `ChanMeanVarianceCalc`)
4. Implement `CalculateThreshold()` method with algorithm-specific logic
5. Add algorithm to `BinarizationFactory.hpp`
6. Create corresponding test in `Doxa.Test/BinarizationTests.cpp`
7. Update bindings in `DoxaPy.cpp` and `DoxaWasm.cpp`

### Modifying Python Bindings

1. Edit `Bindings/Python/src/DoxaPy.cpp` (nanobind code)
2. Rebuild: `cmake --build ./build --config Release`
3. Test: `python test/test_doxa.py`
4. For distribution: update version in `pyproject.toml` and run `python -m build`

### Modifying WebAssembly Bindings

1. Edit `Bindings/WebAssembly/DoxaWasm.cpp` (Emscripten bindings)
2. Optionally update `doxa.js` (JavaScript wrapper)
3. Rebuild: `emcmake cmake -S . -B build-wasm && cmake --build build-wasm`
4. Test: `cd Bindings/WebAssembly && npm test`

## Performance Metrics

The framework includes comprehensive performance evaluation tools:

- **ClassifiedPerformance**: Accuracy, F-Measure, Precision, Recall, MCC, PSNR, NRM
- **Pseudo-Metrics**: Pseudo F-Measure, Precision, Recall (for degraded documents)
- **DRDM**: Distance-Reciprocal Distortion Measure (perceptual quality)

Usage:
```cpp
ClassifiedPerformance performance = ClassifiedPerformance::CalculatePerformance(groundTruth, binaryImage);
```

## Build System Notes

- **C++ Core**: Header-only, no build required
- **C++ Tests**: CMake 3.16+ or Visual Studio 2019+
- **Python**: CMake + nanobind + scikit-build-core (requires Python 3.12+)
- **WebAssembly**: CMake + Emscripten toolchain (use `emcmake cmake`)
- **Standard**: C++17
- **Architecture**: 64-bit only (enforced in cibuildwheel config)
- **CMake Presets**: `default` (C++), `python`, `all` (everything)
