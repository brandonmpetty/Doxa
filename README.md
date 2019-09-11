# Δoxa Binarization Framework

<p align="center">
	<img src="/README/2JohnC1V3.png" width="45%" height="45%"/>
	<img src="/README/2JohnC1V3-GroundTruth.png" width="45%" height="45%"/>
</p>

## Introduction
ΔBF is an image binarization framework written in C++ which focuses primarily on local adaptive thresholding algorithms.
In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

**Algorithms**
* Otsu - "A threshold selection method from gray-level histograms", 1979.
* Bernsen - "Dynamic thresholding of gray-level images", 1986.
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* Gatos - "Adaptive degraded document image binarization", 2005. (Partial)
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.
* Su - "Binarization of Historical Document Images Using the Local Maximum and Minimum", 2010.
* T.R. Singh - "A New local Adaptive Thresholding Technique in Binarization", 2011.
* Bataineh - "An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows", 2011. (unreproducible)
* ISauvola - "ISauvola: Improved Sauvola’s Algorithm for Document Image Binarization", 2016.
* WAN - "Binarization of Document Image Using Optimum Threshold Modification", 2018.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Petty - An algorithm for efficiently calculating the min and max of a local window.  Unpublished.

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Negative Rate Metric (NRM)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Any-Map: PBM (P4), 8-bit PGM (P5), PPM (P6), PAM (P7)

## Overview
The goal of this library is to provide the building blocks one might use to advance the state of handwritten manuscript binarization.
What sets this binarization library apart is that it is intended to be used by those interested in experimenting with their own algorithms and enhancements.
Instead of being relegated to MATLAB, or obfuscated by mathematics in a research paper, a lot of effort has gone into exposing these binarization techniques in an open and transparent way.
A key objective in designing this framework was to make it modular and as easy to use as possible, without sacrificing speed and without depending heavily on 3rd party frameworks.
This library is also heavily unit tested to help ensure quality, and to quickly spot problems after experimenting with the codebase.

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
		tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));

// Load the image into a Qt QImage
QImage qImage(imagePath);

// Use Qt to convert to 8-bit grayscale
qImage = qImage.convertToFormat(QImage::Format_Grayscale8);

// Operations on the ΔBF Image will directly change the QImage when set as a reference.
Image image = Image::Reference(qImage.width(), qImage.height(), (Pixel8*)qImage.bits());
Niblack::UpdateToBinary(image, Parameters());

// Save the updated QImage to the file system, using Qt
qImage.save("binary-image.png");
```

Other examples can be found in the Demo folder, like the [BinaryImageConverter](/Demo/BinaryImageConverter) tool.

### Performance Analysis
Another thing that sets ΔBF apart is its focus on binarization performance.
The [PerformanceMetrics](/Demo/PerformanceMetrics) demo highlights how easy it is to get detailed metrics given a sample output and a ground-truth.

### WebAssembly
Experimental WASM support has been added in order to expose ΔBF to the web.
With the provided JavaScript wrapper, it is easy to utilize this framework in any web project.
A [Live Demo](https://brandonmpetty.github.io/Doxa/WebAssembly) has been created to highlight some of what ΔBF is capable of on the web.

### Help Requested
* Verification of algorithm correctness (especially the Wiener filter used in Gatos)
* Implement, in a very clean way, Howe's binarization algorithm

## License
CC0 - Brandon M. Petty, 2019

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8