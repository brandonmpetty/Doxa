# Δoxa Binarization Framework - Matlab

## Introduction
Doxa is an image binarization library focusing on local adaptive thresholding algorithms. In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

This binding provides a simple, high-level interface for using the Doxa C++ framework directly within Matlab, with idiomatic naming and a `Doxa.*` package namespace.

## Build & Test

### Using CMake Presets (Recommended)
```sh
# From the project root
cmake --preset matlab
cmake --build build-matlab --config Release
ctest --test-dir build-matlab -C Release
```

### Package Toolbox (.mltbx)
After building MEX files, create the distributable toolbox from MATLAB:
```matlab
cd Bindings/Matlab
matlab.addons.toolbox.packageToolbox('Doxa.prj')
% Produces Doxa.mltbx
```

## Matlab Example
Add the build output directory to your Matlab path, then use the `Doxa.*` API.

```matlab
% Add the build directory to the path
addpath('path/to/build-matlab/mex');

% Read a color image and convert to grayscale
img = Doxa.Image('photo.ppm', Doxa.Grayscale.QT);

% Binarize with Sauvola (name-value parameters)
binary = Doxa.binarize(Doxa.Algorithms.SAUVOLA, img, window=75, k=0.2);

% Display the result
imshow(binary.toArray());

% Or binarize in-place for efficiency
Doxa.updateToBinary(Doxa.Algorithms.SAUVOLA, img, window=75, k=0.2);
```

## Algorithms
All 13 binarization algorithms are available via `Doxa.Algorithms`:

| Global | Local Adaptive |
|--------|---------------|
| `OTSU` | `BERNSEN`, `NIBLACK`, `SAUVOLA`, `WOLF`, `NICK`, `SU`, `TRSINGH`, `BATAINEH`, `ISAUVOLA`, `WAN`, `GATOS`, `ADOTSU` |

## Grayscale Conversion
Nine grayscale algorithms are available via `Doxa.Grayscale`:

`MEAN`, `QT`, `BT601`, `BT709`, `BT2100`, `VALUE`, `LUSTER`, `LIGHTNESS`, `MINAVG`

```matlab
% Smart constructor handles files, 2D arrays, and 3D color arrays
img = Doxa.Image('color.ppm', Doxa.Grayscale.MEAN);
img = Doxa.Image(rgb_array, Doxa.Grayscale.QT);
img = Doxa.Image(gray_array);
```

## Performance Metrics

```matlab
% Calculate metrics
metrics = Doxa.calculatePerformance(gt, binary);

% With weight files
pw = Doxa.readWeights('precision_weights.dat');
rw = Doxa.readWeights('recall_weights.dat');
metrics = Doxa.calculatePerformance(gt, binary, precisionWeights=pw, recallWeights=rw);
```

**Metrics:** accuracy, fm, recall, precision, psnr, nrm, mcc, drdm, pseudoFM, pseudoPrecision, pseudoRecall

## License
CC0 - Brandon M. Petty, 2026

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8
