# Δoxa Binarization Framework - Matlab

## Introduction
Doxa is an image binarization library focusing on local adaptive thresholding algorithms. In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

This binding provides a simple, high-level interface for using the Doxa C++ framework directly within Matlab.

## Build & Test
Building the Matlab bindings requires CMake and a C++ compiler. Ensure that Matlab is correctly configured for MEX compilation (`mex -setup`).

```sh
# From the Bindings/Matlab directory
mkdir build
cd build

# Configure the build
cmake ..

# Build the MEX files
cmake --build . --config Release

# Run the tests
ctest -C Release
```

## Matlab Example
Using the Doxa framework in Matlab is straightforward. First, add the build output directory to your Matlab path. Then, you can use the static methods on the `Doxa` class.

```matlab
% Add the build directory (e.g., Bindings/Matlab/build/mex) to the path
addpath('path/to/your/build/mex');

% 1. Read a grayscale image
originalImage = imread('peppers.png');
grayscaleImage = rgb2gray(originalImage);

% 2. Select an algorithm and define parameters
% Parameters are optional and will use library defaults if not provided.
params.window = 25;
params.k = 0.1;

% 3. Binarize the image
% This creates a new binary image, leaving the original unchanged.
binaryImage = Doxa.to_binary(Doxa.SAUVOLA, grayscaleImage, params);

% Or, for maximum efficiency, update the image in-place
% Doxa.update_to_binary(Doxa.SAUVOLA, grayscaleImage, params);

% 4. Display the result
figure;
subplot(1, 2, 1), imshow(originalImage), title('Original');
subplot(1, 2, 2), imshow(binaryImage), title('Binarized (Sauvola)');

% 5. Calculate performance against a ground truth
groundTruthImage = imread('ground_truth.png');
metrics = Doxa.calculate_performance(groundTruthImage, binaryImage);
disp(metrics);
```

## License
CC0 - Brandon M. Petty, 2025

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8
