# Matlab POC - !!Completely Unstable!!!

## Introduction
Doxa is an image binarization library focussing on local adaptive thresholding algorithms. In English, this means that it has the ability to turn a color or gray scale image into a black and white image. 

**Algorithms**
* Otsu - "A threshold selection method from gray-level histograms", 1979.
* Bernsen - "Dynamic thresholding of gray-level images", 1986.
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* Gatos - "Adaptive degraded document image binarization", 2005. (Partial)
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.
* AdOtsu - "A multi-scale framework for adaptive binarization of degraded document images", 2010.
* Su - "Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.
* T.R. Singh - "A New local Adaptive Thresholding Technique in Binarization", 2011.
* Bataineh - "An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows", 2011. (unreproducible)
* ISauvola - "ISauvola: Improved Sauvola's Algorithm for Document Image Binarization", 2016.
* WAN - "Binarization of Document Image Using Optimum Threshold Modification", 2018.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Petty - An algorithm for efficiently calculating the min and max of a local window.  Unpublished, 2019.
* Chan - "Memory-efficient and fast implementation of local adaptive binarization methods", 2019.

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Negative Rate Metric (NRM)
* Matthews Correlation Coefficient (MCC)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.


## Overview
This Doxa Matlab library uses the Δoxa Binarization Framework for quickly processing images in Matlab.

**Build & Test**
```
cmake -S . -B ./build
cmake --build ./build --config Release
ctest
```

**Matlab Example**
```matlab
% Example grayscale image
originalImage = imread('example.jpg');
outputImage = rgb2gray(originalImage);

% Optional parameters
params.windowSize = 74
params.k = 0.25;

% Perform the binarization
ImageBinarization.updateToBinary(
    outputImage, 
    ImageBinarization.SAUVOLA, 
    params
);

% Display the result
imshow(binaryImage);
```

## License
CC0 - Brandon M. Petty, 2025

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8