# Δoxa Binarization Framework

<p align="center">
	<img src="/README/2JohnC1V3.png" width="45%" height="45%"/>
	<img src="/README/2JohnC1V3-GroundTruth.png" width="45%" height="45%"/>
</p>

## Introduction
ΔBF is an image binarization framework written in C++ which focuses exclusively on local adaptive thresholding algorithms.
In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

**Algorithms**
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* Gatos - "Adaptive degraded document image binarization", 2005. (Partial)
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Shafait LowMem

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Pixel Map: RGBA PAM

## Overview
The goal of this library is to provide the building blocks one might use to advance the state of handwritten manuscript binarization.
What sets this binarization library apart is that it is intended to be used by those interested in experimenting with their own algorithms and enhancements.
Instead of being relegated to MATLAB, or obfuscated by mathematics in a research paper, a lot of effort has gone into exposing these binarization techniques in an open and transparent way.
A key objective in designing this framework was to make it modular and as easy to use as possible, without sacrificing speed and without depending heavily on 3rd party frameworks.
This library is also heavily unit tested to help ensure quality, and to quickly spot problems after experimenting with the codebase.

### Example
This short example shows you how easy it is to use ΔBF to process an image.

```cpp
// Read a color image
Image image = PPM::Read(R"(C:\MyImage.pam)");

// Convert it to gray scale
Preprocessor::ToGreyScale(image);

// Use a binarization algorithm to convert it into black and white
Image imageSauvola = Sauvola::ToBinaryImage<Shafait>(image, 26, 0.11);

// Save the processed image
PPM::Write(imageSauvola, R"(C:\MyImage-Sauvola.pam)");
```
<br/>
ΔBF is incredibly light weight, being a header-only library.  It can integrate easily with other 3rd party frameworks like Qt.

```cpp
// Qt has great support for working with complex file formats
// Prompt the user to select an image to open, using Qt
QString imagePath = 
	QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"",
		tr("JPEG (*.jpg *.jpeg);;PNG (*.png)")); // Must be 32b RGBA

// Load the image into a Qt QImage
QImage qImage(imagePath);

// Operations on the ΔBF Image will directly change the QImage when set as a reference.
Image image = Image::Reference(qImage.width(), qImage.height(), (Pixel32*)qImage.bits());
Preprocessor::ToGreyScale(image);
Niblack::UpdateImageToBinary<Shafait>(image);  // Due to Shafait, there are no conflicts writing to the same image

// Save the updated QImage to the file system, using Qt
qImage.save("binary-image.png");
```

Other examples can be found in the Demo folder, like the [BinaryImageConverter](/Demo/BinaryImageConverter) tool.

### Performance Analysis

Another thing that sets ΔBF apart is its focus on binarization performance.
While it is easy to write a tool like [PerformanceMetrics](/Demo/PerformanceMetrics) which can analyze a single image, 
it is also possible to analyze the performance of every K-Value and Window Size permutation, for every algorithm, using a tool like [Kumite](/Demo/Kumite).
This can help you judge the true quality of the binarization algorithm.

| Algorithm | Window | K     | Accuracy | F-Measure | PSNR    | DRDM    | Time      | Image     |
| --------- |:------:|:-----:|:--------:|:---------:|:-------:|:-------:|:---------:|:---------:|
| Wolf      | 20     | 0.19  | [97.6747](/Demo/Kumite/Samples/Wolf-Accuracy.csv)    | [93.2996](/Demo/Kumite/Samples/Wolf-FMeasure.csv)    | [16.3352](/Demo/Kumite/Samples/Wolf-PSNR.csv)    | [1.96513](/Demo/Kumite/Samples/Wolf-DRDM.csv)    | [0.0399408](/Demo/Kumite/Samples/Wolf-Time.csv)    | [View](/README/2JohnC1V3-Wolf.png)    |
| Sauvola   | 40     | 0.15  | [97.6654](/Demo/Kumite/Samples/Sauvola-Accuracy.csv) | [93.1474](/Demo/Kumite/Samples/Sauvola-FMeasure.csv) | [16.3179](/Demo/Kumite/Samples/Sauvola-PSNR.csv) | [1.93476](/Demo/Kumite/Samples/Sauvola-DRDM.csv) | [0.0254095](/Demo/Kumite/Samples/Sauvola-Time.csv) | [View](/README/2JohnC1V3-Sauvola.png) |
| Nick      | 42     | -0.11 | [97.6349](/Demo/Kumite/Samples/Nick-Accuracy.csv)    | [93.0599](/Demo/Kumite/Samples/Nick-FMeasure.csv)    | [16.2615](/Demo/Kumite/Samples/Nick-PSNR.csv)    | [1.96143](/Demo/Kumite/Samples/Nick-DRDM.csv)    | [0.0240333](/Demo/Kumite/Samples/Nick-Time.csv)    | [View](/README/2JohnC1V3-Nick.png)    |
| Niblack   | 187    | -0.72 | [97.2744](/Demo/Kumite/Samples/Niblack-Accuracy.csv) | [91.9411](/Demo/Kumite/Samples/Niblack-FMeasure.csv) | [15.6454](/Demo/Kumite/Samples/Niblack-PSNR.csv) | [2.38675](/Demo/Kumite/Samples/Niblack-DRDM.csv) | [0.0252389](/Demo/Kumite/Samples/Niblack-Time.csv) | [View](/README/2JohnC1V3-Niblack.png) |

It should be noted that the Ground Truth used to generate these numbers is, like virtually all Ground Truths, subjective and a work in progress.
A Photoshop PSD file is attached that can be used to make corrections to the Ground Truth as needed.

### Goals
* Refactor to incorporate tiling in order to reduce memory utilization
* ~~Provide the Distance Reciprocal Distortion  (DRD) metric~~
* Improve and expand the PPM image format support
* Internally process 8 bit images to reduce memory consumption

## License
CC0 - Brandon M. Petty, 2017

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8