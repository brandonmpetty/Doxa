# DoxaPy

## Introduction
DoxaPy is an image binarization library focussing on local adaptive thresholding algorithms. In English, this means that it has the ability to turn a color or gray scale image into a black and white image.


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
DoxaPy uses the Δoxa Binarization Framework for quickly processing python Image files.

### Example
This short demo uses DoxaPy to read in a color image, converts it to binary, and then compares it to a Ground Truth image in order to calculate performance.

```python
from PIL import Image
import numpy as np
import doxapy

def read_image(file):
    return np.array(Image.open(file).convert('L'))


# Read our target image and setup an output image buffer
grayscale_image = read_image("2JohnC1V3.png")
binary_image = np.empty(grayscale_image.shape, grayscale_image.dtype)

# Pick an algorithm from the DoxaPy library and convert the image to binary
sauvola = doxapy.Binarization(doxapy.Binarization.Algorithms.SAUVOLA)
sauvola.initialize(grayscale_image)
sauvola.to_binary(binary_image, {"window": 75, "k": 0.2})

# Calculate the binarization performance using a Ground Truth image
groundtruth_image = read_image("2JohnC1V3-GroundTruth.png")
performance = doxapy.calculate_performance(groundtruth_image, binary_image)
print(performance)

# Display our resulting image
Image.fromarray(binary_image).show()
```

### Alternative Calls
DoxaPy can very efficiently reuse the same memory buffer for converting a grayscale image to binary.  Unless you are constantly changing algorithm parameters for the same image, it is recommended that you call this method.

```python
# Transforms the grayscale image buffer into binary with a single call
doxapy.Binarization.update_to_binary(doxapy.Binarization.Algorithms.NICK, grayscale_image)
```


## Building with Pybind11
Release Build - Requires: NumPy, Pybind11
```
clone https://github.com/brandonmpetty/Doxa
cd Doxa/Bindings/Python
python copy-cpp-files.py
python setup.py install
```

## License
CC0 - Brandon M. Petty, 2023

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8